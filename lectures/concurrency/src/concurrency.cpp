// ReSharper disable CppClangTidyCppcoreguidelinesAvoidNonConstGlobalVariables
// ReSharper disable CppTooWideScope
#include "concurrency.hpp"

#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

namespace conc {

namespace {
std::mutex cout_mutex; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
}

///////////////////////////////////////////////////////////////////////
/// print_project_info_concurrently()
///

void print_project_name()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(12));
    std::lock_guard guard{cout_mutex};
    std::cout << "  name:      concurrency\n";
}
void print_project_namespace()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::lock_guard guard{cout_mutex};
    std::cout << "  namespace: conc\n";
}

void print_project_info_concurrently()
{
    std::cout << "Subproject Info\n\n";
    std::thread name_printer{print_project_name};
    std::thread namespace_printer{print_project_namespace};

    // If you forget to join, the thread destructor will call std::terminate!
    name_printer.join();
    namespace_printer.join();
}

///////////////////////////////////////////////////////////////////////
/// wait_for_detached_threads()
///

void count_up(int start)
{
    for (int i{start}; i <= start + 4; ++i) {
        {
            // Similar to std::lock_guard but allows locking multiple mutexes in
            // a safe fashion. Use std::lock() to achieve this if you're working
            // with C++11/14.
            std::scoped_lock guard{cout_mutex};
            std::cout << "The next number for counter " << std::this_thread::get_id()
                      << " is " << i << "\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::scoped_lock guard{cout_mutex};
    std::cout << "Counter " << std::this_thread::get_id() << " is exiting.\n";
}

void launch_and_detach_threads()
{
    std::thread counter_1{count_up, 1};
    counter_1.detach();

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::thread counter_2{count_up, 10};
    counter_2.detach();
}

void wait_for_detached_threads(int time_to_wait)
{
    std::cout << "launch_and_detach_threads() started.\n";

    conc::launch_and_detach_threads();
    {
        std::scoped_lock guard{cout_mutex};
        std::cout << "launch_and_detach_threads() returned.\n";
    }
    // Don't do this!
    // std::scoped_lock guard{cout_mutex};

    std::this_thread::sleep_for(std::chrono::seconds(time_to_wait));

    {
        std::scoped_lock guard{cout_mutex};
        std::cout << "wait_for_detached_threads() is exiting.\n";
    }
}


///////////////////////////////////////////////////////////////////////
/// return_thread_from_function()
///
std::thread create_a_thread()
{
    std::thread result{[]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << "Running thread.\n";
    }};
    std::cout << "Created thread.\n";
    return result;
}

void return_thread_from_function()
{
    std::thread my_thread{create_a_thread()};
    std::cout << "Got thread!\n";
    // std::thread also_my_thread{std::move(my_thread)};
    // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (my_thread.joinable()) {
        std::cout << "Joining thread.\n";
        my_thread.join();
        std::cout << "Joined thread.\n";
    }
    else {
        std::cout << "NOT joining thread.\n";
    }
}

///////////////////////////////////////////////////////////////////////
/// launch_and_join_many_threads()
///

struct ThreadGuard
{
    explicit ThreadGuard(std::thread&& my_thread) : my_thread{std::move(my_thread)} {}

    ThreadGuard(const ThreadGuard& other) = delete;
    ThreadGuard(ThreadGuard&& other) noexcept = default;

    ThreadGuard& operator=(const ThreadGuard& other) = delete;
    ThreadGuard& operator=(ThreadGuard&& other) noexcept = default;

    ~ThreadGuard()
    {
        if (my_thread.joinable()) {
            my_thread.join();
        }
    }

    [[nodiscard]] const std::thread& thread() const { return my_thread; }

    std::thread my_thread;
};

void test_thread_guard()
{
    {
        ThreadGuard tg{std::thread{[] { std::cout << "Running thread.\n"; }}};
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        if (tg.thread().joinable()) {
            std::cout << "Thread is still joinable.\n";
        }
    }
}

void test_thread_guard_vector()
{
    {
        std::vector<ThreadGuard> guards{};
        guards.push_back(
            ThreadGuard{std::thread{[] { std::cout << "Running thread.\n"; }}});
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        if (guards[0].thread().joinable()) {
            std::cout << "Thread is still joinable.\n";
        }
    }
}

void throw_while_launching(int num_threads, int expression_thrown_at)
{
    std::vector<ThreadGuard> threads{};
    for (int i{0}; i < num_threads; ++i) {
        threads.push_back(ThreadGuard{std::thread{[i, num_threads]() {
            {
                std::scoped_lock guard{cout_mutex};
                std::cout << "Thread with id " << std::this_thread::get_id()
                          << " is starting.\n";
            }
            std::this_thread::sleep_for(
                std::chrono::milliseconds(500 + 100 * num_threads - 100 * i));
            {
                std::scoped_lock guard{cout_mutex};
                std::cout << "Thread with id " << std::this_thread::get_id()
                          << " is stopping.\n";
            }
        }}});
        if (i == expression_thrown_at) {
            throw std::runtime_error("Something went wrong.");
        }
    }
}

void launch_and_join_many_threads()
{
    try {
        throw_while_launching(10, 20);
    }
    catch (const std::runtime_error& err) {
        std::cout << "Caught error: " << err.what() << "\n";
    }
}

///////////////////////////////////////////////////////////////////////
/// adapt_thread_number_to_hardware()
///

void adapt_thread_number_to_hardware()
{
    throw_while_launching(
        std::clamp<int>(std::thread::hardware_concurrency(), 2, 32), -1);
}


///////////////////////////////////////////////////////////////////////
/// work_on_seemingly_protected_class()
///

void work_on_seemingly_protected_class()
{
    MySeeminglyProtectedClass my_protected_class{};
    {
        std::vector<ThreadGuard> my_threads{};
        for (int i{0}; i < 10; ++i) {
            my_threads.push_back(ThreadGuard{std::thread{[&my_protected_class] {
                for (int i{0}; i < 1000; ++i) {
                    const int data{my_protected_class.data()};
                    my_protected_class.data(data + 1);
                }
            }}});
        }
    }
    std::cout << "Item = " << my_protected_class.data() << "\n";
}


///////////////////////////////////////////////////////////////////////
/// work_on_struct_with_mutex()
///

void work_on_struct_with_mutex()
{
    MyStructWithMutex my_protected_struct{};
    {
        std::vector<ThreadGuard> my_threads{};
        for (int i{0}; i < 10; ++i) {
            my_threads.push_back(ThreadGuard{std::thread{[&my_protected_struct] {
                for (int i{0}; i < 1000; ++i) {
                    // Could also use ++data; this wouldn't remove the need for a lock.
                    {
                        std::scoped_lock lock{my_protected_struct.mutex};
                        const int data{my_protected_struct.data};
                        my_protected_struct.data = data + 1;
                    }
                }
            }}});
        }
    }
    std::cout << "Item = " << my_protected_struct.data << "\n";
}


///////////////////////////////////////////////////////////////////////
/// work_on_multiple_structs_with_mutex()
///

void work_on_multiple_structs_with_mutex()
{
    MyStructWithMutex s1{};
    MyStructWithMutex s2{};
    {
        std::vector<ThreadGuard> my_threads{};
        for (int i{0}; i < 10; ++i) {
            my_threads.push_back(ThreadGuard{std::thread{[&s1] {
                for (int i{0}; i < 200; ++i) {
                    {
                        std::scoped_lock lock{s1.mutex};
                        ++s1.data;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }}});
        }
        for (int i{0}; i < 10; ++i) {
            my_threads.push_back(ThreadGuard{std::thread{[&s2] {
                for (int i{0}; i < 200; ++i) {
                    {
                        std::scoped_lock lock{s2.mutex};
                        ++s2.data;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }}});
        }
        for (int i{0}; i < 10; ++i) {
            my_threads.push_back(ThreadGuard{std::thread{[&s1, &s2] {
                for (int i{0}; i < 200; ++i) {
                    {
                        std::scoped_lock lock{s1.mutex, s2.mutex};
                        --s1.data;
                        ++s2.data;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
            }}});
        }
    }
    std::cout << "S1.data = " << s1.data << "\n";
    std::cout << "S2.data = " << s2.data << "\n";
}


// Think in transactions/critical regions
// Lock all locks simultaneously (using std::lock() or std::scoped_lock{})
// Avoid nested locks
// Avoid calling user-supplied code while holding a lock
// Acquire locks in fixed order (if you absolutely have to)
// Use a lock hierarchy

long long get_value()
{
    static long long result{
        std::chrono::system_clock::now().time_since_epoch().count()};
    return result;
}


///////////////////////////////////////////////////////////////////////
/// use_static_initializer()
///

void use_static_initializer()
{
    std::vector<ThreadGuard> my_threads{};
    for (int i{0}; i < 10; ++i) {
        my_threads.push_back(ThreadGuard{std::thread{[] {
            std::scoped_lock lock{cout_mutex};
            std::cout << "Value = " << get_value() << "\n";
        }}});
    }
}

// See also std::call_once()


///////////////////////////////////////////////////////////////////////
/// use_static_initializer()
///

int num_items_to_process{20};
bool more_items_to_process() { return num_items_to_process >= 0; }

struct Item
{
    // ReSharper disable once CppMemberFunctionMayBeConst
    void process() { std::cout << "Processing item number " << item_number << ".\n"; }
    int item_number{};
};

Item get_next_item() { return Item{num_items_to_process--}; }


std::mutex mutex;
std::queue<Item> item_queue;
std::condition_variable item_cond;
void item_producer()
{
    while (more_items_to_process()) {
        const Item item{get_next_item()};
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::scoped_lock lock{mutex};
            item_queue.push(item);
        }
        item_cond.notify_one();
    }
}

void item_consumer()
{
    while (true) {
        std::unique_lock lock{mutex};
        item_cond.wait(lock, [] { return !item_queue.empty(); });
        Item item{item_queue.front()};
        item_queue.pop();
        lock.unlock();

        item.process();
        if (!more_items_to_process()) {
            break;
        }
    }
}

void run_producer_consumer_example()
{
    std::vector<ThreadGuard> my_threads{};
    my_threads.push_back(ThreadGuard{std::thread{item_consumer}});
    my_threads.push_back(ThreadGuard{std::thread{item_producer}});
}

} // namespace conc

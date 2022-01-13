#pragma once
#ifndef CONCURRENCY_HPP
#define CONCURRENCY_HPP
#include <mutex>

namespace conc {

void print_project_info_concurrently(bool throw_exception = false);
void print_project_info_concurrently_no_lock_guard(bool throw_exception = false);
void wait_for_detached_threads(int time_to_wait);
void return_thread_from_function();
void test_thread_guard();
void test_thread_guard_vector();
void launch_and_join_many_threads();
void adapt_thread_number_to_hardware();

// Not really a good idea...
class MySeeminglyProtectedClass
{
public:
    explicit MySeeminglyProtectedClass(int my_data = 0) : my_data{my_data} {}

    [[nodiscard]] int data() const
    {
        std::scoped_lock lock{class_mutex};
        return my_data;
    }

    void data(int new_data)
    {
        std::scoped_lock lock{class_mutex};
        my_data = new_data;
    }

    // Uh oh...
    int& data_as_ref()
    {
        std::scoped_lock lock{class_mutex};
        return my_data;
    }
    
private:
    mutable std::mutex class_mutex;
    int my_data{};
};

void work_on_seemingly_protected_class();

struct MyStructWithMutex
{
    std::mutex mutex;
    int data{};
};
void work_on_struct_with_mutex();
void work_on_multiple_structs_with_mutex();

void use_static_initializer();

void run_producer_consumer_example();
void compute_with_futures(int num_futures);
void compute_with_futures_with_different_timings(int num_futures);
void compute_with_data(int num_futures);

} // namespace conc

#endif // CONCURRENCY_HPP

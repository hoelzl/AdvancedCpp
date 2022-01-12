#include "concurrency.hpp"

int main()
{
	//conc::print_project_info_concurrently();
	//conc::wait_for_detached_threads(5);
	//conc::return_thread_from_function();
	//conc::test_thread_guard();
	//conc::test_thread_guard_vector();
	//conc::launch_and_join_many_threads();
	//conc::adapt_thread_number_to_hardware();
    //conc::work_on_seemingly_protected_class();
	//conc::work_on_struct_with_mutex();
	//conc::work_on_multiple_structs_with_mutex();
	//conc::use_static_initializer();
	conc::run_producer_consumer_example();
}

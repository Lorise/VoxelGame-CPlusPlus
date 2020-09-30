#pragma once
#include "Headers.h"

namespace lib
{
	class ThreadPool
	{
	public:
		ThreadPool( size_t );

		template<class F, class... Args>
		auto enqueue( F&& f, Args&&... args )->std::future<typename std::result_of<F( Args... )>::type>;

		~ThreadPool();

	private:
		// need to keep track of threads so we can join them
		std::vector< std::thread > _workers;

		// the task queue
		std::queue< std::function<void()> > _tasks;

		// synchronization
		std::mutex _queue_mutex;
		std::condition_variable _condition;
		bool _stop;
	};

	// add new work item to the pool
	template<class F, class... Args>
	auto ThreadPool::enqueue( F&& f, Args&&... args )-> std::future<typename std::result_of<F( Args... )>::type>
	{
		using return_type = typename std::result_of<F( Args... )>::type;

		auto task = std::make_shared< std::packaged_task<return_type()> >( std::bind( std::forward<F>( f ), std::forward<Args>( args )... ) );

		std::future<return_type> res = task->get_future();
		{
			std::unique_lock<std::mutex> lock( _queue_mutex );

			// don't allow enqueueing after stopping the pool
			if ( _stop )
				throw std::runtime_error( "enqueue on stopped ThreadPool" );

			_tasks.emplace( [ task ]()
			{
				( *task )( );
			} );
		}

		_condition.notify_one();

		return res;
	}
}
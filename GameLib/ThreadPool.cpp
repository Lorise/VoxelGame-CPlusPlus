#include "ThreadPool.h"

namespace lib
{
	// the constructor just launches some amount of workers
	ThreadPool::ThreadPool( size_t threads ) : _stop( false )
	{
		for ( size_t i = 0; i < threads; ++i )
			_workers.emplace_back( [ this ]
		{
			for ( ;;)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock( this->_queue_mutex );

					this->_condition.wait( lock, [ this ]
					{
						return this->_stop || !this->_tasks.empty();
					} );

					if ( this->_stop && this->_tasks.empty() )
						return;

					task = std::move( this->_tasks.front() );

					this->_tasks.pop();
				}
				task();
			}
		} );
	}

	// the destructor joins all threads
	ThreadPool::~ThreadPool()
	{
		{
			std::unique_lock<std::mutex> lock( _queue_mutex );
			_stop = true;
		}

		_condition.notify_all();

		for ( std::thread &worker : _workers )
			worker.join();
	}
}
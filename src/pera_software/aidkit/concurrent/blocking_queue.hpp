// Copyright 2023 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

namespace pera_software::aidkit::concurrent {

template <typename T>
	class blocking_queue
	{
		public:
			blocking_queue() = default;

			void wait()
			{
				std::unique_lock lock(mutex_);

				condition_.wait(lock, [this] { return !queue_.empty(); });
			}

			bool wait(const std::chrono::milliseconds &duration)
			{
				std::unique_lock lock(mutex_);

				return condition_.wait_for(lock, duration, [this] { return !queue_.empty(); });
			}

			void enqueue(const T &item)
			{
				std::unique_lock lock(mutex_);

				queue_.push(item);
				condition_.notify_one();
			}

			T dequeue()
			{
				std::unique_lock lock(mutex_);

				condition_.wait(lock, [this] { return !queue_.empty(); });

				T item(queue_.front());
				queue_.pop();

				return item;
			}

			size_t size() const
			{
				std::unique_lock lock(mutex_);

				return queue_.size();
			}

		private:
			mutable std::mutex mutex_;
			std::condition_variable condition_;
			std::queue<T> queue_;
	};

}

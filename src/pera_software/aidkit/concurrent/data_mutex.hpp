// Copyright 2019 Peter Most, PERA Software Solutions GmbH
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

namespace pera_software::aidkit::concurrent {

template <typename T, typename Mutex>
	class data_mutex_ptr;

template <typename T, typename Mutex>
	class const_data_mutex_ptr;

template <typename T, typename Mutex = std::mutex>
	class data_mutex {
		public:
			template <typename... Args>
				data_mutex(Args &&... args)
					: data_(std::forward<Args>(args)...)
				{
				}

			data_mutex(const data_mutex &) = delete;
			data_mutex &operator=(const data_mutex &) = delete;

		private:
			friend data_mutex_ptr<T, Mutex>;
			friend const_data_mutex_ptr<T, Mutex>;

			T data_;
			mutable Mutex mutex_;
	};

template <typename T, typename Mutex = std::mutex>
	class data_mutex_ptr {
		public:
			explicit data_mutex_ptr(data_mutex<T, Mutex> *dataMutex) noexcept
				: data_(&dataMutex->data_), mutex_(&dataMutex->mutex_)
			{
				mutex_->lock();
			}

			~data_mutex_ptr() noexcept
			{
				mutex_->unlock();
			}

			T *operator->() noexcept
			{
				return data_;
			}

			T &operator*() noexcept
			{
				return *data_;
			}

			data_mutex_ptr(const data_mutex_ptr &) = delete;
			data_mutex_ptr &operator=(const data_mutex_ptr &) = delete;

		private:
			T *data_;
			mutable Mutex *mutex_;
	};

// Provide class template argument deduction guide (CTAD) to silence the warning:
// "'data_mutex_ptr' may not intend to support class template argument deduction [-Wctad-maybe-unsupported]"

template <typename T, typename Mutex>
	data_mutex_ptr(data_mutex<T, Mutex>) -> data_mutex_ptr<T, Mutex>;

template <typename T, typename Mutex = std::mutex>
	class const_data_mutex_ptr {
		public:
			explicit const_data_mutex_ptr(const data_mutex<T, Mutex> *dataMutex) noexcept
				: data_(&dataMutex->data_), mutex_(&dataMutex->mutex_)
			{
				mutex_->lock();
			}

			~const_data_mutex_ptr() noexcept
			{
				mutex_->unlock();
			}

			const T *operator->() const noexcept
			{
				return data_;
			}

			const T &operator*() const noexcept
			{
				return *data_;
			}

			const_data_mutex_ptr(const const_data_mutex_ptr &) = delete;
			const_data_mutex_ptr &operator=(const const_data_mutex_ptr &) = delete;

		private:
			const T *data_;
			mutable Mutex *mutex_;
	};

// Provide class template argument deduction guide (CTAD) to silence the warning:
// "'const_data_mutex_ptr' may not intend to support class template argument deduction [-Wctad-maybe-unsupported]"

template <typename T, typename Mutex>
	const_data_mutex_ptr(data_mutex<T, Mutex>) -> const_data_mutex_ptr<T, Mutex>;
}

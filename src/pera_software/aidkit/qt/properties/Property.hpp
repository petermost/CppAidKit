// Copyright 2020 Peter Most, PERA Software Solutions GmbH
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

#include <QObject>

namespace pera_software::aidkit::qt {

template <typename T>
	class Property : public QObject
	{
		public:
			explicit Property(QObject *parent = nullptr)
				: Property(T(), parent)
			{
			}

			explicit Property(T value, QObject *parent = nullptr)
				: QObject(parent), value_(std::move(value))
			{
			}

			Property &operator = (const Property<T> &other)
			{
				setValue(other.value());

				return *this;
			}

			T operator = (T value)
			{
				setValue(value);

				return value_;
			}

			operator T () const
			{
				return value_;
			}

			T value() const
			{
				return value_;
			}

		public Q_SLOTS:
			void setValue(T value)
			{
				if (value_ != value) {
					value_ = std::move(value);
					emitValueChanged(value_);
				}
			}

		protected:
			virtual void emitValueChanged(T value) = 0;

		private:
			T value_;
	};

}

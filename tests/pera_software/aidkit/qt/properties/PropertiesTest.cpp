// Copyright 2015 Peter Most, PERA Software Solutions GmbH
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

#include <pera_software/aidkit/qt/core/Strings.hpp>
#include <pera_software/aidkit/qt/properties/StringProperty.hpp>
#include <pera_software/aidkit/qt/properties/IntegerProperty.hpp>
#include <QSignalSpy>
#include <gtest/gtest.h>

namespace pera_software::aidkit::qt {

using namespace std;

TEST(IntegerPropertyTest, testMethods)
{
	IntegerProperty property;
	QSignalSpy spy(&property, &IntegerProperty::valueChanged);
	ASSERT_TRUE(spy.isValid());
	ASSERT_EQ(property.value(), 0);

	property.setValue(13);
	ASSERT_EQ(property.value(), 13);

	ASSERT_EQ(spy.count(), 1);
	ASSERT_EQ(spy[0][0].toInt(), 13);
}

TEST(IntegerPropertyTest, testOperators)
{
	IntegerProperty property(10);
	QSignalSpy spy(&property, &IntegerProperty::valueChanged);
	ASSERT_TRUE(spy.isValid());
	ASSERT_EQ(property.value(), 10);

	property = 13;
	ASSERT_EQ(property, 13);

	ASSERT_EQ(spy.count(), 1);
	ASSERT_EQ(spy[0][0].toInt(), 13);
}

TEST(StringPropertyTest, testMethods)
{
	StringProperty property;
	QSignalSpy spy(&property, &StringProperty::valueChanged);
	ASSERT_TRUE(spy.isValid());
	ASSERT_TRUE(property.value().isEmpty());

	property.setValue("13"_qs);
	ASSERT_EQ(property.value(), "13"_qs);

	ASSERT_EQ(spy.count(), 1);
	ASSERT_EQ(spy[0][0].toString(), "13"_qs);
}

TEST(StringPropertyTest, testOperators)
{
	StringProperty property("10"_qs);
	QSignalSpy spy(&property, &StringProperty::valueChanged);
	ASSERT_TRUE(spy.isValid());
	ASSERT_EQ(property.value(), "10"_qs);

	property = "13"_qs;
	ASSERT_EQ(property, "13"_qs);

	ASSERT_EQ(spy.count(), 1);
	ASSERT_EQ(spy[0][0].toString(), "13"_qs);
}

}

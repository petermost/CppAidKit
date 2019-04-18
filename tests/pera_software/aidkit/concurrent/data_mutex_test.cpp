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

#include "data_mutex_test.hpp"
#include <pera_software/aidkit/concurrent/data_mutex.hpp>
#include <QTest>
#include <vector>
#include <string>
#include <map>

namespace pera_software::aidkit::concurrent {

using namespace std;

static DataMutexTest mutexTest;


class Image {
};

shared_ptr<Image> loadImageFromFile(const string & /* fileName */)
{
	return make_shared<Image>();
}

class ExplicitLockedImageCache {
	public:
		shared_ptr<Image> loadImage(const string &name)
		{
			lock_guard lock(mutex_);

			auto position = cachedImages.find(name);
			if (position == cachedImages.end()) {
				shared_ptr<Image> image = loadImageFromFile(name);
				cachedImages.insert({name, image});
				return image;
			} else {
				return position->second;
			}
		}

		void removeImage(const string &name)
		{
			auto position = cachedImages.find(name);
			if (position != cachedImages.end()) {
				cachedImages.erase(position);
			}
		}

	private:
		mutex mutex_;
		map<string, shared_ptr<Image>> cachedImages;
};

class ImplicitLockedImageCache {
	public:
		shared_ptr<Image> loadImage(const string &name)
		{
			data_ptr images(&cachedImages);

			auto position = images->find(name);
			if (position == images->end()) {
				shared_ptr<Image> image = loadImageFromFile(name);
				images->insert({name, image});
				return image;
			} else {
				return position->second;
			}
		}

		void removeImage(const string &name)
		{
			data_ptr images(&cachedImages);

			auto position = images->find(name);
			if (position != images->end()) {
				images->erase(position);
			}
		}

	private:
		data_mutex<map<string, shared_ptr<Image>>> cachedImages;
};




//#########################################################################################################

// Explicit template instantiation to detect syntax errors:
using StringVectorDataMutex = class data_mutex< vector< string >>;

void DataMutexTest::testRegularLocking()
{
	StringVectorDataMutex names( 20u, "empty" );

	data_ptr names_ptr(&names);
	names_ptr->at(0) = "";
	(*names_ptr)[0] = "";
}

void DataMutexTest::testConstLocking()
{
	const StringVectorDataMutex names( 20u, "empty" );

	const_data_ptr names_ptr(&names);
	string first = names_ptr->at(0);
	first = (*names_ptr)[0];
}

}

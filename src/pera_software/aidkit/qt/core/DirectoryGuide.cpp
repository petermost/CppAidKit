// Copyright 2014 Peter Most, PERA Software Solutions GmbH
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

#include "DirectoryGuide.hpp"
#include <QDir>
#include <QDirIterator>

namespace pera_software::aidkit::qt {

DirectoryGuide::DirectoryGuide(QObject *parent)
	: QObject(parent)
{
}

void DirectoryGuide::walk(const QFileInfo &parentDirectory)
{
	constexpr QDir::Filters FILTERS = QDir::Files | QDir::Dirs | QDir::Hidden | QDir::System
		| QDir::NoDotAndDotDot | QDir::NoSymLinks;

	bool stop = false;
	QDirIterator directoryIterator(parentDirectory.filePath(), FILTERS, QDirIterator::NoIteratorFlags);
	while (directoryIterator.hasNext()) {
		directoryIterator.next();
		auto currentFileInfo = directoryIterator.fileInfo();

		// Visit either a directory or everything else is considered to be a file:

		if (currentFileInfo.isDir()) {
			Q_EMIT directoryVisited(parentDirectory, currentFileInfo, &stop);
			if (stop) {
				// Skip this directory
				continue;
			}
			walk(currentFileInfo);
			Q_EMIT directoryLeft(parentDirectory, currentFileInfo, &stop);
			if (stop) {
				// Skip the remaining entries in the same directory
				continue;
			}
		} else {
			Q_EMIT fileVisited(parentDirectory, currentFileInfo, &stop);
			if (stop) {
				// Skip the remaining files in the same directory
				continue;
			}
		}
	}
}

}

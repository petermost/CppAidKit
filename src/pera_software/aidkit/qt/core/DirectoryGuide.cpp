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

namespace pera_software { namespace aidkit { namespace qt {

DirectoryGuide::DirectoryGuide( QObject *parent )
	: QObject( parent ) {
}

void DirectoryGuide::walk( const QFileInfo &parentDirectory, DirectoryVisitor *visitor ) {
	const QDir::Filters FILTERS = QDir::Files | QDir::Dirs | QDir::Hidden | QDir::System
		| QDir::NoDotAndDotDot | QDir::NoSymLinks;

	QDirIterator directoryIterator( parentDirectory.filePath(), FILTERS, QDirIterator::NoIteratorFlags );
	while ( directoryIterator.hasNext() ) {
		directoryIterator.next();
		auto currentFileInfo = directoryIterator.fileInfo();

		// Visit either a directory or everything else is considered to be a file:

		if ( currentFileInfo.isDir() ) {
			if ( !visitor->visitDirectory( parentDirectory, currentFileInfo )) {
				// Skip this directory
				continue;
			}
			walk( currentFileInfo, visitor );
			if ( !visitor->leaveDirectory( parentDirectory, currentFileInfo )) {
				// Skip the remaining entries in the same directory
				continue;
			}
		} else {
			if ( !visitor->visitFile( parentDirectory, currentFileInfo )) {
				// Skip the remaining files in the same directory
				continue;
			}
		}
	}
}



DirectoryVisitor::DirectoryVisitor( QObject *parent )
	: QObject( parent ) {
}

DirectoryVisitor::~DirectoryVisitor() {
}

bool DirectoryVisitor::visitDirectory( const QFileInfo & /* parentDirectory */, const QFileInfo & /*currentDirectory */ ) {
	return true;
}

bool DirectoryVisitor::visitFile( const QFileInfo & /* parentDirectory */, const QFileInfo &/* currentFile */ ) {
	return true;
}

bool DirectoryVisitor::leaveDirectory( const QFileInfo &/* parentDirectory */, const QFileInfo & /* currentDirectory */ ) {
	return true;
}

} } }

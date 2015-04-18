#include "AidKit_Qt_DirectoryGuide.hpp"
#include <QDir>
#include <QDirIterator>
#include <QDebug>

namespace PERA { namespace AidKit { namespace Qt {

QList< QString > queryDirectoryEntries( const QString &directoryPath )
{
	QList< QString > entries;

	QDirIterator directoryIterator( directoryPath );
	while ( directoryIterator.hasNext() ) {
		entries.append( directoryIterator.next() );
	}
	return entries;
}



DirectoryVisitor::DirectoryVisitor( QObject *parent )
	: QObject( parent )
{
}

DirectoryVisitor::~DirectoryVisitor()
{
}

bool DirectoryVisitor::visitDirectory(const QFileInfo & /* parentDirectory */, const QFileInfo & /*currentDirectory */ )
{
	return true;
}

bool DirectoryVisitor::visitFile( const QFileInfo & /* parentDirectory */, const QFileInfo &/* currentFile */ )
{
	return true;
}

bool DirectoryVisitor::leaveDirectory( const QFileInfo &/* parentDirectory */, const QFileInfo & /* currentDirectory */)
{
	return true;
}



DirectoryGuide::DirectoryGuide( QObject *parent )
	: QObject( parent )
{
}

void DirectoryGuide::walk( const QFileInfo &parentDirectory, DirectoryVisitor *visitor )
{
	const QDir::Filters filters = QDir::Files | QDir::Dirs | QDir::Hidden | QDir::System
		| QDir::NoDotAndDotDot | QDir::NoSymLinks;

	QDirIterator directoryIterator( parentDirectory.filePath(), filters, QDirIterator::NoIteratorFlags );
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

} } }


#pragma once

#include <QObject>

class QString;
class QFileInfo;

namespace PERA {
	namespace AidKit {
		namespace Qt {

			class DirectoryVisitor : public QObject {
				Q_OBJECT
				public:
					DirectoryVisitor( QObject *parent = nullptr );
					virtual ~DirectoryVisitor();

				protected:
					friend class DirectoryGuide;

					virtual bool visitDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory );
					virtual bool visitFile( const QFileInfo &parentDirectory, const QFileInfo &currentFile );
					virtual bool leaveDirectory( const QFileInfo &parentDirectory, const QFileInfo &currentDirectory );
			};



			class DirectoryGuide : public QObject {
				Q_OBJECT
				public:
					DirectoryGuide( QObject *parent = nullptr );
					void walk(const QFileInfo &parentDirectory, DirectoryVisitor *visitor );

				signals:

				public slots:
			};

			QList< QString > queryDirectoryEntries( const QString &directoryPath );

		}
	}
}

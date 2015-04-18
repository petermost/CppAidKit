#pragma once

#include <QAction>

namespace PERA { namespace AidKit { namespace Qt {

class Action : public QAction {
	Q_OBJECT
	public:
		explicit Action( QObject *parent );
		Action( const QString &text, QObject* parent );
		Action( const QIcon &icon, const QString &text, QObject* parent );

	signals:

	public slots:
};

} } }

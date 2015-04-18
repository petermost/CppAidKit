#pragma once

#include "AidKit_Qt_Action.hpp"

namespace PERA { namespace AidKit { namespace Qt {

class QuitAction : public Action {
	Q_OBJECT
	public:
		explicit QuitAction( QObject *parent );
};

class OpenAction : public Action {
	Q_OBJECT
	public:
		explicit OpenAction( QObject *parent );
};

class PlayAction : public Action {
	Q_OBJECT
	public:
		explicit PlayAction( QObject *parent );
};

class PauseAction : public Action {
	Q_OBJECT
	public:
		explicit PauseAction( QObject *parent );
};

class PrintPreviewAction : public Action {
	Q_OBJECT
	public:
		explicit PrintPreviewAction( QObject *parent );
};

class PrintAction : public Action {
	Q_OBJECT
	public:
		explicit PrintAction( QObject *parent );
};

class GoNextAction : public Action {
	Q_OBJECT
	public:
		explicit GoNextAction( QObject *parent );
};

class GoPreviousAction : public Action {
	Q_OBJECT
	public:
		explicit GoPreviousAction( QObject *parent );
};

} } }

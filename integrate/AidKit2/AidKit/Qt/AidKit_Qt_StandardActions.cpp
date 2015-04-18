#include "AidKit_Qt_StandardActions.hpp"

// The icon names can be found at:
// http://standards.freedesktop.org/icon-naming-spec/icon-naming-spec-latest.html

namespace PERA { namespace AidKit { namespace Qt {

QuitAction::QuitAction( QObject *parent )
	: Action( parent )
{
	setText( tr( "&Quit" ));
	setIcon( QIcon::fromTheme( "application-exit" ));
	setShortcut( QKeySequence::Quit );
}


OpenAction::OpenAction( QObject *parent )
	: Action( parent )
{
	setText( tr( "&Open" ));
	setIcon( QIcon::fromTheme( "document-open" ));
	setShortcut( QKeySequence::Open );
}

PlayAction::PlayAction( QObject *parent )
	: Action( parent )
{
	setText( tr( "Play" ));
	setIcon( QIcon::fromTheme( "media-playback-start" ));
	// setShortcut( Qt::Key_Space );
}

PauseAction::PauseAction( QObject *parent )
	: Action( parent )
{
	setText( tr( "&Pause" ));
	setIcon( QIcon::fromTheme( "media-playback-pause" ));
	// setShortcut( Qt::Key_Space );
}

PrintPreviewAction::PrintPreviewAction( QObject *parent )
	: Action( parent )
{
	setText( tr( "Print Pre&view..." ));
	setIcon( QIcon::fromTheme( "document-print-preview" ));
}

PrintAction::PrintAction( QObject *parent )
	: Action( parent )
{
	setText( tr( "&Print..." ));
	setIcon( QIcon::fromTheme( "document-print" ));
	setShortcut( QKeySequence::Print );
}

GoNextAction::GoNextAction( QObject *parent )
	: Action( parent )
{
	setText( tr( "&Next" ));
	setIcon( QIcon::fromTheme( "go-next" ));
	setShortcut( QKeySequence::Forward );
}

GoPreviousAction::GoPreviousAction( QObject *parent )
	: Action( parent )
{
	setText( tr( "&Previous" ));
	setIcon( QIcon::fromTheme( "go-previous" ));
	setShortcut( QKeySequence::Back );
}


} } }

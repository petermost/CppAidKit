#pragma once

#include <pera_software/aidkit/AidKit.hpp>
#include <QAction>

namespace pera_software {
	namespace aidkit {
		namespace qt {

			class AIDKIT_EXPORT QuitAction : public QAction {
				Q_OBJECT
				public:
					explicit QuitAction( QObject *parent = nullptr );
			};
		}
	}
}

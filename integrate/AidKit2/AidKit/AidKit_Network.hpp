#pragma once

#include "AidKit_Platform.hpp"

#if defined( AIDKIT_LINUX )
	#include "Linux/AidKit_Linux_Network.hpp"

	namespace PERA {
	namespace AidKit {

		using Linux::ntoh16;
		using Linux::hton16;

		using Linux::ntoh32;
		using Linux::hton32;

		using Linux::ntoh64;
		using Linux::hton64;

	}
	}
#elif defined( AIDKIT_WINDOWS )
	#include "Windows/AidKit_Windows_Network.hpp"

	namespace PERA {
	namespace AidKit {

		using Windows::ntoh16;
		using Windows::hton16;

		using Windows::ntoh32;
		using Windows::hton32;

		using Windows::ntoh64;
		using Windows::hton64;
	}
	}
#endif

#pragma once

#include "../UtilityCpp.h"
#include "../DisableWarnings.hpp"
#include <string>
#include <exception>
#include <boost/exception/exception.hpp>

namespace std 
{
	UTILITYCPP_API wostream &operator << ( wostream &, const exception & );
}

		class UTILITYCPP_API Exception : public std::exception, public boost::exception
		{
			public:
				virtual const std::wstring Message() const = 0;

			private:
				virtual const char *what() const final;

				mutable std::string mMessage;
		};
	}
}

#pragma once

#include <exception>
#include <string>

namespace PERA {
	namespace AidKit {

		class Exception : public std::exception {
			public:
				Exception() noexcept;

				Exception( const std::string &what );

				virtual ~Exception() noexcept;

				virtual const char *what() const noexcept;

			private:
				std::string what_;
		};

	}
}

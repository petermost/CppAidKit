#pragma once

#include "AidKit_Platform.hpp"
#include "AidKit_Exception.hpp"
#include <string>

#define AIDKIT_STATIC_ASSERT( expression ) \
	static_assert(( expression ), #expression )

#define AIDKIT_VERIFY( expression ) \
	PERA::AidKit::checkAssertion( expression, #expression, __FILE__, __LINE__, __FUNCTION__ )

#ifdef AIDKIT_DEBUG
	#define AIDKIT_ASSERT( expression ) \
		AIDKIT_VERIFY( expression )
#else
	#define AIDKIT_ASSERT( expression )
#endif

namespace PERA {
	namespace AidKit {

		void checkAssertion( bool isSatisfied, const std::string &expression, const std::string &fileName,
				int lineNumber, const std::string &functionName );

		class AssertionException : public Exception {
			public:
				AssertionException( const std::string &expression, const std::string &fileName,
						int lineNumber, const std::string &functionName );

				~AssertionException() noexcept;

				const std::string &expression() const noexcept {
					return expression_;
				}

				const std::string &fileName() const	noexcept {
					return fileName_;
				}

				const std::string &functionName() const noexcept {
					return functionName_;
				}

				int lineNumber() const noexcept {
					return lineNumber_;
				}

			private:
				std::string expression_;
				std::string fileName_;
				int lineNumber_;
				std::string functionName_;
		};

	}
}

#include "AidKit_Debug.hpp"
#include <string>

using std::string;
using std::to_string;

namespace PERA { namespace AidKit {

void checkAssertion( bool isSatisfied, const string &expression, const string &fileName, int lineNumber, const string &functionName )
{
	if ( !isSatisfied )
		throw AssertionException( expression, fileName, lineNumber, functionName );
}

AssertionException::AssertionException( const string &expression, const string &fileName, int lineNumber, const string &functionName )
	: Exception( fileName + "(" + to_string( lineNumber ) + "): " + functionName + ": Assertion '" + expression + "' failed!" )
{
	expression_ = expression;
	fileName_ = fileName;
	lineNumber_ = lineNumber;
	functionName_ = functionName;
}

AssertionException::~AssertionException() noexcept
{
}

} }

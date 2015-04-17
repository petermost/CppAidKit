#include "stdafx.h"
#include "ErrNoException.hpp"

using namespace std;


ErrNoException ErrNoException::LastError()
{
	return ErrNoException( errno );
}

ErrNoException::ErrNoException( int errNo, const wstring &errorMessage )
{
	mErrNo = errNo;
	if ( !errorMessage.empty() )
		mErrorMessage = errorMessage;
	else
		mErrorMessage = _wcserror( errNo );
}

const wstring ErrNoException::Message() const
{
	return mErrorMessage;
}

} }

#pragma once

#include "../UtilityCpp.h"
#include <exception>
#include <string>
#include "Exception.hpp"

		class UTILITYCPP_API ErrNoException : public Exception
		{
			public:
				static ErrNoException LastError();

				ErrNoException( int errNo = 0, const std::wstring &errorMessage = L"" );

				int ErrNo() const
					{ return mErrNo; }

				virtual const std::wstring Message() const override;

			private:
				int mErrNo;
				std::wstring mErrorMessage;
		};

		template < typename T >
			class ErrNoExceptionTemplate : public ErrNoException
			{
				public:
					static ErrNoExceptionTemplate LastError()
					{
						return ErrNoExceptionTemplate( errno );
					}

					ErrNoExceptionTemplate( int errNo = 0, const std::wstring &errorMessage = L"" )
						: ErrNoException( errNo, errorMessage )
					{
					}
			};
	}
}

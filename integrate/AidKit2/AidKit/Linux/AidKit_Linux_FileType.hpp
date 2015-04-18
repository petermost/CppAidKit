#pragma once

#include <string>
#include <magic.h>
#include <exception>

namespace PERA { namespace AidKit { namespace Linux {

class FileType {
	public:
		FileType();
		~FileType();

		const std::string determineFileType( const std::string &fileName );

	private:
		magic_t _cookie;
};

class FileTypeException : public std::exception {
	public:
		FileTypeException( magic_t magicCookie );
		FileTypeException( int errorCode, const std::string &errorMessag );
		virtual ~FileTypeException()
			throw();

		virtual const char *what() const
			throw();

		int errorCode() const;
		const std::string &errorMessage() const;

	private:
		int _errorCode;
		std::string _errorMessage;
};

} } }

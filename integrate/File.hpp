#pragma once

#include <UtilityCpp/UtilityCpp.h>
#include <UtilityCpp/Boost/FileSystem.hpp>
#include <UtilityCpp/Exceptions/ErrNoException.hpp>
#include <memory>
#include <string>
#include <stdio.h>
#include <boost/throw_exception.hpp>

		typedef Exceptions::ErrNoExceptionTemplate< class File > FileException;

		class UTILITYCPP_API FileNotFoundException : public FileException
		{
			public:
				FileNotFoundException( const boost::filesystem::path &fileName );

				const boost::filesystem::path &FileName() const;

			private:
				boost::filesystem::path mFileName;
		};

		class UTILITYCPP_API EndOfFileException : public FileException
		{
			public:
				EndOfFileException();
		};

		class UTILITYCPP_API File
		{
			public:
				typedef int64_t length_t;

				typedef int64_t position_t;

				enum class open_mode
				{
					read,
					write,
					append,
					read_write,
					write_read,
					append_read_write
				};

				enum class origin
				{
					begin = SEEK_SET,
					current = SEEK_CUR,
					end = SEEK_END
				};

				enum class buffer_mode
				{
					full = _IOFBF,
					line = _IOLBF,
					none = _IONBF
				};

				File();
				File( std::shared_ptr< FILE > file );
				File( const boost::filesystem::path &fileName, open_mode mode );
				virtual ~File();

				// Open/Close a file:

				void open( const boost::filesystem::path &fileName, open_mode mode );
				void close();

				// Set the buffer:

				void set_buffer( void *buffer, buffer_mode mode, size_t size );

				// Write/Read characters:

				virtual int put( int c )
				{
					if (( c = _putc_nolock( c, mFile.get() )) == EOF && error() )
						BOOST_THROW_EXCEPTION( FileException::LastError() );
					else
						return c;
				}

				virtual int get()
				{
					int c;

					if (( c = _getc_nolock( mFile.get() )) == EOF && error() )
						BOOST_THROW_EXCEPTION( FileException::LastError() );
					else
						return c;
				}
				
				// Write strings:

				void put( const std::string &str );
				void put( const std::wstring &str );

				int print( const char format[], ... );
				int print( const wchar_t format[], ... );

				virtual size_t write( const void *buffer, size_t size, size_t count )
				{
					size_t writeCount;

					if (( writeCount = _fwrite_nolock( buffer, size, count, mFile.get() )) < count && error() )
						BOOST_THROW_EXCEPTION( FileException::LastError() );
					else
						return writeCount;
				}

				// Write/Read binary data:

				size_t write( const void *buffer, size_t size )
				{
					return write( buffer, 1, size );
				}

				virtual size_t read( void *buffer, size_t size, size_t count )
				{
					size_t readCount;

					if (( readCount = _fread_nolock( buffer, size, count, mFile.get() )) < count && error() )
						BOOST_THROW_EXCEPTION( FileException::LastError() );
					else
						return readCount;
				}

				size_t read( void *buffer, size_t size )
				{
					return read( buffer, 1, size );
				}

				// Positioning:

				virtual position_t tell();
				virtual void seek( position_t position, origin origin = origin::begin );
				virtual void rewind();

				void flush();

				bool error() const
					{ return ferror( mFile.get() ) != 0; }

				bool eof() const
					{ return feof( mFile.get() ) != 0; }

				const boost::filesystem::path &name() const;

				virtual length_t length() const;

			private:
				boost::filesystem::path mName;
				std::shared_ptr< FILE > mFile;
		};
	}
}

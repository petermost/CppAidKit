// Copyright 2015 Peter Most, PERA Software Solutions GmbH
//
// This file is part of the CppAidKit library.
//
// CppAidKit is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CppAidKit is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <pera_software/aidkit/Platform.hpp>

#if defined( AIDKIT_GCC )
	#if defined( AIDKIT_MINGW )
		#define AIDKIT_UNLOCKED_PUTC   _putc_nolock
		#define AIDKIT_UNLOCKED_PUTWC  _putwc_nolock
		#define AIDKIT_UNLOCKED_GETC   _getc_nolock
		#define AIDKIT_UNLOCKED_GETWC  _fgetwc_nolock
		#define AIDKIT_UNLOCKED_FWRITE _fwrite_nolock
		#define AIDKIT_UNLOCKED_FREAD  _fread_nolock

		// These *_nolock functions exist in the mingw491 stdio.h but result in a linker error!

		#define AIDKIT_UNLOCKED_FSEEK  ::_fseeki64
		#define AIDKIT_UNLOCKED_FTELL  ::_ftelli64
		#define AIDKIT_UNLOCKED_FFLUSH ::std::fflush
		#define AIDKIT_UNLOCKED_FCLOSE ::std::fclose

		// Missing unlocked functions:

		#define AIDKIT_UNLOCKED_FOPEN    ::std::fopen
		#define AIDKIT_UNLOCKED_FERROR   ::std::ferror
		#define AIDKIT_UNLOCKED_FEOF     ::std::feof
		#define AIDKIT_UNLOCKED_FPUTS    ::std::fputs
		#define AIDKIT_UNLOCKED_FPUTWS   ::std::fputws
		#define AIDKIT_UNLOCKED_REWIND   ::std::rewind
		#define AIDKIT_UNLOCKED_FGETPOS  ::std::fgetpos
		#define AIDKIT_UNLOCKED_FSETPOS  ::std::fsetpos
		#define AIDKIT_UNLOCKED_CLEARERR ::std::clearerr
	#else
		#define AIDKIT_UNLOCKED_PUTC     putc_unlocked
		#define AIDKIT_UNLOCKED_PUTWC    putwc_unlocked
		#define AIDKIT_UNLOCKED_GETC     getc_unlocked
		#define AIDKIT_UNLOCKED_GETWC    getwc_unlocked
		#define AIDKIT_UNLOCKED_FWRITE   fwrite_unlocked
		#define AIDKIT_UNLOCKED_FREAD    fread_unlocked
		#define AIDKIT_UNLOCKED_FPUTS    fputs_unlocked
		#define AIDKIT_UNLOCKED_FPUTWS   fputws_unlocked
		#define AIDKIT_UNLOCKED_FFLUSH   fflush_unlocked
		#define AIDKIT_UNLOCKED_FERROR   ferror_unlocked
		#define AIDKIT_UNLOCKED_FEOF     feof_unlocked
		#define AIDKIT_UNLOCKED_CLEARERR clearerr_unlocked

		// Missing unlocked functions:

		#define AIDKIT_UNLOCKED_FOPEN   ::std::fopen
		#define AIDKIT_UNLOCKED_FCLOSE  ::std::fclose
		#define AIDKIT_UNLOCKED_FTELL   ::std::ftell
		#define AIDKIT_UNLOCKED_FSEEK   ::std::fseek
		#define AIDKIT_UNLOCKED_REWIND  ::std::rewind
		#define AIDKIT_UNLOCKED_FGETPOS ::std::fgetpos
		#define AIDKIT_UNLOCKED_FSETPOS ::std::fsetpos
	#endif
#elif defined( AIDKIT_MSVC )
	#define AIDKIT_UNLOCKED_PUTC   _putc_nolock
	#define AIDKIT_UNLOCKED_PUTWC  _putwc_nolock
	#define AIDKIT_UNLOCKED_GETC   _getc_nolock
	#define AIDKIT_UNLOCKED_FWRITE _fwrite_nolock
	#define AIDKIT_UNLOCKED_FREAD  _fread_nolock
	#define AIDKIT_UNLOCKED_FTELL  _ftelli64_nolock
	#define AIDKIT_UNLOCKED_FSEEK  _fseeki64_nolock
	#define AIDKIT_UNLOCKED_FFLUSH _fflush_nolock
	#define AIDKIT_UNLOCKED_FCLOSE _fclose_nolock

	// Missing unlocked functions:

	#define AIDKIT_UNLOCKED_FOPEN    ::std::fopen
	#define AIDKIT_UNLOCKED_GETWC    ::std::getwc
	#define AIDKIT_UNLOCKED_FERROR   ::std::ferror
	#define AIDKIT_UNLOCKED_FEOF     ::std::feof
	#define AIDKIT_UNLOCKED_FPUTS    ::std::fputs
	#define AIDKIT_UNLOCKED_FPUTWS   ::std::fputws
	#define AIDKIT_UNLOCKED_REWIND   ::std::rewind
	#define AIDKIT_UNLOCKED_FGETPOS  ::std::fgetpos
	#define AIDKIT_UNLOCKED_FSETPOS  ::std::fsetpos
	#define AIDKIT_UNLOCKED_CLEARERR ::std::clearerr
#else
	#error Missing unlocked file functions!
#endif
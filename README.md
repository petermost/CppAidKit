CppAidKit
=========

A C++ library which contains C++11/Qt aid classes. The documentation is for now lacking because it is foremost a privatly used library. But some notable highlights:

##Standard classes:
- [file](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/basic_file.hpp): A RAII wrapper around `std::FILE *` functions and it's wide character versions. It also returns or throws a `std::error_code` instead of setting `std::errno`.
- [file_error](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/file_error.hpp): A customized `std::error_code` for the above mentionded file class.
- [enum_class](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/enum_class.hpp): A Java inspired enum class which allows searching/printing etc.
- [unicode.hpp](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/unicode.hpp): Allows converting UTF-8 strings to wstrings and vice versa.
- [errno.hpp](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/errno.hpp): Create a `std::error_code` from errno.
- [system_error](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/system_error.hpp): Utility functions for throwing a `std::system_error` when an `std::error_code` was returned.

##Qt classes:
- [DirectoryGuide/DirectoryVisitor](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/qt/core/DirectoryGuide.hpp): Allow traversing a directory tree.
- [hton/ntoh](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/qt/net/Endian.hpp): Functions to convert from host to network byte order and vice versa based on the size of the type.

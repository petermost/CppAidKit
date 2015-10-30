CppAidKit
=========

A C++ library which contains C++11/Qt aid classes. The documentation is for now lacking because it is foremost a privatly used library. But some notable highlights:

##Standard classes:
- enum_class: A Java inspired enum class which allows searching/printing etc.
- unicode.hpp: Allow converting UTF-8 strings to wstrings and vice versa.
- errno.hpp: Create an `std::error_code` from errno.
- basic_file.hpp/file.hpp: A RAII wrapper around `std::FILE *` functions and it's wide character versions.
- file_error.hpp: A customized `std::error_code` for file errors.
- system_error.hpp: Utility functions for throwing a `std::system_error` when an `std::error_code` was returned.

##Qt classes:
- DirectoryGuide/DirectoryVisitor: Allow traversing a directory tree.
- Endian.hpp: ntoh/hton which do the correct byte swapping based on the size of the integer.

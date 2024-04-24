C++ AidKit
==========

A C++ library which contains C++20/Qt/CMake aid classes/scripts. The documentation is somewhat lacking, but all classes have unittests and should therefore function as documentation.

If somebody else, besides me :wink:, should actually use the AidKit-library, let me know and I start working on the documentation.

Some notable classes:
## Standard classes:
- [data_mutex](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/concurrent/data_mutex.hpp): Wrapper around a thread shared resource which ensures at comple time, when accessing the resource, the corresponding mutex is locked.
- [file](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/basic_file.hpp): A RAII wrapper around `std::FILE *` functions. It also returns or throws a `std::error_code` instead of setting `std::errno`.
- [file_error](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/file_error.hpp): A customized `std::error_code` for the above mentionded file class.
- [file_ptr](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/file_ptr.hpp): A simple alias for a `std::unique_ptr<>` with a custom deleter which closes the `std::FILE *`.
- [enum_class](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/enum_class.hpp): A Java inspired enum class which allows searching/printing etc.
- [enum_flags](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/enum_flags.hpp): Define flags like enums and test it with normal bit test operations.
- [errno.hpp](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/errno.hpp): Create a `std::error_code` from errno.
- [system_error](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/io/system_error.hpp): Utility functions for throwing a `std::system_error` when an `std::error_code` was returned.

## Qt classes:
- [DirectoryGuide/DirectoryVisitor](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/qt/core/DirectoryGuide.hpp): Allow traversing a directory tree.
- [hton/ntoh](https://github.com/petermost/CppAidKit/blob/master/src/pera_software/aidkit/qt/net/Endian.hpp): Functions to convert from host to network byte order and vice versa based on the size of the type.

## CMake scripts:
- [CMakeLists.txt](https://github.com/petermost/CppAidKit/blob/master/CMakeLists.txt): A (hopefully) exemplary CMake build script for a library build.
- [output_options.cmake](https://github.com/petermost/CppAidKit/blob/master/cmake/output_options.cmake): Build all targets into the build directory.
- [rpath_options.cmake](https://github.com/petermost/CppAidKit/blob/master/cmake/rpath_options.cmake): Setup `rpath` so shared libraries are searched in the current directory (and `./lib` for Qt libraries).

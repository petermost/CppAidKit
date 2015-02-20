# Copyright 2014 Peter Most, PERA Software Solutions GmbH
#
# This file is part of the CppAidKit library.
#
# CppAidKit is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# CppAidKit is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with CppAidKit. If not, see <http://www.gnu.org/licenses/>.

TARGET = AidKit

TEMPLATE = lib

CONFIG += c++11

QT       += widgets testlib

DEFINES += AIDKIT_LIBRARY_BUILD

HEADERS +=\
	headers/pera_software/aidkit/AidKit.hpp \
	headers/pera_software/aidkit/qt/MainWindow.hpp \
	headers/pera_software/company/PERA.hpp \
	headers/pera_software/company/AboutDialog.hpp \
	headers/pera_software/company/Application.hpp

SOURCES += \
	sources/pera_software/aidkit/AidKit.cpp \
	sources/pera_software/aidkit/qt/MainWindow.cpp \
	sources/pera_software/company/PERA.cpp \
	sources/pera_software/company/AboutDialog.cpp \
	sources/pera_software/company/Application.cpp

RESOURCES += \
	resources/pera_software/Resources.qrc

INCLUDEPATH += ./headers

unix {
	target.path = /usr/lib
	INSTALLS += target
}

OTHER_FILES += \
	lgpl.txt


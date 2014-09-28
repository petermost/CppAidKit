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
    headers/pera_software/aidkit/qt/Images.hpp \
    headers/pera_software/aidkit/qt/AboutDialog.hpp \
    headers/pera_software/aidkit/qt/MainWindow.hpp \
    headers/pera_software/aidkit/qt/Application.hpp \
    headers/pera_software/aidkit/qt/AidKit.hpp

SOURCES += \
    sources/pera_software/aidkit/qt/AboutDialog.cpp \
    sources/pera_software/aidkit/qt/Images.cpp \
    sources/pera_software/aidkit/qt/MainWindow.cpp \
    sources/pera_software/aidkit/qt/Application.cpp \
    sources/pera_software/aidkit/qt/AidKit.cpp

RESOURCES += \
    AidKitImages.qrc

INCLUDEPATH += ./headers

unix {
    target.path = /usr/lib
    INSTALLS += target
}

OTHER_FILES += \
    lgpl.txt


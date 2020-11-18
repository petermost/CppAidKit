// Copyright 2020 Peter Most, PERA Software Solutions GmbH
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

#include "Path.hpp"
#include "Strings.hpp"
#include <cstring>

namespace pera_software::aidkit::qt {

static const QChar DRIVE_SEPARATOR(':'_qc);
static const QChar DIRECTORY_SEPARATOR_LINUX('/'_qc);
static const QChar DIRECTORY_SEPARATOR_WINDOWS('\\'_qc);
static const QChar EXTENSION_SEPARATOR('.'_qc);

template <typename T>
	int wrapIndex(const QVector<T> &container, int index)
	{
		return index >= 0 ? index : container.size() + index;
	}

static QString prependSeparator(QString str, QChar separator)
{
	if (!str.isEmpty() && str.front() != separator)
		return separator + str;
	else
		return str;
}

static QString appendSeparator(QString str, QChar separator)
{
	if (!str.isEmpty() && str.back() != separator)
		return str + separator;
	else
		return str;
}

static QString addDriveSeparator(QString drive)
{
	return appendSeparator(drive, DRIVE_SEPARATOR);
}

static QString addDirectorySeparator(QString directory)
{
	return appendSeparator(directory, DIRECTORY_SEPARATOR_LINUX);
}

static QString addExtensionSeparator(QString extension)
{
	return prependSeparator(extension, EXTENSION_SEPARATOR);
}

Path::Path(QStringView path)
{
	QChar c;
	bool isEnd;
	QStringView::size_type begin = 0, end = 0;

	// Extract the drive and the directories:

	for (end = 0; end < path.length(); ++end) {
		if ((c = path.at(end)) == DRIVE_SEPARATOR) {
			drive_ = path.mid(begin, end - begin + 1).toString();
			begin = end + 1;
		} else if (c == DIRECTORY_SEPARATOR_LINUX || c == DIRECTORY_SEPARATOR_WINDOWS) {
			directories_.append(path.mid(begin, end - begin + 1).toString());
			begin = end + 1;
		}
	}
	// Extract the name and the extensions:

	bool hasName = false;
	for (end = begin; end < path.length(); ++end) {
		if ((isEnd = (end == path.length() - 1)) || path.at(end) == EXTENSION_SEPARATOR) {
			if (!hasName) {
				name_ = path.mid(begin, isEnd ? end - begin + 1 : end - begin).toString();
				hasName = true;
			} else {
				extensions_.append(path.mid(begin, isEnd ? end - begin + 1 : end - begin).toString());
			}
			begin = end;
		}
	}
}

void Path::setDrive()
{
	drive_.clear();
}

void Path::setDrive(QString drive)
{
	drive_ = addDriveSeparator(drive);
}

QString Path::drive() const
{
	return drive_;
}

QString Path::directory() const
{
	return toString(Directories);
}

QString Path::directory(int index) const
{
	return directories_.value(wrapIndex(directories_, index));
}

QString Path::name() const
{
	return name_;
}

QString Path::extension() const
{
	return extensionAt(-1);
}

QString Path::extensionAt(int index) const
{
	return extensions_.value(wrapIndex(extensions_, index));
}

QString Path::toString() const
{
	return toString(Drive | Directories | Name | Extensions);
}

QString Path::toString(ToStringOptions options) const
{
	QString path;

	if (options & ToStringOption::Drive) {
		path.append(drive_);
	}
	if (options & ToStringOption::Directories) {
		for (auto &directory : directories_)
			path.append(directory);
	}
	if (options & ToStringOption::Name) {
		path.append(name_);
	}
	if (options & ToStringOption::Extensions) {
		for (auto &extension : extensions_)
			path.append(extension);
	}
	return path;
}

/*
//=============================================================================
CFilePath::~CFilePath(void)
//=============================================================================
{
}

//=============================================================================
const char *CFilePath::operator=(const char Path[])
//=============================================================================
{
	SplitPath(Path, &my_Drive, &my_Directories, &my_Name, &my_Extension);
	return (CFilePath::Path());
}

//=============================================================================
void CFilePath::ChangeDrive(const char Drive[])
//=============================================================================
{
	my_Drive = Drive;
}

//=============================================================================
void CFilePath::ChangeDirectoryAt(int Position, const char Directory[])
//=============================================================================
{
	vector<QString>::size_type Index = (Position >= 0) ? Position : my_Directories.size() + Position;

	my_Directories.at(Index) = Directory;
}

//=============================================================================
void CFilePath::ChangeName(const char Name[])
//=============================================================================
{
	my_Name = Name;
}

//=============================================================================
void CFilePath::ChangeExtension(const char Extension[])
//=============================================================================
{
	my_Extension = Extension;
}

//=============================================================================
const char *CFilePath::Path(void)
//=============================================================================
{
	MergePath(my_szPath, my_Drive, my_Directories, my_Name, my_Extension);
	return (my_szPath);
}

//=============================================================================
const char *CFilePath::Directory(void)
//=============================================================================
{
	MergePath(my_szDirectory, my_Drive, my_Directories, QString(), QString());
	return (my_szDirectory);
}

//=============================================================================
const char *CFilePath::Drive(void) const
//=============================================================================
{
	return (my_Drive.c_str());
}

//=============================================================================
const char *CFilePath::DirectoryAt(int Position) const
//=============================================================================
{
	vector<QString>::size_type Index = (Position >= 0) ? Position : my_Directories.size() + Position;

	return (my_Directories.at(Index).c_str());
}

//=============================================================================
const char *CFilePath::Name(void) const
//=============================================================================
{

	return (my_Name.c_str());
}

//=============================================================================
const char *CFilePath::Extension(void) const
//=============================================================================
{
	return (my_Extension.c_str());
}

//=============================================================================
CFilePath::operator const char_t *(void)
//=============================================================================
{
	return (Path());
}
*/

}

// Copyright 2021 Peter Most, PERA Software Solutions GmbH
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

#include "main.hpp"
#include <string_view>

using namespace std;
using namespace filesystem;
using namespace pera_software::aidkit;

extern "C" pera_software::aidkit::exit_result aidkit_main(std::filesystem::path name,
	std::vector<std::string> arguments, std::vector<std::pair<std::string, std::string>> environment);

namespace pera_software::aidkit {

int g_argc;
char **g_argv;

}

static pair<string, string> splitEnvironmentEntry(string_view entry)
{
	pair<string, string> splitEntry;

	if (auto pos = entry.find('='); pos != string_view::npos) {
		splitEntry.first = entry.substr(0, pos);
		splitEntry.second = entry.substr(pos + 1);
	}
	return splitEntry;
}

static vector<pair<string, string>> splitEnvironmentEntries(char *envp[])
{
	const char *entry;
	vector<pair<string, string>> environment;

	for (size_t i = 0; (entry = envp[i]) != nullptr; ++i) {
		environment.emplace_back(splitEnvironmentEntry(entry));
	}
	return environment;
}

int main(int argc, char *argv[], char *envp[])
{
	g_argc = argc;
	g_argv = argv;

	path name(argv[0]);
	vector<string> arguments(&argv[1], &argv[argc]);
	vector<pair<string, string>> environment(splitEnvironmentEntries(envp));

	return static_cast<int>(aidkit_main(name, arguments, environment));
}

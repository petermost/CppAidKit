#include "stdafx.h"
#include "Dumper.hpp"


using namespace std;

using boost::io::ios_base_all_saver;

namespace { namespace Debugging {

DumperOutput::DumperOutput( wostream &stream )
	: mStream( stream )
{
}

void DumperOutput::AddName( const wchar_t name[] )
{
	mStream << name << L" = ";
}


void DumperOutput::AddSeparator()
{
	mStream << L", ";
}

void DumperOutput::BeginCollection()
{
	mStream << L'[';
}

void DumperOutput::EndCollection()
{
	mStream << L']';
}

void DumperOutput::BeginValue()
{
	mStream << L'<';
}

void DumperOutput::EndValue()
{
	mStream << L'>';
}

void DumperOutput::BeginStruct()
{
	mStream << L'{';
}

void DumperOutput::EndStruct()
{
	mStream << L'}';
}



DumperFormatSetter::DumperFormatSetter( wostream &stream ) 
	: mStreamStateSaver( stream )
{
	stream << hex << uppercase;
}

} }

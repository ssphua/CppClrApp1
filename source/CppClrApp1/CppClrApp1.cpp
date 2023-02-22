// CppClrApp1.cpp : main project file.

#include "stdafx.h"
#include <stdio.h>

using namespace System;
using namespace System::Data::SqlClient;
using namespace System::IO;

int main(array<String ^> ^args)
{
	SqlConnection ^connection;
	SqlCommand ^command1, ^command2;
	SqlDataReader ^reader;
	try
	{
		connection = gcnew SqlConnection("");

		command1 = gcnew SqlCommand(Console::ReadLine(), connection);
		command1->ExecuteNonQuery(); //CWEID 89
		reader = command1->ExecuteReader(); //CWEID 89

		File::Delete(reader->GetString(0)); //CWEID 73
		File::Delete((String ^)reader[0]); //CWEID 73
		String ^str = reader->GetString(0);
		File::Delete(gcnew String(str->ToCharArray())); //CWEID 73

		command2 = gcnew SqlCommand(args[0], connection);
		command2->ExecuteNonQuery(); //CWEID 89

		char buf[128];
		scanf("%.128s", buf);
		printf(buf); //CWEID 134
	}
	catch(Exception ^e)
	{
		Console::WriteLine(e);
	}
	finally
	{
		if(connection) connection->~SqlConnection();
		if(command1) command1->~SqlCommand();
		if(command2) command2->~SqlCommand();
		if(reader) reader->~SqlDataReader();
	}

	String ^taint = Console::ReadLine();
	File::Delete(taint); //CWEID 73
	array<Char> ^sep = { ':' };
	File::Delete(taint->Split(sep)[0]); //CWEID 73
}

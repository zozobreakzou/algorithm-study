// iteratorFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <queue>
#include <string>
#include <iostream>

#include <Windows.h>

using std::queue;
using std::string;

string joinPath(const string& path1, const string& path2)
{
	string path = path1;
	path.append("\\");
	path.append(path2);
	return path;
}

void iterateFile(const char* szFolder)
{
	queue<string> visitedFolder;
	
	std::cout << szFolder << std::endl;
	visitedFolder.push(szFolder);

	while ( !visitedFolder.empty() )
	{
		string strFolder = visitedFolder.front();
		visitedFolder.pop();

		WIN32_FIND_DATA findData;
		HANDLE hFindFile = ::FindFirstFile( joinPath(strFolder, "*.*").c_str() , &findData );
		if ( hFindFile != INVALID_HANDLE_VALUE )
		{
			do 
			{
				if ( findData.cFileName[0] == '.' )
					continue;

				string fullName = joinPath(strFolder, findData.cFileName);
				std::cout << fullName.c_str() << std::endl;

				if ((findData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) != 0)
					visitedFolder.push(fullName);

			} while ( FindNextFile(hFindFile, &findData) );
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	iterateFile("C:\\Program Files");

	return 0;
}


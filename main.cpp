#include "dxbc_inspect.h"
#include "dxbc_disassemble.h"
#include <windows.h>

#include <cstdio>

using namespace DXBC;
using namespace std;


int main(int argc, const char **argv)
{
	if( argc == 1)
	{
		printf("Not enough parameters\n");
		return 1;
	}

	HANDLE hFile = CreateFile(argv[1], GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if( hFile == INVALID_HANDLE_VALUE )
	{
		printf("Could not open file: \"%s\"", argv[1]);
		return 1;
	}

	DWORD fileSize = GetFileSize(hFile, 0);
	if (fileSize == 0)
	{
		printf("FileSize is 0");
		return 1;
	}

	char *shaderHex = new char[fileSize];

	ReadFile(hFile, shaderHex, fileSize, 0, 0);

	CloseHandle(hFile);


	DXBCFile dxbcFile(shaderHex, fileSize);


	//printf("Disassembly: \n%s\n", disassembly.c_str());

	delete[] shaderHex;

	return 0;
}
 
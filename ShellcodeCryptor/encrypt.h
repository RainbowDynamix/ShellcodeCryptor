#pragma once
#include <Windows.h>

VOID CryptFile(char* inFile, char* method, char* key);
VOID XorByInputKey(IN PBYTE pShellcode, IN SIZE_T sShellcodeSize, IN PBYTE bKey, IN SIZE_T sKeySize);
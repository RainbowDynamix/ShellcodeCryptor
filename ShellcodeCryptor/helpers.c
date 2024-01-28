#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

void printShellcode(PBYTE pShellcode, SIZE_T sShellcode) {
	for (size_t i = 0; i < sShellcode; i++)
	{
		printf("\\0x%x", pShellcode[i]);
	}
}


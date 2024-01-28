#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#include "encrypt.h"

VOID CryptFile(char* inFile, char* method, char* key) {
	// XOR, Encrypt or Decrypt
	if (method == "xor") 
	{
		printf("Encryption key: %s\n", key);
		char* file = inFile;
		size_t filenameSize = strlen(file);

		char* fname = (char*)malloc((filenameSize + 1) * sizeof(char));

		// Allocate memory for file name dynamically
		strcpy_s(fname, filenameSize + 1, file);

		FILE* scFile;
		if (fopen_s(&scFile, fname, "rb") != 0) {
			printf("[!] Error opening file\n");
			exit(-1);
		}

		// Determine file size
		fseek(scFile, 0, SEEK_END);
		long fileSize = ftell(scFile);
		fseek(scFile, 0, SEEK_SET);

		char* scBuffer = (char*)malloc(fileSize);

		// Read bytes into shellcode buffer
		fread(scBuffer, 1, fileSize, scFile);

		fclose(scFile);
		free(fname);

		XorByInputKey(scBuffer, sizeof(scBuffer), key, sizeof(key));

		// Specify the file name
		const char* filename = "XOREncrypted.bin";

		// Open the file in binary write mode using fopen_s
		FILE* eFile;
		if (fopen_s(&eFile, filename, "wb") != 0) {
			fprintf(stderr, "Error opening file %s for writing\n", filename);
			exit(-1); // Return an error code
		}

		// Get the size of the buffer
		size_t bufferSize = sizeof(scBuffer) / 2;

		// Write the contents of the buffer to the file using a loop
		for (size_t i = 0; i < bufferSize; i++) {
			// Write the byte to the file
			fputc(scBuffer[i], eFile);
		}

		// Close the file
		fclose(eFile);

		printf("[+] XOR-encrypted file written to : XOREncrypted.bin\n");
	}
	
}

VOID XorByInputKey(IN PBYTE pShellcode, IN SIZE_T sShellcodeSize, IN PBYTE bKey, IN SIZE_T sKeySize) {
	for (size_t i = 0, j = 0; i < sShellcodeSize; i++, j++) {
		// if end of the key, start again 
		if (j > sKeySize)
		{
			j = 0;
		}
		pShellcode[i] = pShellcode[i] ^ bKey[j];
	}
}
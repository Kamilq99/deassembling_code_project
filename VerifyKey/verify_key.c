// verify_key.c
#include <stdbool.h>
#include <string.h>

__declspec(dllexport) bool verify_license_key(const char* key) {
    bool is_valid = false;

    // Assembly comparison - for simplicity, we check against a fixed key "ABCD-1234"
    __asm__ (
        "movl $0, %%eax\n"            // Set is_valid to false
        "movl %[key], %%esi\n"        // Load the address of key into esi
        "movl $0x34433241, %%ebx\n"   // "ABCD" as a number in the register
        "movl (%%esi), %%ecx\n"       // Load the first 4 bytes of the key
        "cmpl %%ebx, %%ecx\n"         // Compare if the first 4 bytes are "ABCD"
        "jne end\n"                   // Jump to end if different

        "movl $0x3732312d, %%ebx\n"   // "-1234" as a number in the register
        "movl 4(%%esi), %%ecx\n"      // Load the next 4 bytes
        "cmpl %%ebx, %%ecx\n"         // Compare if it is "-1234"
        "jne end\n"                   // Jump to end if different

        "movl $1, %%eax\n"            // Set is_valid to true (key is correct)
        "end:\n"
        "movl %%eax, %[is_valid]\n"   // Store the result in the is_valid variable

        : [is_valid] "=r" (is_valid)   // Output: is_valid value
        : [key] "r" (key)             // Input: key
        : "eax", "ebx", "ecx", "esi"  // Registers used
    );

    return is_valid;
}
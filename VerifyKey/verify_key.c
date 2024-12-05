#include <stdbool.h>

__declspec(dllexport) bool verify_license_key(const char* key) {
    bool is_valid = false;

    __asm__ __volatile__ (
        "xor %%eax, %%eax\n"             // Zainicjuj eax (is_valid = false)
        "mov %[key], %%esi\n"            // Przenieś adres key do esi
        "movl $0x34433241, %%ebx\n"      // Załaduj wartość 'ABCD' do ebx
        "movl (%%esi), %%ecx\n"          // Załaduj pierwsze 4 bajty z *key do ecx
        "cmpl %%ebx, %%ecx\n"            // Porównaj ecx z ebx
        "jne 1f\n"                       // Skocz do etykiety 1, jeśli różne

        "movl $0x3732312d, %%ebx\n"      // Załaduj wartość '-1234' do ebx
        "movl 4(%%esi), %%ecx\n"         // Załaduj kolejne 4 bajty z key do ecx
        "cmpl %%ebx, %%ecx\n"            // Porównaj ecx z ebx
        "jne 1f\n"                       // Skocz do etykiety 1, jeśli różne

        "movl $1, %%eax\n"               // Ustaw eax (is_valid = true)
        "jmp 2f\n"                       // Skocz do etykiety 2

        "1:\n"
        "xor %%eax, %%eax\n"             // Zeruj eax (is_valid = false)

        "2:\n"
        "movb %%al, %[is_valid]\n"       // Zapisz al do is_valid

        : [is_valid] "=r" (is_valid)     // Wyjście
        : [key] "r" (key)                // Wejście
        : "eax", "ebx", "ecx", "esi"     // Zmienione rejestry
    );

    return is_valid;
}
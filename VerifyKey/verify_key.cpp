#include <cstring>
#include <windows.h>

// Funkcja eksportowana z DLL, która weryfikuje klucz
extern "C" __declspec(dllexport) bool ValidateKey(const char* key) {
    // Zdefiniowany stały klucz licencyjny
    const char* hardcodedKey = "SECRET-1234";

    // Porównanie klucza wejściowego z kluczem stałym
    return strcmp(key, hardcodedKey) == 0;
}

// Punkt wejścia dla DLL
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        // Można dodać inicjalizację lub logikę dla procesu
        break;
    case DLL_THREAD_ATTACH:
        // Inicjalizacja dla nowego wątku
        break;
    case DLL_THREAD_DETACH:
        // Sprzątanie po zakończeniu wątku
        break;
    case DLL_PROCESS_DETACH:
        // Sprzątanie po zakończeniu procesu
        break;
    }
    return TRUE;
}

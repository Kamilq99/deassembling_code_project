#include <cstring>
#include <windows.h>

// Exported function from DLL that verifies a key
extern "C" __declspec(dllexport) bool ValidateKey(const char* key) {
    // Defined constant license key
    const char* hardcodedKey = "SECRET-1234";

    // Compare the input key with the constant key
    return strcmp(key, hardcodedKey) == 0;
}

// Entry point for the DLL
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        // Initialization or logic for the process can be added here
        break;
    case DLL_THREAD_ATTACH:
        // Initialization for a new thread
        break;
    case DLL_THREAD_DETACH:
        // Cleanup after a thread ends
        break;
    case DLL_PROCESS_DETACH:
        // Cleanup after the process ends
        break;
    }
    return TRUE;
}
//the end
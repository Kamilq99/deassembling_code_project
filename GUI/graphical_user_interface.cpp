#include <windows.h>
#include <string>
#include <iostream>

// Typ funkcji z DLL
typedef bool (*ValidateKeyFunc)(const char*);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hDllInstance;
ValidateKeyFunc ValidateKey;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Za³aduj DLL
    hDllInstance = LoadLibrary("verify_key.dll");
    if (!hDllInstance) {
        MessageBox(NULL, "Could not load VerifyKey.dll", "Error", MB_ICONERROR);
        return -1;
    }

    // Pobierz funkcjê ValidateKey
    ValidateKey = (ValidateKeyFunc)GetProcAddress(hDllInstance, "ValidateKey");
    if (!ValidateKey) {
        MessageBox(NULL, "Could not find ValidateKey function", "Error", MB_ICONERROR);
        return -1;
    }

    // Konfiguracja okna
    const char CLASS_NAME[] = "LicenseWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Utwórz okno
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "License Key Validation",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 200,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Pêtla komunikatów
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Zwolnij DLL
    FreeLibrary(hDllInstance);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndEdit;
    switch (uMsg) {
    case WM_CREATE:
        hwndEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 50, 200, 20, hwnd, NULL, NULL, NULL);
        CreateWindow("BUTTON", "Validate", WS_CHILD | WS_VISIBLE,
            100, 100, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // Klikniêcie przycisku
            char key[256];
            GetWindowText(hwndEdit, key, sizeof(key));
            bool result = ValidateKey(key);
            MessageBox(hwnd, result ? "Valid key!" : "Invalid key!", "Result", MB_OK);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

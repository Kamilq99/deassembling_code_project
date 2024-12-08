#include <windows.h>
#include <string>
#include <iostream>

// Function type from the DLL
typedef bool (*ValidateKeyFunc)(const char*);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hDllInstance;
ValidateKeyFunc ValidateKey;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    std::cout << "Starting application..." << std::endl;

    // Load the DLL
    hDllInstance = LoadLibrary("verify_key.dll");
    if (!hDllInstance) {
        DWORD dwError = GetLastError();
        MessageBox(NULL, "Could not load VerifyKey.dll", "Error", MB_ICONERROR);
        std::cerr << "Error loading DLL: " << dwError << std::endl;  // Diagnostic
        return -1;
    }
    else {
        std::cout << "DLL loaded successfully!" << std::endl;  // Diagnostic
    }

    // Retrieve the ValidateKey function
    ValidateKey = (ValidateKeyFunc)GetProcAddress(hDllInstance, "ValidateKey");
    if (!ValidateKey) {
        DWORD dwError = GetLastError();
        MessageBox(NULL, "Could not find ValidateKey function", "Error", MB_ICONERROR);
        std::cerr << "Error finding function: " << dwError << std::endl;  // Diagnostic
        return -1;
    }
    else {
        std::cout << "Function loaded successfully!" << std::endl;  // Diagnostic
    }

    // Window setup
    const char CLASS_NAME[] = "LicenseWindow";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    // Check if the window class is registered correctly
    if (!RegisterClass(&wc)) {
        DWORD dwError = GetLastError();
        MessageBox(NULL, "Failed to register window class", "Error", MB_ICONERROR);
        std::cerr << "Error registering window class: " << dwError << std::endl;  // Diagnostic
        return -1;
    }
    else {
        std::cout << "Window class registered successfully!" << std::endl;  // Diagnostic
    }

    // Create the window
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
        DWORD dwError = GetLastError();
        MessageBox(NULL, "Failed to create window", "Error", MB_ICONERROR);
        std::cerr << "Error creating window: " << dwError << std::endl;  // Diagnostic
        return 0;
    }
    else {
        std::cout << "Window created successfully!" << std::endl;  // Diagnostic
    }

    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Free the DLL
    FreeLibrary(hDllInstance);
    std::cout << "DLL unloaded successfully!" << std::endl;  // Diagnostic

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hwndEdit;
    switch (uMsg) {
    case WM_CREATE:
        std::cout << "Window creation event triggered..." << std::endl;  // Diagnostic
        hwndEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER,
            50, 50, 200, 20, hwnd, NULL, NULL, NULL);
        CreateWindow("BUTTON", "Validate", WS_CHILD | WS_VISIBLE,
            100, 100, 100, 30, hwnd, (HMENU)1, NULL, NULL);
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { // Button click
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
//the end
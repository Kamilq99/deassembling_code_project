#include <windows.h>
#include <stdio.h>

// Function prototype for the license verification function in VerifyKey.dll
typedef bool (*VerifyKeyFunc)(const char* key);

// Window procedure declaration
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// Entry point for the Windows application
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Register the window class
    const char CLASS_NAME[] = "LicenseKeyWindow";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "License Verification",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 300, 150,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Message loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Window procedure to handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hLabel, hEdit, hButton;
    static HINSTANCE hLib = NULL;
    static VerifyKeyFunc verify_key = NULL;

    switch (uMsg) {
        case WM_CREATE:
            // Create the label
            hLabel = CreateWindow(
                "STATIC", 
                "Enter your license key below", 
                WS_VISIBLE | WS_CHILD, 
                20, 20, 240, 20, 
                hwnd, 
                NULL, 
                NULL, 
                NULL
            );

            // Create the text box for entering the key
            hEdit = CreateWindow(
                "EDIT", 
                "", 
                WS_VISIBLE | WS_CHILD | WS_BORDER, 
                20, 50, 240, 20, 
                hwnd, 
                NULL, 
                NULL, 
                NULL
            );

            // Create the "Verify" button
            hButton = CreateWindow(
                "BUTTON", 
                "Verify", 
                WS_VISIBLE | WS_CHILD, 
                90, 80, 100, 30, 
                hwnd, 
                (HMENU) 1, 
                NULL, 
                NULL
            );

            // Load the VerifyKey.dll dynamically
            hLib = LoadLibrary("VerifyKey/VerifyKey.dll");
            if (hLib != NULL) {
                // Get the address of the verify_license_key function
                verify_key = (VerifyKeyFunc)GetProcAddress(hLib, "verify_license_key");
                if (verify_key == NULL) {
                    MessageBox(hwnd, "Could not find the function in the DLL", "Error", MB_OK);
                }
            } else {
                MessageBox(hwnd, "Could not load VerifyKey.dll", "Error", MB_OK);
            }
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {  // Handle the "Verify" button click
                char licenseKey[256];
                GetWindowText(hEdit, licenseKey, 256);  // Get the entered license key

                if (verify_key != NULL) {
                    // Call the verify_license_key function from the DLL
                    if (verify_key(licenseKey)) {
                        MessageBox(hwnd, "License key is valid!", "Success", MB_OK);
                    } else {
                        MessageBox(hwnd, "Invalid license key!", "Error", MB_OK);
                    }
                }
            }
            break;

        case WM_DESTROY:
            // Free the loaded DLL before exiting
            if (hLib != NULL) {
                FreeLibrary(hLib);
            }
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

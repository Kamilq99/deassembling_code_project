#include <windows.h>

// Deklaracja funkcji
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Zarejestrowanie klasy okna
    const char CLASS_NAME[] = "LicenseKeyWindow";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Stworzenie okna
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

    // Pętla wiadomości
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

// Funkcja okna (window procedure) obsługująca wiadomości
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND hLabel, hEdit, hButton;

    switch (uMsg) {
        case WM_CREATE:
            // Etykieta z opisem
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

            // Pole tekstowe do wpisania klucza
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

            // Przycisk "Verify"
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
            break;

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {  // Obsługa przycisku "Verify"
                char licenseKey[256];
                GetWindowText(hEdit, licenseKey, 256);
                MessageBox(hwnd, licenseKey, "Entered License Key", MB_OK);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

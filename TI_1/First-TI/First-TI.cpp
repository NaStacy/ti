#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"
#include "First-TI.h"

#include "cipher.h"

#define MAX_LOADSTRING 100

#define ID_COMBOBOX_METHOD 1
#define ID_TEXTBOX_ENCRYPTION 2
#define ID_TEXTBOX_DECRYPTION 3
#define ID_COMBOBOX_KEY 4
#define ID_EDIT_KEY 5
#define ID_BUTTON_CIPHER 6
#define ID_BUTTON_DECIPHER 7

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FIRSTTI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FIRSTTI));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FIRSTTI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance;

   HWND hWnd = CreateWindowW(szWindowClass, L"Cipher", WS_OVERLAPPED | WS_BORDER | WS_SYSMENU,
      CW_USEDEFAULT, 0, 980, 560, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    char cipherString[255] = "";
    char decipherString[255] = "";
    char keyString[255] = "";
    char typeString[255] = "";
    int digitKey, digitType;

    static HWND hComboBoxType;
    static HWND hTextBoxCipher;
    static HWND hTextBoxDecipher;
    static HWND hComboBoxKey;
    static HWND hEditKey;
    static HWND hStaticCipher;
    static HWND hStaticDecipher;
    static HWND hStaticKey;
    static HWND hButtonCipher;
    static HWND hButtonDecipher;

    switch (message)
    {
    case WM_CREATE:
        hComboBoxType = CreateWindowExW(WS_EX_CLIENTEDGE, L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
            12, 12, 350, 300, hWnd, (HMENU)ID_COMBOBOX_METHOD, hInst, NULL);

        SendMessageA(hComboBoxType, CB_ADDSTRING, (WPARAM)0, (LPARAM)"Метод железнодорожной изгороди");
        SendMessageA(hComboBoxType, CB_ADDSTRING, (WPARAM)0, (LPARAM)"Столбцовый метод");
        SendMessageA(hComboBoxType, CB_ADDSTRING, (WPARAM)0, (LPARAM)"Метод поворачивающейся решётки");
        SendMessageA(hComboBoxType, CB_ADDSTRING, (WPARAM)0, (LPARAM)"Шифр Плейфера");
        SendMessageA(hComboBoxType, CB_SETCURSEL, 0, 0);

        hTextBoxCipher = CreateWindowW(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
            12, 75, 740, 200, hWnd, (HMENU)ID_TEXTBOX_ENCRYPTION, hInst, NULL);

        hTextBoxDecipher = CreateWindowW(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
            12, 315, 740, 200, hWnd, (HMENU)ID_TEXTBOX_DECRYPTION, hInst, NULL);

        hComboBoxKey = CreateWindowExW(WS_EX_CLIENTEDGE, L"COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
            770, 130, 185, 300, hWnd, (HMENU)ID_COMBOBOX_KEY, hInst, NULL);

        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"1");
        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"2");
        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"3");
        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"4");
        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"5");
        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"6");
        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"7");
        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"8");
        SendMessageA(hComboBoxKey, CB_ADDSTRING, (WPARAM)0, (LPARAM)"9");
        SendMessageA(hComboBoxKey, CB_SETCURSEL, 0, 0);

        hEditKey = CreateWindowW(L"EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER,
            770, 100, 185, 20, hWnd, (HMENU)ID_EDIT_KEY, hInst, NULL);

        hStaticCipher = CreateWindowW(L"STATIC", NULL, WS_CHILD | WS_VISIBLE, 12, 50, 120, 20, hWnd, NULL, hInst, NULL);
        hStaticDecipher = CreateWindowW(L"STATIC", NULL, WS_CHILD | WS_VISIBLE, 12, 290, 120, 20, hWnd, NULL, hInst, NULL);
        hStaticKey = CreateWindowW(L"STATIC", NULL, WS_CHILD | WS_VISIBLE, 770, 75, 120, 20, hWnd, NULL, hInst, NULL);

        SendMessageA(hStaticCipher, WM_SETTEXT, (WPARAM)0, (LPARAM)"Исходный текст");
        SendMessageA(hStaticDecipher, WM_SETTEXT, (WPARAM)0, (LPARAM)"Результат");
        SendMessageA(hStaticKey, WM_SETTEXT, (WPARAM)0, (LPARAM)"Ключ");

        hButtonCipher = CreateWindowW(L"BUTTON", L"Шифровать", WS_CHILD | WS_VISIBLE | BS_FLAT,
            770, 160, 185, 30, hWnd, (HMENU)ID_BUTTON_CIPHER, hInst, NULL);

        hButtonDecipher = CreateWindowW(L"BUTTON", L"Дешифровать", WS_CHILD | WS_VISIBLE | BS_FLAT,
            770, 200, 185, 30, hWnd, (HMENU)ID_BUTTON_DECIPHER, hInst, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ID_BUTTON_CIPHER:
            digitKey = SendMessageA(hComboBoxKey, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
            digitType = SendMessageA(hComboBoxType, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
            SendMessageA(hComboBoxType, CB_GETLBTEXT, (WPARAM)(digitType), (LPARAM)typeString);
            GetWindowTextA(hEditKey, (LPSTR)&keyString[0], 255);
            GetWindowTextA(hTextBoxCipher, (LPSTR)&cipherString[0], 255);
            GetWindowTextA(hTextBoxDecipher, (LPSTR)&decipherString[0], 255);

            if (strcmp(typeString, "Метод железнодорожной изгороди") == 0)
            {
                strcpy(decipherString, RailCipher(string(cipherString), digitKey + 1).c_str());
            }
            else if (strcmp(typeString, "Столбцовый метод") == 0)
            {
                if (string(keyString) == "")
                {
                    ::MessageBoxA(hWnd, "Incorrect Key", "ERROR", MB_OK);
                    break;
                }
                strcpy(decipherString, ColumnCipher(string(cipherString), string(keyString)).c_str());
            }
            else if (strcmp(typeString, "Метод поворачивающейся решётки") == 0)
            {
                strcpy(decipherString, LatticeCipher(string(cipherString)).c_str());
            }
            else if (strcmp(typeString, "Шифр Плейфера") == 0)
            {
                if (string(cipherString).find_first_not_of("abcdefghijklmnopqrstuvwxyz") != string::npos)
                {
                    ::MessageBoxA(hWnd, "Incorrect Cipher Message", "ERROR", MB_OK);
                    break;
                }
                if (string(keyString).find_first_not_of("abcdefghijklmnopqrstuvwxyz") != string::npos)
                {
                    ::MessageBoxA(hWnd, "Incorrect Key", "ERROR", MB_OK);
                    break;
                }
                strcpy(decipherString, PleiferCipher(string(cipherString), string(keyString), 0).c_str());
            }

            SetWindowTextA(hTextBoxDecipher, decipherString);
            break;
        case ID_BUTTON_DECIPHER:
            digitKey = SendMessageA(hComboBoxKey, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
            digitType = SendMessageA(hComboBoxType, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
            SendMessageA(hComboBoxType, CB_GETLBTEXT, (WPARAM)(digitType), (LPARAM)typeString);
            GetWindowTextA(hEditKey, (LPSTR)&keyString[0], 255);
            GetWindowTextA(hTextBoxCipher, (LPSTR)&cipherString[0], 255);
            GetWindowTextA(hTextBoxDecipher, (LPSTR)&decipherString[0], 255);

            if (strcmp(typeString, "Метод железнодорожной изгороди") == 0)
            {
                strcpy(cipherString, RailDecipher(string(decipherString), digitKey + 1).c_str());
            }
            else if (strcmp(typeString, "Столбцовый метод") == 0)
            {
                if (string(keyString) == "")
                {
                    ::MessageBoxA(hWnd, "Incorrect Key", "ERROR", MB_OK);
                    break;
                }
                strcpy(cipherString, ColumnDecipher(string(decipherString), string(keyString)).c_str());
            }
            else if (strcmp(typeString, "Метод поворачивающейся решётки") == 0)
            {
                strcpy(cipherString, LatticeDecipher(string(decipherString)).c_str());
            }
            else if (strcmp(typeString, "Шифр Плейфера") == 0)
            {
                if (string(decipherString).find_first_not_of("abcdefghijklmnopqrstuvwxyz") != string::npos)
                {
                    ::MessageBoxA(hWnd, "Incorrect Decipher Message", "ERROR", MB_OK);
                    break;
                }
                if (string(keyString).find_first_not_of("abcdefghijklmnopqrstuvwxyz") != string::npos)
                {
                    ::MessageBoxA(hWnd, "Incorrect Key", "ERROR", MB_OK);
                    break;
                }
                strcpy(cipherString, PleiferCipher(string(decipherString), string(keyString), 1).c_str());
            }

            SetWindowTextA(hTextBoxCipher, cipherString);
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
// 3.11.2022.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "3.11.2022.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY3112022, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY3112022));

    MSG msg;

    // Цикл основного сообщения:
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
    wcex.cbSize         = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY3112022));
    wcex.hCursor        = NULL;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd) return FALSE;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

HCURSOR hCursor1, hCursor2;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    WCHAR str[MAX_LOADSTRING];

    switch (message)
    {
    case WM_CREATE:
    {
        HINSTANCE hInstance = GetModuleHandle(NULL);
        hCursor1 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
        hCursor2 = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR2));
    }
    break;

    case WM_LBUTTONDOWN:
    {
        RECT rect;
        GetClientRect(hWnd, &rect);
        COORD mLoc = { LOWORD(lParam), HIWORD(lParam) };

        const int MARG = 100;

        if (rect.left + MARG < mLoc.X && rect.top + MARG < mLoc.Y &&
            rect.right - MARG > mLoc.X && rect.bottom - MARG > mLoc.Y)
            SetWindowText(hWnd, TEXT("ЛКМ был в \"Рамке\""));

        else if (rect.left + MARG == mLoc.X && rect.top + MARG == mLoc.Y &&
            rect.right - MARG == mLoc.X && rect.bottom - MARG == mLoc.Y)
            SetWindowText(hWnd, TEXT(" ЛКМ был на \"Рамке\""));

        else SetWindowText(hWnd, TEXT("ЛКМ был в не \"Рамке\""));
    }
    break;

    case WM_RBUTTONDOWN:
    {
        RECT rect;
        GetClientRect(hWnd, &rect);
        wsprintfW(str, L"Размер окна: %iх%i", rect.right - rect.left, rect.bottom - rect.top);
        SetWindowText(hWnd, str);
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

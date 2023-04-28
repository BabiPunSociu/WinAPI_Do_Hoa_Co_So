
#include "framework.h"
#include "Do_Hoa_Co_So.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
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

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DOHOACOSO, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DOHOACOSO));

    MSG msg;

    // Main message loop:
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DOHOACOSO));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DOHOACOSO);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
    static int x, y;
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;

        //  BÚT VẼ (HPEN)
        /*
        // windows cung cấp 3 bút vẽ: BLACK_PEN, WHITE_PEN, NULL_PEN
            // GetStockObject(): để lấy bút vẽ
        // Ngoài ra có thể tự tạo bút vẽ
            // CreatePen(iPenStyle, iWidth, crColor)
                // Các kiểu nét bút:
                // PS_SOLID: nét liền
                // PS_DASH: nét ------
                // PS_DOT: nét .......
                // PS_DashDot: nét _._._._
                // PS_DashDotDot: nét _.._.._.._..
                // PS_NULL
                // PS_INSIDEFRAME: nét liền
            // DeleteObject(): để hủy bút vẽ
        // SelectObject(): để gán bút vẽ cho ngữ cảnh thiết bị -> trả về
            //  handle của bút cũ. đồng thời thiết lập bút mới
        // Lấy handle của bút vẽ hiện thời: hPen = GetCurrentObject (hdc, OBJ_PEN) ;
        */

        // Màu nền: (nền mặc định: OPAQUE)
        /*
        Thay nền:
        SetBkColor(hdc, crColor);
        Lấy màu hiện thời:
        GetBkColor();
        Ngăn không cho Windows làm đầy quãng ngắt:
        SetBkMode(hdc, TRANSPARENT);
        */

        // Chổi quét BRUSH
        /*
        * Có 5 hàm cho oheos tạo các chổi quét
            * hBrush = CreateSolidBrush(crColor);
            * hBrush = CreateHatchBrush(iHatchStyle, crColor);  // Các đường gạch
                * Các style:
                * HS_HORIZONTAL
                * HS_VERTICAL
                * HS_FDIAGONAL
                * HS_BDIAGONAL
                * HS_CROSS
                * HS_DIAGCROSS
        * Làm việc với bút vẽ:
            * SelectObject
            * DeleteObject
            * GetObject
        */


        static HPEN hPen1, hPen2;
        hPen1 = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
        hPen2 = CreatePen(PS_DASH, 2, RGB(0,255,255));

        static HBRUSH hBrush1, hBrush2;
        hBrush1 = CreateSolidBrush(RGB(255, 255, 20));
        hBrush2 = CreateHatchBrush(HS_CROSS, RGB(220, 10, 30));

        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...

        // Vẽ điểm dùng SetPixel
        SetPixel(hdc, 100, 100, RGB(255, 0, 0));

        // Vẽ đoạn thẳng
        MoveToEx(hdc, 100, 30, NULL);  // Thiết lập vi trí bắt đầu
        LineTo(hdc, 500, 200);  // Vẽ đoạn thẳng từ vi tri hiện thời tới vị trí mới


        // Lấy vị trí hiện thời
   //   GetCurrentPositionEx(hdc, &p);


        // Vẽ nhiều đoạn thẳng
        POINT p[5] = { {100, 100}, {200, 100}, {200, 200}, {100, 200}, {100, 100} };

        // Cach 1: Dùng vòng lặp vẽ từng đoạn
        /*
        MoveToEx(hdc, p[0].x, p[0].y, NULL);    // Tạo điểm bắt đầu
        for (int i = 0;i < 5;i++)
        {
            LineTo(hdc, p[i].x, p[i].y);
        }
        */
        // Cach 2: Vẽ chuỗi đoạn thẳng nối tiếp
    //    Polyline(hdc, p, 5);    // vẽ đường gấp khúc
    //    Polygon(hdc, p, 3);     // vẽ hình kín bằng cách tự động nối điểm đầu -> điểm cuối

        // Vẽ hình chữ nhật
        SelectObject(hdc, hPen1);   // Set bút
        SelectObject(hdc, hBrush1); // tô màu vùng kín
        Rectangle(hdc, 100, 30, 500, 200);
        // Vẽ hình chữ nhật bo tròn góc
        RoundRect(hdc, 520, 30, 920, 200, 50, 50);


        // Vẽ elip: các tọa độ là hình chữ nhật ngoại tiếp elip
        Ellipse(hdc, 530, 40, 910, 190);  // Vẽ nằm trong HCN bo góc
        

        SelectObject(hdc, hPen2);
        SelectObject(hdc, hBrush2);
        // Hình tròn: độ dài width=height
        Ellipse(hdc, 520, 210, 720, 410);


        // Vẽ cung tròn:
        Arc(hdc, 730, 210, 930, 410, 830, 0, 210, 350);
        //hdc, xLeft, yTop, xRight, yBottom, xStart, yStart, xEnd, yEnd

        // Vẽ hình quạt:
        Pie(hdc, 730, 210, 930, 410, 830, 410, 930, 310);

        // Vẽ hình 
        Chord(hdc, 730, 210, 930, 410, 930, 310, 830, 210);

        EndPaint(hWnd, &ps);
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

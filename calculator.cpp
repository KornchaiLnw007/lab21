#include <windows.h>
#include <sstream>
#include <string>

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    static HWND hNum1, hNum2, hResult;
    static HWND hAddBtn, hSubBtn, hMulBtn, hDivBtn;

    switch (Message) {
        case WM_CREATE:
            
			CreateWindowEx(0, "EDIT", "<3 Please input 2 numbers <3", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 20, 200 , 25, hwnd, NULL, NULL, NULL);
			
            hNum1 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 55, 110, 25, hwnd, NULL, NULL, NULL);
            hNum2 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 20, 85, 110, 25, hwnd, NULL, NULL, NULL);
            
            hAddBtn = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE, 150, 55, 30, 30, hwnd, (HMENU)1, NULL, NULL);

            hSubBtn = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE, 180, 55, 30, 30, hwnd, (HMENU)2, NULL, NULL);
            
            hMulBtn = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE, 150, 85, 30, 30, hwnd, (HMENU)3, NULL, NULL);
            
            hDivBtn = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE, 180, 85, 30, 30, hwnd, (HMENU)4, NULL, NULL);
            
            break;

        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED) {
                char num1Text[256], num2Text[256];
                GetWindowText(hNum1, num1Text, sizeof(num1Text));
                GetWindowText(hNum2, num2Text, sizeof(num2Text));

                
                double num1 = atof(num1Text);
                double num2 = atof(num2Text);
                double result = 0;
                std::string resultMessage;

                
                switch (LOWORD(wParam)) {
                    case 1: 
                        result = num1 + num2;
                        break;
                    case 2: 
                        result = num1 - num2;
                        break;
                    case 3: 
                        result = num1 * num2;
                        break;
                    case 4: 
                        if (num2 != 0) {
                            result = num1 / num2;
                        } else {
                            MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_ICONEXCLAMATION | MB_OK);
                            return 0;
                        }
                        break;
                }

               
                std::ostringstream oss;
                oss << "Result: " << result;
                resultMessage = oss.str();

                
                MessageBox(hwnd, resultMessage.c_str(), "Result", MB_OK | MB_ICONINFORMATION);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(232, 89, 89)); // ใช้สีเขียวสด
    wc.lpszClassName = "MyCalculator";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

	hwnd = CreateWindowEx(0, "MyCalculator", "My Calculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) { 	
        MessageBox(NULL, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

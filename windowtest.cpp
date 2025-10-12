#include <windows.h>

// 窗口类
class CMyWindow {
private:
    HWND hWnd;           // 窗口句柄
    const char* title;   // 窗口标题
    int width;           // 窗口宽度
    int height;          // 窗口高度

    // 窗口过程函数
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        // 根据消息类型进行处理
        switch (uMsg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;
            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

public:
    // 构造函数
    CMyWindow(const char* windowTitle, int windowWidth, int windowHeight)
        : title(windowTitle), width(windowWidth), height(windowHeight), hWnd(nullptr) {}

    // 创建窗口
    BOOL Create() {
        // 注册窗口类
        WNDCLASSEX wc = {0};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = "MyWindowClass";

        if (!RegisterClassEx(&wc)) {
            return FALSE;
        }

        // 创建窗口
        hWnd = CreateWindowEx(
            WS_EX_STATICEDGE,        // 扩展风格
            "MyWindowClass",         // 窗口类名
            title,                   // 窗口标题
            WS_CAPTION | WS_SYSMENU,     // 窗口风格
            CW_USEDEFAULT,           // X坐标
            CW_USEDEFAULT,           // Y坐标
            width,                   // 宽度
            height,                  // 高度
            NULL,                    // 父窗口
            NULL,                    // 菜单
            GetModuleHandle(NULL),   // 应用程序实例
            NULL                     // 窗口创建参数
        );

        if (!hWnd) {
            return FALSE;
        }

        // 显示窗口
        ShowWindow(hWnd, SW_SHOW);
        UpdateWindow(hWnd);

        return TRUE;
    }

    // 销毁窗口
    void Destroy() {
        if (hWnd) {
            DestroyWindow(hWnd);
            hWnd = nullptr;
        }
    }

    // 窗口消息循环
    void RunMessageLoop() {
        MSG msg = {0};
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
};

// 主函数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    CMyWindow myWindow("WS_EX_STATICEDGE WS_OVERLAPPEDWINDOW", 600, 300);
    if (!myWindow.Create()) {
        return 1;
    }

    myWindow.RunMessageLoop();
    myWindow.Destroy();
    return 0;
}
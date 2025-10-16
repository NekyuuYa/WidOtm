#pragma once
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <thread>
#include <string>

extern unsigned int fps;


class WO_FpsSch {
public:
    explicit WO_FpsSch(unsigned fps=60) noexcept
        : kPeriod(std::chrono::nanoseconds(1'000'000'000 / fps)),
        next_(std::chrono::steady_clock::now() + kPeriod) {}

    // 阻塞
    bool wait() noexcept {
        auto now = std::chrono::steady_clock::now();
        if (now >= next_) {
            next_ += kPeriod;
            return false;
        }
        std::this_thread::sleep_until(next_);
        next_ += kPeriod;
        return true;
    }

    void setFps(unsigned fps) noexcept {
        kPeriod = std::chrono::nanoseconds(1'000'000'000 / fps);
    }

private:
    std::chrono::nanoseconds kPeriod;    // 每帧理论时长
    std::chrono::steady_clock::time_point next_;
};

struct WO_SIZE {
    int width;
    int height;
};
struct WO_PST
{
    int x;
    int y;
};


struct tm_frame{
    unsigned int frame_id;
    tm_frame(unsigned int f=0) : frame_id(f) {}
    tm_frame(const tm& time) {
        frame_id = (time.tm_hour * 60 * 60 + time.tm_min * 60 + time.tm_sec) * fps;
    }
};

namespace WO_OBJ {
    int CLASSES_ID = 0;
    struct PrtClass {
        WNDCLASSEX wc;
        int id;
        LPCWSTR className;
        PrtClass(HBRUSH brush = NULL,
                HICON icon = LoadIcon(NULL, IDI_APPLICATION),
                HCURSOR cursor = LoadCursor(NULL, IDC_ARROW)) {
            id = ++CLASSES_ID;
            className = (L"PrtClass" + std::to_wstring(id)).c_str();
            wc.cbSize = sizeof(WNDCLASSEX);
            wc.style = CS_HREDRAW | CS_VREDRAW;
            wc.lpfnWndProc = DefWindowProc;
            wc.cbClsExtra = 0;
            wc.cbWndExtra = 0;
            wc.hInstance = GetModuleHandle(NULL);
            wc.hIcon = icon;
            wc.hCursor = cursor;
            wc.hbrBackground = brush;
            wc.lpszMenuName = NULL;
            wc.lpszClassName = className;
            wc.hIconSm = NULL;
            RegisterClassEx(&wc);
        }
    };
    class paint {
        private:
            WO_SIZE size;
            WO_PST pos;
            LPCWSTR PrtClassName;
            HWND hWnd;
        public:
            paint() {};
            paint(PrtClass PrtCls): PrtClassName(PrtCls.className) {};
            bool INIT(WO_SIZE size, WO_PST pos) {
                this->size = size;
                this->pos = pos;
                hWnd = CreateWindowEx(
                    0, PrtClassName, L"",
                    WS_POPUP | WS_VISIBLE,
                    pos.x, pos.y, size.width, size.height,
                    NULL, NULL, NULL, NULL
                );
            }
    };
}


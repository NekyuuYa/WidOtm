#pragma once
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <thread>

extern unsigned int fps;

// 窗口类型

// 无标题栏窗口
#define NO_TITLE 0
// 标准带标题窗口，含基本操作控件
#define STD_WITH_TITLE 1
typedef int WO_TYPE;

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

class WO_tmWindow {
    private:
        WO_SIZE size;
        WO_TYPE type;
        WO_PST pos;
        HWND hWnd;
        
    public:
        /**
         * @brief 声明一个新的窗口
         * @param type 窗口类型
         */
        WO_tmWindow (WO_TYPE type = NO_TITLE) {
            this->type = type;
        }

        bool modifiySize(WO_SIZE size) {
            if (this->size.width != size.width || this->size.height != size.height) {
                this->size = size;
                return true;
            }
            return false;
        }

        bool initWindow(WO_SIZE size, WO_PST pos) {
            this->size = size;
            this->pos = pos;
            WNDCLASSEX wc = {0};
            switch (type) {
            case NO_TITLE:
                break;
            case STD_WITH_TITLE:
                break;
            default:
                break;
            }
        }
};
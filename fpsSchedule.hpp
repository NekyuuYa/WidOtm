#pragma once
#include <chrono>
#include <thread>

class FpsScheduler {
public:
    explicit FpsScheduler(unsigned fps) noexcept
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
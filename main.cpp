#include <iostream>
#include "fpsSchedule.hpp"

const unsigned fps = 60;

void render(int frame) {

}
int main() {
    FpsScheduler sched(fps);
    int frame = 0;
    while (true) {
        frame++;
        if (sched.wait())          // 返回 true 表示正常帧
            render(frame);
    }
    return 0;
}


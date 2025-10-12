#include <iostream>
#include "WidOtm_compPack.hpp"

void render(int frame) {
    
}
int main() {
    auto WD1 = WO_tmWindow(NO_TITLE);
    WO_FpsSch sched(60);
    int frame = 0;
    while (true) {
        frame++;
        if (sched.wait())          // 返回 true 表示正常帧
            render(frame);
    }
    return 0;
}


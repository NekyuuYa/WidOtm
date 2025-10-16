#include <iostream>
#include <algorithm>
#include "WidOtm_compPack.hpp"

void render(int frame) {
    
}
int main() {
    auto TPCls1 = WO_OBJ::PrtClass();
    WO_OBJ::paint WordList[6];
    std::fill_n(WordList, 6, WO_OBJ::paint(TPCls1));

    
    WO_FpsSch sched(60);
    int frame = 0;
    while (true) {
        frame++;
        if (sched.wait())          // 返回 true 表示正常帧
            render(frame);
    }
    return 0;
}

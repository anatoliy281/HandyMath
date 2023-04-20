#ifndef __COLORING_H
#define __COLORING_H

#include "types_global.h"


enum class Color {
    Black=30, Red, Green, Yellow, Blue, Purple, LightBlue, White
};

enum class Background {
    Black=40, Red, Green, Yellow, Blue, Purple, LightBlue, White  
};
enum Appearence {
    Normal=0, Bold, Bleak, Italic, Underscored=4, Inversed=7, Invisible=8
};

template<typename... Options>
std::string coloring(std::string text, Options... opt) {
    // промежуточные лямбда
    auto str_cast = [](auto prop) { return ";" + std::to_string(static_cast<int>(prop)); };
    auto makeBracket = [bra="\x1b[", ket="m"](auto optStr) { return bra + optStr + ket; }; 
    // 
    const auto custom_view { makeBracket(("" + ... + str_cast(opt))) };
    const auto default_view { makeBracket(str_cast(Appearence::Normal)) };

    return custom_view + text + default_view;
};

#endif //__COLORING_H
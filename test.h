#ifndef __TEST_H
#define __TEST_H

#include <sstream>
#include <iostream>
#include "coloring.h"

namespace Test {
    
template<typename... Args>
void Show(std::string strMes, Args... args) {
    std::cout << coloring(strMes, Color::Yellow);
    auto t = ("" + ... + (args + " "));
    std::cout << reinterpret_cast<const char*>(t.c_str()) << std::endl;
}
    
template<auto func = []{}>
void BlockTest(std::string name) {
    std::stringstream ss;
    auto& fc (name[0]);
    fc = std::toupper(fc);
    ss << "[test" << name << "]\n";
    std::cout << reinterpret_cast<const char*>(coloring(ss.str(), Color::Yellow, Appearence::Bold).c_str());

    func();
}


    
} // mamespace Test

#endif //__TEST_H
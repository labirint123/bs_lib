#pragma once
#include <string>
#include <vector>
#include <iostream>

inline void Log(const std::string& str) {
    std::cout << "[string] " << str << std::endl;
}
inline void Log(int value) {
    std::cout << "[int] " << value << std::endl;
}
inline void Log(unsigned int value) {
    std::cout << "[uint] " << value << std::endl;
}
inline void Log(double value) {
    std::cout << "[double] " << value << std::endl;
}
inline void Log(float value) {
    std::cout << "[float] " << value << std::endl;
}

template <typename T>
inline void Log(const std::vector<T>& vec) {
    std::cout << "[vector] [\n";
    for (const auto& item : vec)
        Log(item);
    std::cout << "]" << std::endl;
}

template <typename T>
inline void Log(const T& value) {
    std::cout << "[Log] value: " << value << std::endl;
}

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

inline void Log(const std::string &str)
{
    std::cout << "[string] " << str << std::endl;
}
inline void Log(int value)
{
    std::cout << "[int] " << value << std::endl;
}
inline void Log(unsigned int value)
{
    std::cout << "[uint] " << value << std::endl;
}
inline void Log(double value)
{
    std::cout << "[double] " << value << std::endl;
}
inline void Log(float value)
{
    std::cout << "[float] " << value << std::endl;
}
inline void Log(sf::Vector2f value)
{
    std::cout << "[Vector2f] " << "x: " << value.x << "\ty: " << value.y << std::endl;
}
inline void Log(sf::Vector2i value)
{
    std::cout << "[Vector2i] " << "x: " << value.x << "\ty: " << value.y << std::endl;
}
inline void Log(sf::Vector2u value)
{
    std::cout << "[Vector2u] " << "x: " << value.x << "\ty: " << value.y << std::endl;
}

template <typename T>
inline void Log(const std::vector<T> &vec)
{
    std::cout << "[vector] [\n";
    for (const auto &item : vec)
        Log(item);
    std::cout << "]" << std::endl;
}

template <typename T>
inline void Log(const T &value)
{
    std::cout << "[Log] value: " << value << std::endl;
}

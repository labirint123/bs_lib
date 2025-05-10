#include "JsonManager.h"
#include <iostream>

int main() {
    JsonManager config;

    if (!config.load("hi.json")) {
        std::cerr << "Failed to load config.json\n";
        config.set("window.width",300);
        config.set("window.height",300);
        config.set("window.title",std::string("title"));
        config.set("fullscreen",true);
        config.save("hi.json");
        return 1;
    }

    int width = config.get<int>("window.width", 800);
    int height = config.get<int>("window.height", 600);
    std::string title = config.get<std::string>("window.title", "Untitled");
    bool fullscreen = config.get<bool>("fullscreen", false);

    std::cout << "Title: " << title << "\n";
    std::cout << "Size: " << width << "x" << height << "\n";
    std::cout << "Fullscreen: " << (fullscreen ? "Yes" : "No") << "\n";

    return 0;
}

#pragma once
#include <string>
#include <json.hpp>

class JsonManager {
public:
    explicit JsonManager(const std::string& filepath = "");
    bool load(const std::string& filepath);
    bool save(const std::string& filepath = "");

    template<typename T>
    T get(const std::string& key, const T& defaultValue = T()) const;

    template<typename T>
    void set(const std::string& key, const T& value);

    bool contains(const std::string& key) const;
    void remove(const std::string& key);
    void clear();

private:
    nlohmann::json data;
    std::string path;
};

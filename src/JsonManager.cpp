#include "JsonManager.h"
#include <fstream>

JsonManager::JsonManager(const std::string& filepath) {
    if (!filepath.empty())
        load(filepath);
}

bool JsonManager::load(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) return false;
    in >> data;
    path = filepath;
    return true;
}

bool JsonManager::save(const std::string& filepath) {
    std::string target = filepath.empty() ? path : filepath;
    if (target.empty()) return false;
    std::ofstream out(target);
    if (!out.is_open()) return false;
    out << data.dump(4);
    return true;
}

bool JsonManager::contains(const std::string& key) const {
    return data.contains(key);
}

void JsonManager::remove(const std::string& key) {
    data.erase(key);
}

void JsonManager::clear() {
    data.clear();
}

template<typename T>
T JsonManager::get(const std::string& key, const T& defaultValue) const {
    if (data.contains(key))
        return data.at(key).get<T>();
    return defaultValue;
}

template<typename T>
void JsonManager::set(const std::string& key, const T& value) {
    data[key] = value;
}

template int JsonManager::get<int>(const std::string&, const int&) const;
template float JsonManager::get<float>(const std::string&, const float&) const;
template double JsonManager::get<double>(const std::string&, const double&) const;
template bool JsonManager::get<bool>(const std::string&, const bool&) const;
template std::string JsonManager::get<std::string>(const std::string&, const std::string&) const;

template void JsonManager::set<int>(const std::string&, const int&);
template void JsonManager::set<float>(const std::string&, const float&);
template void JsonManager::set<double>(const std::string&, const double&);
template void JsonManager::set<bool>(const std::string&, const bool&);
template void JsonManager::set<std::string>(const std::string&, const std::string&);

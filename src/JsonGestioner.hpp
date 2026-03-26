#pragma once
#include "../json/json.hpp"
#include <string>

using json = nlohmann::json;

class JsonGestionner {
    public:

    static json readFile(const std::string& filePath);

    static void initPasswordFile(const std::string& filePath);

    static void  addEntry(const std::string& filePath, std::string& site, std::string& username, std::string& password, std::string& note);

    static void supprimerEntree(const std::string& filePath, int supNumber);

};


#include "JsonGestioner.hpp"

#include <fstream>
#include "../json/json.hpp"
#include <iostream>

using json = nlohmann::json; //permet de pas ecrire nlohmann::json a chaque fois

json JsonGestionner::readFile(const std::string& filePath){
    std::ifstream file(filePath);
    if(!file){
        std::cerr << "Erreur de l'ecture du fichier : " << filePath << std::endl;
        return NULL;
    }

    json data;
    file >> data;

    return data;
}

void JsonGestionner::initPasswordFile(const std::string& filePath){
    std::ofstream file(filePath);

    if(!file){
        std::cout << "Erreur de lecture fichier" << std::endl;
        return;
    }

    file <<"{"
        <<"\"entries\": ["
        <<"{"
        <<"\"note\": \"exemplemdp\","
        <<"\"password\": \"exempleMdp\","
        <<"\"site\": \"exempleSite.com\","
        <<"\"username\": \"exempleUsername\""
        <<"}"
        <<"]"
        <<"}";

    file.close();
}

void JsonGestionner::addEntry(const std::string& filePath, std::string& site, std::string& username, std::string& password, std::string& note){
    std::ifstream input(filePath);
    json data;

    if(input){
        input >> data;
        input.close();
    } else {
        data["entries"] = json::array();
    }

    json entry;
    entry["site"] = site;
    entry["username"] = username;
    entry["password"] = password;
    entry["note"] = note;

    data["entries"].push_back(entry);

    std::ofstream output(filePath);
    output << data.dump(4);
    output.close();
}


void JsonGestionner::supprimerEntree(const std::string& filePath, int supNumber){

}

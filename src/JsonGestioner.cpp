
#include "JsonGestioner.hpp"

#include <fstream>
#include "../json/json.hpp"
#include <iostream>

using json = nlohmann::json; //permet de pas ecrire nlohmann::json a chaque fois

json JsonGestionner::lireFichier(const std::string& cheminFichier){
    std::ifstream fichier(cheminFichier);
    if(!fichier){
        std::cerr << "Erreur de l'ecture du fichier : " << cheminFichier << std::endl;
        return NULL;
    }

    json data;
    fichier >> data;

    return data;
}

void JsonGestionner::ajouterEntree(const std::string& cheminFichier, std::string& site, std::string& username, std::string& password, std::string& note){
    std::ifstream input(cheminFichier);
    json data;

    if(input){
        input >> data;
        input.close();
    } else {
        data["entries"] = json::array();
    }

    json entree;
    entree["site"] = site;
    entree["username"] = username;
    entree["password"] = password;
    entree["note"] = note;

    data["entries"].push_back(entree);

    std::ofstream output(cheminFichier);
    output << data.dump(4);
    output.close();
}

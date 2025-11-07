
#ifndef JSONGESTIONER_HPP
#define JSONGESTIONER_HPP

#include "../json/json.hpp"
#include <string>

using json = nlohmann::json;

class JsonGestionner {
    public:

    static json lireFichier(const std::string& cheminFichier);

    static void  ajouterEntree(const std::string& cheminFichier, std::string& site, std::string& username, std::string& password, std::string& note);

};

#endif // JSONGESTIONER_HPP

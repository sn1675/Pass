
#include <iostream>
#include <string>

#include "../json/json.hpp"

#include "Passgen.hpp"
#include "JsonGestioner.hpp"
#include "App.hpp"


using json = nlohmann::json; //permet de pas ecrire nlohmann::json a chaque fois

void printMenu(){
    std::string menu[] = {
        "+-----------------------------------------+",
        "- MENU",
        "   0 - Quitter",
        "   1 - Random pass generator",
        "   2 - Accedez a vos mdp",
        "   3 - Ajouter mdp",
        "   4 - Supprimer mdp",
        "   5 - Modifier mdp",
        "+-----------------------------------------+"
    };

    for(const auto &line : menu){
        std::cout << line << std::endl;
    }
}

bool chooseInput(std::string demande){
    std::string choix = "y";

    std::cout << demande;
    std::getline(std::cin, choix);

    if (choix == "" || choix == "y" || choix == "Y"){
        return true;
    }

    return false;
}

void App::login(){
    short count = 0;

    std::string id;
    std::string password;
    while (count < 3) {


        std::cout << "Id: ";
        std::cin >> id;

        std::cout << "password: ";
        std::cin >>password;

        if (id == "nath" && password == "abc") {
            App::menu();
        }

        std::cout << "\nMot de passe ou id errone veuillez reesayer\n\n";
        ++count;
    }

    std::cout << "nombre d'essais trop important\nau revoir !" << std::endl;
}

void App::menu(){

    while(true){

        short c = -1;

        printMenu();
        std::cout << "votre choix : ";
        std::cin >> c;

        switch (c) {


            // CASE 0 TERMINÉ

            case 0: {
                std::cout << "au revoir !" << std::endl;
                exit(EXIT_SUCCESS);
                break;
            }


            // CASE 1 TERMINÉ

            case 1: {
                int len = 10;
                bool maj = false, num = false, spe = false;

                std::cout << "longeur du mdp : ";
                std::cin >> len;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                PassGen::Options opts{
                    opts.len = len,
                    opts.maj = chooseInput("voulez vous ajouter des majuscules ? (Y, n)"),
                    opts.num = chooseInput("voulez vous ajouter des nombres ? (Y, n)"),
                    opts.spe = chooseInput("voulez vous ajouter des speciaux ? (Y, n)"),
                };

                std::cout << "\n\n\n" << "Votre mdp : " << PassGen::genratePassword(opts) << "\n\n\n";

                break;
            }


            // CASE 2 EN COURS

            case 2: {

                /*demander le mdp pour decrypter*/

                json data = JsonGestionner::readFile("json/mdp.json");

                if(data.contains("entries")){
                    for(const auto& entry : data["entries"]){
                        std::cout << "\n\n";
                        std::cout << "Website: " << entry["site"] << std::endl;
                        std::cout << "  Username: " <<  entry["username"] << std::endl;
                        std::cout << "  Password: " <<  entry["password"] << std::endl;
                    }
                }
                break;
            }


            // CASE 3 TERMINÉ

            case 3: {
                std::string site, username, mdp, note;
                std::cout << "entrez le nom du site : ";
                std::cin >> site;
                std::cout << "entrez votre username : ";
                std::cin >> username;
                std::cout << "entrez votre mdp : ";
                std::cin >> mdp;
                std::cout << "entrez une note : ";
                std::cin >> note;
                JsonGestionner::addEntry("json/mdp.json", site, username, mdp, note);
                break;
            }


            // CASE 4 A COMMENCER

            case 4: {
                std::cout << "supp mdp" << std::endl;
                break;
            }

            default: {
                std::cout << "choix invalide" << std::endl;
                break;
            }
        }
    }
}

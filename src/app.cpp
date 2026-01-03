
#include <cstdlib>
#include <fstream>
#include <filesystem>
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

void printMenuLogin(){
    std::string menu[] = {
        "+-----------------------------------------+",
        "- Connexion",
        "   0 - Quitter",
        "   1 - Se connecter",
        "   2 - Cree un compte",
        "   3 - Supp un compte",
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

int loginCheck(std::string username, std::string password){
    short count = 0;

    while (count < 3) {


        std::cout << "Username: ";
        std::cin >> username;

        std::cout << "password: ";
        std::cin >>password;

        if (username == "nath" && password == "abc") {
            return 1;

        }

        std::cout << "\nMot de passe ou id errone veuillez reesayer\n\n";
        ++count;
    }

    std::cout << "nombre d'essais trop important\nau revoir !" << std::endl;
    return 0;
}

void App::login(){
    while (true){
        short c = -1;

        printMenuLogin();

        std::cout << "Votre choix : ";
        std::cin >> c;

        switch (c) {

            //CASE 0 TERMINE

            case 0: {
                std::cout << "Au revoir" << std::endl;
                exit(EXIT_SUCCESS);
                break;
            }

            // CASE 1 EN COURS

            case 1: {
                //complicado
                break;
            }

            // CASE 2 EN COURS

            case 2: {
                //choisir un nom utilisateur qui n'existe pas déja
                std::string nom;
                std::cout << "Entrez votre nom d'utilisateur : ";
                std::cin >> nom;

                std::filesystem::path userPath = std::filesystem::path("users") / nom;

                if(std::filesystem::exists(userPath)){
                    std::cout << "Le nom d'utilisateur existe déjà" << std::endl;
                    break;
                }

                //choisir le mdp à faire


                std::filesystem::create_directory(userPath);
                if(!std::filesystem::exists(userPath)){ std::cout << "Erreur dans la creation du dossier" << std::endl; break;}


                //cree le dossier avec le nom utilisateur ansi que les fichier .env et mdp.json
                std::ofstream filePassword(userPath / "mdp.json");
                std::ofstream fileEnv(userPath / ".env");
                if(!filePassword || !fileEnv){
                    std::cerr << "Erreur dans la creation d un ou des fichier" << std::endl;
                    break;
                }

                filePassword.close();
                fileEnv.close();
                break;
            }

            // CASE 3 EN COURS

            case 3: {

                //demander le nom utilisateur
                //verif si il existe

                //demander le mdp
                //confirmer
                //supprimer le mdp
                break;
            }

            default: {
                std::cout << "choix invalide" << std::endl;
                break;
            }
        }
    }
}

void App::menu(){

    while(true){

        short c = -1;

        printMenu();
        std::cout << "votre choix : ";
        std::cin >> c;

        switch (c) {


            // CASE 0 TERMINE

            case 0: {
                std::cout << "Au revoir !" << std::endl;
                exit(EXIT_SUCCESS);
                break;
            }


            // CASE 1 TERMINE

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


            // CASE 3 TERMINE

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

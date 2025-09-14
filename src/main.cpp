#include <iostream>
#include <string>
#include <thread>

//Json & ficher
#include <fstream>
#include "../json/json.hpp"

#define true 1
#define false 0

using json = nlohmann::json; //permet de pas ecrire nlohmann::json a chaque fois

json lireFichier(const std::string& cheminFichier){
    std::ifstream fichier(cheminFichier);
    if(!fichier){
        std::cerr << "Erreur de l'ecture du fichier : " << cheminFichier << std::endl;
        return NULL;
    }

    json data;
    fichier >> data;

    return data;
}

void ajouterEntree(const std::string& cheminFichier, std::string& site, std::string& username, std::string& password, std::string& note){
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

    std::cout << "Mdp défini !" << std::endl;

}

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

int choixInput(std::string demande){
    std::string choix = "y";

    std::cout << demande;
    std::getline(std::cin, choix);

    if (choix == "" || choix == "y" || choix == "Y"){
        return 1;
    }

    return 0;
}


void passGen(int *len, int *maj, int *num, int *spe){
    std::string mdp;

    std::string let = "abcdefghijklmnopqrstuvwxyz";
    std::string majLet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string numb = "0123456789";
    std::string spec = "!@#$%^&*()-_=+[]{};:,.<>?/";

    std::string comp = let;

    if (*maj) comp += majLet;
    if (*num) comp += numb;
    if (*spe) comp += spec;

    for(int i=0; i<*len; i++){
        mdp += comp[rand() % comp.size()];
    }
    std::cout << mdp << std::endl;
}


int main(){

    srand (time(NULL));

    while(true){

        short choix = -1;

        printMenu();
        std::cout << "votre choix : ";
        std::cin >> choix;

        switch (choix) {

            case 0: {
                std::cout << "au revoir !" << std::endl;
                exit(EXIT_SUCCESS);
                break;
            }

            case 1: {
                std::string choixLen;
                std::string choixLenBug = "";
                int len = 8;
                int maj = false, num = false, spe = false;

                std::cout << "longeur du mdp : ";
                std::cin >> choixLen;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                choixLenBug += choixLen;

                if (choixInput("voulez vous ajouter des majuscules ? (Y, n)")){ maj = true; }
                if (choixInput("voulez vous ajouter des nombres ? (Y, n)")){ num = true; }
                if (choixInput("voulez vous ajouter des speciaux ? (Y, n)")){ spe = true; }


                std::cout << "\n\n\n votre mdp: ";
                passGen(&len, &maj, &num, &spe);
                std::cout << "\n\n\n";
                break;
            }

            case 2: {

                /*demander le mdp pour decrypter les mdp*/

                json data = lireFichier("../json/mdp.json");

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
                ajouterEntree("../json/mdp.json", site, username, mdp, note);
                break;
            }

            case 4: {
                std::cout << "supp mdp" << std::endl;
                break;
            }

            default: {
                std::cout << "choix invalide" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                break;
            }
        }
    }

    return 0;
}

/*g++ main.cpp -o main && ./main*/

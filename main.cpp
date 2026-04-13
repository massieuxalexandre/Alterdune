#include "player.h"
#include "monster.h"
#include "item.h"
#include "action.h"
#include "utils.h"
#include <random>
using namespace std;

int main() {
    vector<vector<string>> actions_data = {
                                            {"COMPLIMENT", "Tu dis a Froggit qu'il a une jolie peau.", "10"},
                                            {"DISCUSS", "Vous parlez de la pluie et du beau temps.", "20"},
                                            
                                            {"OBSERVE", "Tu analyses les mouvements de la boite.", "0"},
                                            {"PET", "Tu caresses doucement le couvercle.", "40"},
                                            {"OFFER_SNACK", "Tu jettes un morceau de pain dans la boite.", "60"},

                                            {"REASON", "Tu tentes de lui expliquer que la violence est inutile.", "10"},
                                            {"DANCE", "Tu lances une battle de danse endiablee !", "30"},
                                            {"JOKE", "Tu racontes une blague sur les processeurs.", "-20"},
                                            {"INSULT", "Tu lui dis que son code est mal indente.", "-50"}
};

    map<string, Action> actions = load_actions(actions_data);
    map<string, Monster*> monsters = load_monsters("data/monsters.csv", actions);
    map<string, Item> items = load_items("data/items.csv");




    cout << "Bienvenue dans Alterdune !" << endl;
    cout << "Entrez votre nom : ";
    // string player_name;
    // getline(cin, player_name);
    string player_name = "test";
    Player player(player_name, items);
    clear();
    

    bool play = true;
    while (play){
        main_menu(player, items);
        string choice;
        getline(cin, choice);
        clear();
        if (choice == "1"){
            bestiaire();
            go_back();

        }
        else if (choice == "2"){
            Monster* monster = monsters["QueenByte"];
            cout << "C'est parti " << player.get_name() << " ! Vous allez jouer contre le monstre " << monster->get_name() << endl;
            string tour = "player";
            int damages;
            while (player.is_alive() && monster->is_alive()){
                if (tour == "player"){
                    damages = random_damages(monster->get_max_hp());
                }
                else if (tour == "monster"){
                    damages = random_damages(player.get_max_hp());
                }
                
                match_menu(monster->get_name());
                if (tour == "player"){
                    string match_choice;
                    getline(cin, match_choice);
                    clear();
                    if (match_choice == "1"){
                        fight(player, monster, damages, tour);
                    }
                    else if (match_choice == "2"){
                        cout << "Copiez l'action que vous voulez executer : " << endl;
                        cout << endl;
                        monster->print_acts();
                    }
                    else if (match_choice == "3"){
                        
                    }
                    else if (match_choice == "4"){
                        
                    }
                }
                else if (tour == "monster"){
                    fight(player, monster, damages, tour);
                    next_tour();
                }
                next_tour();
                clear();
            }
            if (!player.is_alive()){
                cout << "Dommage ! Vous avez ete elimine par " << monster->get_name() << endl;

            }
            else if (!monster->is_alive()){
                cout << "Vous avez gagne la partie !" << endl;
            }
            return 1;
        }
        else if (choice == "3"){
            player.stats();
            go_back();
        }
        else if (choice == "4"){
            player.print_items();
            cout << "Copiez le nom de l'item que vous souhaitez utiliser : " << endl;
            string item_choice;
            getline(cin, item_choice);
            clear();
            player.set_items(item_choice);
            go_back();
        }
        else if (choice == "5"){
            cout << "Merci d'avoir joue, au revoir !" << endl;
            cout << endl;
            play = false;
        }
    }

    
    return 0;
}
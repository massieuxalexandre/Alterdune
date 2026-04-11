#include "player.h"
#include "monster.h"
#include "item.h"
#include "action.h"
#include "utils.h"
#include <random>
using namespace std;

int main() {
    vector<vector<string>> actions_data = {{"REASON", "C'est important la raison !", "10"},
                                            {"DANCE", "Let's danceeeee", "30"},
                                            {"JOKE", "As tu vu ta tête ?? Hahahah", "-20"},
                                            {"INSULT", "Tu est vraiment une m****", "-50"}};

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
            Monster* monster = monsters["Froggit"];
            string tour = "player";
            int damages;
            while (player.is_alive() && monster->is_alive()){
                if (tour == "player"){
                    damages = random_damages(player.get_max_hp());
                }
                else if (tour == "monster"){
                    damages = random_damages(monster->get_max_hp());
                }
                
                match_menu();
                string match_choice;
                getline(cin, match_choice);
                if (tour == "player"){
                    if (match_choice == "1"){
                        fight(player, monster, damages, tour);
                    }
                    else if (match_choice == "2"){
                        cout << "Copiez l'action que vous voulez executer parmi celles disponibles";
                        monster->print_acts();
                    }
                    else if (match_choice == "3"){
                        
                    }
                    else if (match_choice == "4"){
                        
                    }
                }
                else if (tour == "monster"){
                    fight(player, monster, damages, tour);
                }
                clear();
            }
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
#include "player.h"
#include "monster.h"
#include "item.h"
#include "action.h"
#include "utils.h"
using namespace std;

int main() {
    vector<vector<string>> actions_data = {{"REASON", "C'est important la raison !", "10"},
                                            {"DANCE", "Let's danceeeee", "30"},
                                            {"JOKE", "As tu vu ta tête ?? Hahahah", "-20"},
                                            {"INSULT", "Tu est vraiment une m****", "-50"}};

    map<string, Action> actions = load_actions(actions_data);
    map<string, Monster> monsters = load_monsters("data/monsters.csv", actions);
    map<string, Item> items = load_items("data/items.csv");




    cout << "Bienvenue dans Alterdune !" << endl;
    cout << "Entrez votre nom : ";
    // string player_name;
    // getline(cin, player_name);
    string player_name = "test";
    Player player(player_name);
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
            start_match(player, monsters["Froggit"]);
            go_back();
        }
        else if (choice == "3"){
            player.stats();
            go_back();
        }
        else if (choice == "4"){
            all_items(items);
            go_back();
        }
        else if (choice == "5"){
            cout << "Merci d'avoir joue, au revoir !" << endl;
            play = false;
        }
    }

    
    return 0;
}
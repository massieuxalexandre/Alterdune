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
    string player_name = "alex";
    Player player(player_name, items);
    clear();
    

    bool play = true;
    while (play){
        main_menu(player);
        string choice;
        getline(cin, choice);
        clear();
        if (choice == "1"){
            bestiaire();
            next_tour();
        }
        else if (choice == "2"){
            Monster* monster = monsters["QueenByte"];
            cout << "C'est parti " << player.get_name() << " ! Vous allez jouer contre le monstre " << monster->get_name() << endl;
            string tour;
            int damages;
            for (int i = 0; player.is_alive() && monster->is_alive(); i++){
                if (i % 2 == 0){
                    tour = "player";
                }
                else{
                    tour = "monster";
                }
                 
                
                if (tour == "player"){
                    match_menu(monster->get_name());
                    damages = random_damages(monster->get_max_hp());
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
                        cout << endl;
                        string act_choice;
                        getline(cin, act_choice);
                        clear();
                        monster->act(stoi(act_choice));
                    }
                    else if (match_choice == "3"){
                        player.print_items();
                        string item_choice;
                        getline(cin, item_choice);
                        clear();
                        player.use_item(item_choice);
                    }
                    else if (match_choice == "4"){
                        if (monster->spare()){
                            cout << "Vous avez epargne : " << monster->get_name() << " !" << endl;
                        }
                        else{
                            cout << "Vous ne pouvez pas epargner " << monster->get_name() << ", voici sa jauge de pitie : " << monster->get_current_mercy() << "/" << monster->get_mercy_goal() << endl;
                        }
                        cout << endl;
                    }
                }
                else if (tour == "monster"){
                    damages = random_damages(player.get_max_hp());
                    fight(player, monster, damages, tour);
                }
                next_tour();
                clear();
            }

            if (!player.is_alive()){
                cout << "Dommage ! Vous avez ete elimine par " << monster->get_name() << endl;
                cout << endl;

            }
            else if (!monster->is_alive()){
                cout << "Vous avez gagne la partie !" << endl;
                player.set_wins(player.get_wins() + 1);
                cout << endl;
            }
        }
        else if (choice == "3"){
            player.stats();
            next_tour();
        }
        else if (choice == "4"){
            player.print_items();
            string item_choice;
            getline(cin, item_choice);
            clear();
            player.use_item(item_choice);
        }
        else if (choice == "5"){
            cout << "Merci d'avoir joue, au revoir !" << endl;
            cout << endl;
            play = false;
        }
        next_tour();
        clear();
    }

    
    return 0;
}
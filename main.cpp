#include "player.h"
#include "monster.h"
#include "item.h"
#include "action.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
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
    vector<Monster*> monsters = load_monsters("data/monsters.csv", actions);
    vector<Item> items = load_items("data/items.csv");
    vector<vector<string>> history;




    cout << "Bienvenue dans Alterdune !" << endl;
    cout << "Entrez votre nom : ";
    string player_name;
    getline(cin, player_name);
    // string player_name = "alex";
    Player player(player_name, items);
    clear();
    

    while (true){
        player.set_current_hp(player.get_max_hp());
        player.set_items(items);
        main_menu(player);
        string choice;
        getline(cin, choice);
        clear();

        if (!in_array(choice, 1, 5)){
            cout << "Choix invalide, veuillez réessayer." << endl;
            cout << endl;
            continue;
        }

        if (choice == "1"){
            bestiaire(history);
            next_tour();
        }


        else if (choice == "2"){
            int random_index_monster = random_int(monsters.size()-1);
            Monster* monster = monsters[random_index_monster];
            monster->set_current_hp(monster->get_max_hp());
            monster->set_current_mercy(monster->get_mercy_goal()/2);
            cout << "C'est parti " << player.get_name() << " ! Vous allez jouer contre le monstre " << monster->get_name() << endl;
            string tour;
            int damages;

            for (int i = 0; player.is_alive() && monster->is_alive(); i++){
                if (i % 2 == 0){
                    tour = "player";
                    match_menu(monster->get_name());
                    damages = random_int(monster->get_max_hp());
                    string match_choice;
                    getline(cin, match_choice);
                    clear();
                    if (!in_array(match_choice, 1, 4)){
                        cout << "Choix invalide, veuillez réessayer." << endl;
                        cout << endl;
                        i--;
                        continue;
                    }
                    else if (match_choice == "1"){
                        fight(player, monster, damages, tour);
                    }
                    else if (match_choice == "2"){
                        monster->print_acts();
                        cout << endl;
                        string act_choice;
                        getline(cin, act_choice);
                        clear();
                        if (!in_array(act_choice, 1, monster->get_acts().size())){
                            cout << "Choix invalide, veuillez réessayer." << endl;
                            cout << endl;
                            i--;
                            continue;
                        }
                        monster->act(stoi(act_choice));
                    }
                    else if (match_choice == "3"){
                        player.print_items();
                        string item_choice;
                        getline(cin, item_choice);
                        clear();
                        if (!in_array(item_choice, 1, player.get_items().size())){
                            cout << "Choix invalide, veuillez réessayer." << endl;
                            cout << endl;
                            i--;
                            continue;
                        }
                        else if(!player.use_item(stoi(item_choice))){
                            i--;
                        }
                    }
                    else if (match_choice == "4"){
                        if (!monster->spare()){
                            i--;
                            cout << "Vous ne pouvez pas epargner ce monstre pour le moment : sa jauge de pitie est a " << monster->get_current_mercy() << "/" << monster->get_mercy_goal() << endl;
                        }
                        else{
                            player.set_spared(player.get_spared() + 1);
                            cout << "Vous avez epargné " << monster->get_name() << " !" << endl;
                        }
                        cout << endl;
                    }
                }
                else{
                    tour = "monster";
                    damages = random_int(player.get_max_hp());
                    fight(player, monster, damages, tour);
                }
                next_tour();
                clear();
            }

            if (!player.is_alive()){
                cout << "Partie perdue ! Vous avez été eliminé par " << monster->get_name() << endl;
                cout << endl;

            }
            else if (!monster->is_alive()){
                cout << "Vous avez tué " << monster->get_name() << ". Partie gagnée !" << endl;
                player.set_wins(player.get_wins() + 1);
                history.push_back({monster->get_name(), monster->get_category()});
                cout << endl;
            }
            next_tour();
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
            if (!in_array(item_choice, 1, player.get_items().size())){
                cout << "Choix invalide, veuillez réessayer." << endl;
                cout << endl;
                continue;
            }
            else{
                player.use_item(stoi(item_choice));
            }
            next_tour();
        }


        else if (choice == "5"){
            cout << "Merci d'avoir joué, au revoir !" << endl;
            cout << endl;
            return 1;
        }


        if (player.get_wins() == 10){
            if (player.get_spared() == 0){
                cout << "Fin génocidaire ! Vous avez tué tous les monstres vaincus" << endl;
            }
            else if (player.get_kills() == 0){
                cout << "Fin pacifiste ! Vous avez épargné tous les monstres vaincus" << endl;
            }
            else{
                cout << "Fin neutre ! Vous avez à la fois tué et épargné les monstres" << endl;
            }
            cout << endl;
            return 1;
        }

        // next_tour();
    }

    
    return 0;
}
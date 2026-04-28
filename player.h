#ifndef PLAYER_H
#define PLAYER_H
#include "item.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
using namespace std;


class Player{
    private:
        string name;
        int max_hp;
        int current_hp;
        int kills;
        int spared;
        int wins;
        vector<Item> items;

    public:
        Player(){};
        Player(string name, vector<Item> items){
            this->name = name;
            this->max_hp = 100;
            this->current_hp = 100;
            this->kills = 0;
            this->spared = 0;
            this->wins = 0;
            this->items = items;
        }

        void stats(){
            cout << "Statistiques du joueur :" << endl;
            cout << "Nom : " << this->name << endl;
            cout << "HP : " << this->current_hp << "/" << this->max_hp << endl;
            cout << "Kills : " << this->kills << endl;
            cout << "Monstres epargnes : " << this->spared << endl;
            cout << "Victoires : " << this->wins << endl;
            cout << endl;
        }

        vector<Item> get_items(){
            return this->items;
        }

        void print_items(){
            cout << "Choisissez l'item que vous souhaitez utiliser : " << endl;
            cout << endl;
            for (int i = 0; i < this->items.size(); i++){
                cout << i+1 << ". " << this->items[i].name << " (" << this->items[i].type << " " << this->items[i].value << " HP) - " << this->items[i].quantity << " unites" << endl;
            }
        }

        bool use_item(int choice){
            if (this->current_hp >= this->max_hp){
                cout << "Vous ne pouvez pas consommer cette potion : vous avez deja " << this->current_hp << " HP" << endl;
                cout << endl;
                return false;
            }
            else if (this->items[choice-1].quantity <= 0){
                cout << "Vous n'avez plus de " << this->items[choice-1].name << " en votre possession !" << endl;
                cout << endl;
                return false;
            }
            this->items[choice-1].quantity--;
            this->current_hp += this->items[choice-1].value;
            cap_hp();
            cout << "Utilisation de " << this->items[choice-1].name << "..." << endl;
            cout << "HP : " << this->current_hp << "/" << this->max_hp << endl;
            cout << endl;
            return true;
        }

        string get_name(){
            return this->name;
        }

        int get_max_hp(){
            return this->max_hp;
        }

        int get_current_hp(){
            return this->current_hp;
        }

        int get_kills(){
            return this->kills;
        }

        int get_spared(){
            return this->spared;
        }

        int get_wins(){
            return this->wins;
        }

        bool is_alive(){
            return this->current_hp > 0;
        }

        void set_current_hp(int hp){
            this->current_hp = hp;
        }
        void set_kills(int kills){
            this->kills = kills;
        }
        void set_spared(int spared){
            this->spared = spared;
        }
        void set_wins(int wins){
            this->wins = wins;
        }

        void cap_hp(){
            if (this->current_hp > this->max_hp){
                this->current_hp = this->max_hp;
            }
            else if (this->current_hp < 0){
                this->current_hp = 0;
            }
        }

        void set_items(vector<Item> items){
            this->items = items;
        }

};

#endif
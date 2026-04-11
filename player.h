#ifndef PLAYER_H
#define PLAYER_H
#include "item.h"
#include <string>
#include <iostream>
#include <map>
using namespace std;


class Player{
    private:
        string name;
        int max_hp;
        int current_hp;
        int kills;
        int spared;
        int wins;
        map<string, Item> items;

    public:
        Player(){};
        Player(string name, map<string, Item> items){
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
            cout << "Epargnes : " << this->spared << endl;
            cout << "Victoires : " << this->wins << endl;
            cout << endl;
        }

        map<string, Item> get_items(){
            return this->items;
        }

        void print_items(){
            cout << "Items disponibles :" << endl;
            for (auto& [name, item] : this->items) {
            cout << item.name << " (" << item.type << ", +" << item.value << " HP) - " << item.quantity << " unites" << endl;
    }
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

        void set_items(string name){
            if (this->current_hp < this->max_hp){
                this->items[name].quantity--;
                this->current_hp += this->items[name].value;
                cout << "Utilisation de " << name << "..." << endl;
                cout << "HP : " << this->current_hp << "/" << this->max_hp << endl;
                cout << endl;
            }
            else{
                cout << "Vous ne pouvez pas consommer cette potion : vous avez deja " << this->current_hp << " HP" << endl;
                cout << endl;
            }
        }

        // void fight(Monster*& monster, int damages){
        //     int monster_current_hp = monster->get_current_hp();
        //     monster->set_current_hp(monster_current_hp - damages);
        // }

        // void be_fought(int damages){
        //     this->set_current_hp(this->get_current_hp() - damages);
        // }

};

#endif
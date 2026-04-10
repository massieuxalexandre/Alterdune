#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
using namespace std;


class Player{
    private:
        string name;
        int max_hp;
        int current_hp;
        int kills;
        int spared;
        int wins;

    public:
        Player(string name){
            this->name = name;
            this->max_hp = 100;
            this->current_hp = 100;
            this->kills = 0;
            this->spared = 0;
            this->wins = 0;
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

        string get_name(){
            return this->name;
        }

        int get_max_hp(){
            return this->max_hp;
        }

        int get_hp(){
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

        void set_hp(int hp){
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

};

#endif
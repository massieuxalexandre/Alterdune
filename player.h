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

        // affichage des stats du joueur
        void stats(){
            cout << "Statistiques du joueur :" << endl;
            cout << "Nom : " << this->name << endl;
            cout << "HP : " << this->current_hp << "/" << this->max_hp << endl;
            cout << "Kills : " << this->kills << endl;
            cout << "Monstres epargnes : " << this->spared << endl;
            cout << "Victoires : " << this->wins << endl;
            cout << endl;
        }


        // afficher les items que le joueur a
        void print_items(){
            cout << "Choisissez l'item que vous souhaitez utiliser : " << endl;
            cout << endl;
            for (int i = 0; i < this->items.size(); i++){
                cout << i+1 << ". " << this->items[i].name << " (" << this->items[i].type << " " << this->items[i].value << " HP) - " << this->items[i].quantity << " unites" << endl;
            }
        }

        // bornage des hp entre 0 et max_hp (=100 par défaut)
        void cap_hp(){
            if (this->current_hp > this->max_hp){
                this->current_hp = this->max_hp;
            }
            else if (this->current_hp < 0){
                this->current_hp = 0;
            }
        }

        // utilisation d'un item (choisi via l'indice = choice-1)
        bool use_item(int choice){

            // si le joueur a déjà ses hp au max, il ne peut pas consommer l'item
            if (this->current_hp >= this->max_hp){
                cout << "Vous ne pouvez pas consommer cette potion : vous avez deja " << this->current_hp << " HP" << endl;
                cout << endl;
                return false;
            }

            // si il n'y plus d'item disponible (car tous utilisés), il ne peut pas consommer l'item
            else if (this->items[choice-1].quantity <= 0){
                cout << "Vous n'avez plus de " << this->items[choice-1].name << " en votre possession !" << endl;
                cout << endl;
                return false;
            }

            // sinon, il peut la consommer, ce qui réduit sa quantité de 1
            this->items[choice-1].quantity--;

            // modification des hp selon la valeur de l'item choisi
            this->current_hp += this->items[choice-1].value;
            // bornage des hp
            cap_hp();

            // puis affichage
            cout << "Utilisation de " << this->items[choice-1].name << "..." << endl;
            cout << "HP : " << this->current_hp << "/" << this->max_hp << endl;
            cout << endl;
            return true;
        }


        // joueur en vie ou non
        bool is_alive(){
            return this->current_hp > 0;
        }


        // getters et setters
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

        vector<Item> get_items(){
            return this->items;
        }

        void set_current_hp(int hp){
            this->current_hp = hp;
            // on borne bien les hp
            cap_hp();
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

        void set_items(vector<Item> items){
            this->items = items;
        }

};

#endif
#ifndef MONSTER_H
#define MONSTER_H
#include "action.h"
#include <string>
#include <iostream>
using namespace std;


class Monster{
    protected:
        string name;
        int current_hp;
        int max_hp;
        int attack;
        int defense;
        int mercy_goal;
        // int current_mercy;
        Action act1;
        Action act2;

    public:
        Monster(){};
        Monster(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2){
            this->name = name;
            this->current_hp = hp;
            this->max_hp = hp;
            this->attack = attack;
            this->defense = defense;
            // this->current_mercy = current_mercy;
            this->mercy_goal = mercy_goal;
            this->act1 = act1;
            this->act2 = act2;
        }

        void set_current_hp(int hp){
            this->current_hp = hp;
        }

        string get_name(){
            return this->name;
        }

        int get_current_hp(){
            return this->current_hp;
        }

        int get_max_hp(){
            return this->max_hp;
        }

        bool is_alive(){
            return this->current_hp > 0;
        }

        // void fight(Player& player, int damages){
        //     int player_current_hp = player.get_current_hp();
        //     player.set_current_hp(player_current_hp - damages);
        // }

        void print_acts(){
            cout << act1.id << endl;
            cout << act2.id << endl;
        }

};

class Miniboss : public Monster{
    protected:
        Action act3;

    public:
        Miniboss(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2, Action act3) : Monster(name, hp, attack, defense, mercy_goal, act1, act2){
            this->act3 = act3;
        }

        void print_acts(){
            Monster::print_acts();
            cout << act3.id << endl;
        }

};

class Boss : public Miniboss{
    protected:
        Action act4;

    public:
        Boss(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2, Action act4) : Miniboss(name, hp, attack, defense, mercy_goal, act1, act2, act3){

            this->act4 = act4;
        }

        void print_acts(){
            Miniboss::print_acts();
            cout << act4.id << endl;
        }


};

#endif
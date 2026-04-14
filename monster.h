#ifndef MONSTER_H
#define MONSTER_H
#include "action.h"
#include <string>
#include <iostream>
#include <map>
using namespace std;


class Monster{
    protected:
        string name;
        int current_hp;
        int max_hp;
        int attack;
        int defense;
        int mercy_goal;
        int current_mercy;
        map<string, Action> acts;

    public:
        Monster() {};
        Monster(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2){
            this->name = name;
            this->current_hp = hp;
            this->max_hp = hp;
            this->attack = attack;
            this->defense = defense;
            this->mercy_goal = mercy_goal;
            this->current_mercy = this->mercy_goal/2;
            this->acts[act1.id] = act1;
            this->acts[act2.id] = act2;
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

        int get_mercy_goal(){
            return this->mercy_goal;
        }

        int get_current_mercy(){
            return this->current_mercy;
        }

        bool is_alive(){
            return this->current_hp > 0;
        }

        virtual void print_acts(){
            cout << "1. " << this->acts.begin()->second.id << endl;
            cout << "2. " << (++this->acts.begin())->second.id << endl;
        }

        void cap_mercy(){
            if (this->current_mercy > this->mercy_goal){
                this->current_mercy = this->mercy_goal;
            }
            else if (this->current_mercy < 0){
                this->current_mercy = 0;
            }
        }

        void act(int choice){
            cout << this->acts[choice-1].text << endl;
            this->current_mercy += this->acts[choice-1].impact;
            cap_mercy();
            cout << "Pitie du monstre : " << this->current_mercy << "/" << this->mercy_goal << endl;
            cout << endl;
        }

        bool spare(){
            if (this->current_mercy >= this->mercy_goal){
                this->current_hp = 0;
                return true;
            }
            return false;
        }

};

class Miniboss : public Monster{
    public:
        Miniboss(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2, Action act3) : Monster(name, hp, attack, defense, mercy_goal, act1, act2){
            this->acts[act3.id] = act3;
        }

        virtual void print_acts(){
            Monster::print_acts();
            cout << "3. " << this->acts[2].id << endl;
        }


};

class Boss : public Miniboss{
    public:
        Boss(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2, Action act3, Action act4) : Miniboss(name, hp, attack, defense, mercy_goal, act1, act2, act3){
            this->acts[act4.id] = act4;
        }

        virtual void print_acts(){
            Miniboss::print_acts();
            cout << "4. " << this->acts[3].id << endl;
        }


};

#endif
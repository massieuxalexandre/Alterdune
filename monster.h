#ifndef MONSTER_H
#define MONSTER_H
#include "action.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
using namespace std;


class Monster{
    protected:
        string name;
        string category;
        int current_hp;
        int max_hp;
        int attack;
        int defense;
        int mercy_goal;
        int current_mercy;
        vector<Action> acts;

    public:
        Monster() {};
        Monster(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2){
            this->name = name;
            this->category = "NORMAL";
            this->current_hp = hp;
            this->max_hp = hp;
            this->attack = attack;
            this->defense = defense;
            this->mercy_goal = mercy_goal;
            this->current_mercy = this->mercy_goal/2;
            this->acts.push_back(act1);
            this->acts.push_back(act2);
        }
        virtual ~Monster() {}
        virtual string get_category() = 0;

        bool is_alive(){
            return this->current_hp > 0;
        }

        void print_acts(){
            cout << "Choisissez l'action que vous souhaitez utiliser : " << endl;
            cout << endl;
            for (int i = 0; i < this->acts.size(); i++){
                cout << i+1 << ". " << this->acts[i].id << endl;
            }
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
            if (this->current_mercy < this->mercy_goal){
                return false;
            }
            this->current_hp = 0;
            return true;
        }

        void cap_hp(){
            if (this->current_hp > this->max_hp){
                this->current_hp = this->max_hp;
            }
            else if (this->current_hp < 0){
                this->current_hp = 0;
            }
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

        vector<Action> get_acts(){
            return this->acts;
        }

        void set_current_mercy(int mercy){
            this->current_mercy = mercy;
        }

        void set_current_hp(int hp){
            this->current_hp = hp;
            cap_hp();
        }

};

class NormalMonster : public Monster{
    public:
        NormalMonster(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2) : Monster(name, hp, attack, defense, mercy_goal, act1, act2) {
            this->category = "NORMAL";
        }

        string get_category() override {
            return this->category;
        }
};

class Miniboss : public Monster{
    public:
        Miniboss(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2, Action act3) : Monster(name, hp, attack, defense, mercy_goal, act1, act2){
            this->category = "MINIBOSS";
            this->acts.push_back(act3);
        }

        string get_category() override{
            return this->category;
        }
};

class Boss : public Miniboss{
    public:
        Boss(string name, int hp, int attack, int defense, int mercy_goal, Action act1, Action act2, Action act3, Action act4) : Miniboss(name, hp, attack, defense, mercy_goal, act1, act2, act3){
            this->category = "BOSS";
            this->acts.push_back(act4);
        }

        string get_category() override{
            return this->category;
        }
};

#endif
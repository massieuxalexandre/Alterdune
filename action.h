#ifndef ACTION_H
#define ACTION_H
#include <string>
#include <iostream>
using namespace std;


class Action{
public:
    // nom de l'action
    string id;

    // ce que l'action affiche
    string text;

    // quantité d'impact sur la jauge "Mercy" d'un monstre
    int impact;

    Action(){};
    Action(string id, string text, int impact){
        this->id = id;
        this->text = text;
        this->impact = impact;
    }
};


#endif
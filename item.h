#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;

class Item{
    public:
        string name;
        string type;

        // nombre de HP que va récupérer un joueur en utilisant cet item
        int value;

        // quantité disponible
        int quantity;

        Item(){};
        Item(string name, string type, int value, int quantity){
            this->name = name;
            this->type = type;
            this->value = value;
            this->quantity = quantity;
        }
};

#endif
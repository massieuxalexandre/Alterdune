#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
using namespace std;

class Item{
    public:
        string name;
        string type;
        int value;
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
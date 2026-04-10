#ifndef ACTION_H
#define ACTION_H
#include <string>
#include <iostream>
using namespace std;


class Action{
public:
    string id;
    string text;
    int impact;

    Action(){};
    Action(string id, string text, int impact){
        this->id = id;
        this->text = text;
        this->impact = impact;
    }
};


#endif
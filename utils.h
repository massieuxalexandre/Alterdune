#ifndef UTILS_H
#define UTILS_H
#include "player.h"
#include "monster.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <random>
using namespace std;

void main_menu(Player& player, map<string, Item> items){
    cout << "Bonjour " << player.get_name() << " ! " << endl;
    cout << endl;
    player.stats();
    cout << endl;
    cout << "Items disponibles :" << endl;
    for (auto& [nom, item] : items) {
        cout << item.name << " (" << item.type << ") - " << item.quantity << " unites" << endl;
    }
    cout << endl;
    cout << "Menu principal :" << endl;
    cout << "1. Bestiaire" << endl;
    cout << "2. Demarrer un combat" << endl;
    cout << "3. Statistiques du joueur" << endl;
    cout << "4. Items" << endl;
    cout << "5. Quitter" << endl;
}


void match_menu(){
    cout << "Combat en cours..." << endl;
    cout << endl;
    cout << "1. Fight" << endl;
    cout << "2. Act" << endl;
    cout << "3. Item" << endl;
    cout << "4. Mercy" << endl;
    cout << endl;
}

void fight_menu(){
    cout << "1. Fight" << endl;
    cout << "2. Act" << endl;
    cout << "3. Item" << endl;
    cout << "4. Mercy" << endl;
    cout << endl;
}


void clear(){
    for (int i = 0; i < 100; i++) {
        cout << endl;
    }
}

vector<vector<string>> load_csv(string file){
    vector<vector<string>> data;
    ifstream infile(file);
    string line;
    while (getline(infile, line)) {
        vector<string> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ';')) {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}

void bestiaire(){
    vector<vector<string>> history_data = load_csv("data/history.csv");
    cout << "Tous les monstres vaincus :" << endl;
    for (auto& row : history_data) {
        cout << row[1] << " (" << row[0] << ")" << " - Type de mort : " << row[6] << endl;
    }
    cout << endl;
}

void write_csv(string file, vector<vector<string>> data){
    ofstream outfile(file);
    for (int i = 0; i < data.size(); i++) {
        for (int j = 0; j < data[i].size(); j++) {
            outfile << data[i][j];
            if (j != data[i].size() - 1) {
                outfile << ";";
            }
        }
        outfile << endl;
    }
}

map<string, Monster*> load_monsters(string file, map<string, Action> actions){
    vector<vector<string>> monsters_data = load_csv(file);
    map<string, Monster*> monsters_map;
    for (int i = 0; i < monsters_data.size(); i++) {
        string type = monsters_data[i][0];
        string name = monsters_data[i][1];
        int hp = stoi(monsters_data[i][2]);
        int attack = stoi(monsters_data[i][3]);
        int defense = stoi(monsters_data[i][4]);
        int mercy_goal = stoi(monsters_data[i][5]);
        Action act1 = actions[monsters_data[i][6]];
        Action act2 = actions[monsters_data[i][7]];
        Action act3 = actions[monsters_data[i][8]];
        Action act4 = actions[monsters_data[i][9]];
        if (type == "NORMAL"){
            monsters_map[name] = new Monster(name, hp, attack, defense, mercy_goal, act1, act2);
        }
        else if (type == "MINIBOSS"){
            monsters_map[name] = new Miniboss(name, hp, attack, defense, mercy_goal, act1, act2, act3);
        }
        else if (type == "BOSS"){
            monsters_map[name] = new Boss(name, hp, attack, defense, mercy_goal, act1, act2, act4);
        }
    }
    return monsters_map;
}

map<string, Item> load_items(string file){
    vector<vector<string>> items_data = load_csv(file);
    map<string, Item> items_map;
    for (int i = 0; i < items_data.size(); i++) {
        string name = items_data[i][0];
        string type = items_data[i][1];
        int value = stoi(items_data[i][2]);
        int quantity = stoi(items_data[i][3]);
        items_map[name] = Item(name, type, value, quantity);
    }
    return items_map;
}

map<string, Action> load_actions(vector<vector<string>> actions_data){
    map<string, Action> actions_map;
    for (int i = 0; i < actions_data.size(); i++){
        string id = actions_data[i][0];
        string text = actions_data[i][1];
        int impact = stoi(actions_data[i][2]);
        actions_map[id] = Action(id, text, impact);
    }
    return actions_map;
}

void go_back(){
    cout << "N'importe quelle touche + ENTREE pour retourner" << endl;
    string back;
    getline(cin, back);
    clear();
}

int random_damages(int max) {
    int min = 0;
    static random_device rd;
    static mt19937 gen(rd());
    
    uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}

void fight(Player& player, Monster* monster, int damages, string tour){
    if (tour == "player"){
        monster->set_current_hp(monster->get_current_hp() - damages);
    }
    else if (tour == "monster"){
        player.set_current_hp(player.get_current_hp() - damages);
    }
}

#endif
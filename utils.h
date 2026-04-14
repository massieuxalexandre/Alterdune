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

void main_menu(Player& player){
    cout << "Bonjour " << player.get_name() << " ! " << endl;
    cout << endl;
    player.stats();
    cout << "Items disponibles :" << endl;
    for (int i = 0; i < player.get_items().size(); i++){
        cout << i+1 << ". " << player.get_items()[i].name << " (" << player.get_items()[i].type << " " << player.get_items()[i].value << " HP) - " << player.get_items()[i].quantity << " unités" << endl;
    }
    cout << endl;
    cout << "Menu principal :" << endl;
    cout << endl;
    cout << "1. Bestiaire" << endl;
    cout << "2. Démarrer un combat" << endl;
    cout << "3. Statistiques du joueur" << endl;
    cout << "4. Items" << endl;
    cout << "5. Quitter" << endl;
    cout << endl;
}


void match_menu(string monster_name){
    cout << "A votre tour de jouer. Choisissez ce que vous voulez faire : " << endl;
    cout << endl;
    cout << "1. Combattre" << endl;
    cout << "2. Actions" << endl;
    cout << "3. Items" << endl;
    cout << "4. Epargner le monstre" << endl;
    cout << endl;
}


void clear(){
    // cout << "\033[2J\033[H" << flush;
    for (int i = 0; i < 100; i++){
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

void bestiaire(vector<vector<string>> history_data){
    if (history_data.size() == 0){
        cout << "Vous n'avez encore vaincu aucun monstre." << endl;
        cout << endl;
        return;
    }

    cout << "Tous les monstres vaincus :" << endl;
    for (int i = 0; i < history_data.size(); i++){
        cout << history_data[i][0] << " (" << history_data[i][1] << ") - " << history_data[i][2] << endl;
    }
    cout << endl;
}

vector<Monster*> load_monsters(string file, map<string, Action> actions){
    vector<vector<string>> monsters_data = load_csv(file);
    vector<Monster*> monsters_vector;
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
            monsters_vector.push_back(new Monster(name, hp, attack, defense, mercy_goal, act1, act2));
        }
        else if (type == "MINIBOSS"){
            monsters_vector.push_back(new Miniboss(name, hp, attack, defense, mercy_goal, act1, act2, act3));
        }
        else if (type == "BOSS"){
            monsters_vector.push_back(new Boss(name, hp, attack, defense, mercy_goal, act1, act2, act3, act4));
        }
    }
    return monsters_vector;
}

vector<Item> load_items(string file){
    vector<vector<string>> items_data = load_csv(file);
    vector<Item> items_vector;
    for (int i = 0; i < items_data.size(); i++) {
        string name = items_data[i][0];
        string type = items_data[i][1];
        int value = stoi(items_data[i][2]);
        int quantity = stoi(items_data[i][3]);
        items_vector.push_back(Item(name, type, value, quantity));
    }
    return items_vector;
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


void next_tour(){
    cout << "Appuyez sur 'ENTREE' pour continuer" << endl;
    string back;
    getline(cin, back);
    clear();
}

int random_int(int max) {
    int min = 0;
    static random_device rd;
    static mt19937 gen(rd());
    
    uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}


void fight(Player& player, Monster* monster, int damages, string tour){
    if (tour == "player"){
        monster->set_current_hp(monster->get_current_hp() - damages);
        cout << "Attaque de " << player.get_name() << " envers " << monster->get_name() << endl;
        cout << "Dégats émis : " << damages << endl;
        if (monster->is_alive()){
            cout << "HP de " << monster->get_name() << " : " << monster->get_current_hp() << "/" << monster->get_max_hp() << endl;
        }
        else {
            monster->cap_hp();
            cout << "HP de " << monster->get_name() << " : " << monster->get_current_hp() << "/" << monster->get_max_hp() << endl;
            player.set_kills(player.get_kills() + 1);
        }
    }
    else if (tour == "monster"){
        player.set_current_hp(player.get_current_hp() - damages);
        cout << monster->get_name() << " vous attaque !" << endl;
        cout << "Dégats encaissés : " << damages << endl;
        if (player.is_alive()){
            cout << "Vos HP : " << player.get_current_hp() << "/" << player.get_max_hp() << endl;
        }
        else {
            player.cap_hp();
            cout << "Vos HP : " << player.get_current_hp() << "/" << player.get_max_hp() << endl;
        }
    }
    cout << endl;
}

bool in_array(string value, int start, int end){
    vector<string> arr;
    for (int i = start; i <= end; i++){
        arr.push_back(to_string(i));
    }
    cout << endl;
    for (int i = 0; i < arr.size(); i++){
        if (arr[i] == value){
            return true;
        }
    }
    return false;
}


#endif
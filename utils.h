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

// affichage du menu principal
void main_menu(Player& player){
    cout << "Bonjour " << player.get_name() << " ! " << endl;
    cout << endl;
    player.stats();
    cout << "Items disponibles :" << endl;
    for (int i = 0; i < player.get_items().size(); i++){
        cout << i+1 << ". " << player.get_items()[i].name << " (" << player.get_items()[i].type << " " << player.get_items()[i].value << " HP) - " << player.get_items()[i].quantity << " unites" << endl;
    }
    cout << endl;
    cout << "Menu principal :" << endl;
    cout << endl;
    cout << "1. Bestiaire" << endl;
    cout << "2. Demarrer un combat" << endl;
    cout << "3. Statistiques du joueur" << endl;
    cout << "4. Items" << endl;
    cout << "5. Quitter" << endl;
    cout << endl;
}


// affichage du menu de combat
void match_menu(string monster_name){
    cout << "A votre tour de jouer. Choisissez ce que vous voulez faire : " << endl;
    cout << endl;
    cout << "1. Combattre" << endl;
    cout << "2. Actions" << endl;
    cout << "3. Items" << endl;
    cout << "4. Epargner le monstre" << endl;
    cout << endl;
}


// affichage du bestiaire
void bestiaire(vector<vector<string>> history_data){
    if (history_data.size() == 0){
        cout << "Vous n'avez encore vaincu aucun monstre." << endl;
        cout << endl;
        return;
    }

    cout << "Tous les monstres vaincus :" << endl;
    cout << endl;
    for (int i = 0; i < history_data.size(); i++){
        cout << history_data[i][0] << " (" << history_data[i][1] << ") - " << history_data[i][2] << endl;
    }
    cout << endl;
}


// clear le terminal pour une meilleure lisibilité
void clear(){
    for (int i = 0; i < 100; i++){
        cout << endl;
    }
}


// parser un .csv grâce aux librairies <fstream> et <sstream>
vector<vector<string>> load_csv(string file){
    ifstream infile(file);

    // gestion de l'erreur d'ouverture du fichier
    if (!infile.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier " + file);
    }
    
    // si le fichier est bien ouvert, on peut parser le .csv
    vector<vector<string>> data;
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


// charger les monstres depuis le .csv et créer leurs objets
vector<Monster*> load_monsters(string file, map<string, Action> actions){
    vector<vector<string>> monsters_data = load_csv(file);

    // tableau de pointeurs qui contiendra tous les objets monstres
    vector<Monster*> monsters_vector;

    for (int i = 0; i < monsters_data.size(); i++) {
        string type = monsters_data[i][0];
        string name = monsters_data[i][1];
        int hp = stoi(monsters_data[i][2]);
        // int attack = stoi(monsters_data[i][3]);
        // int defense = stoi(monsters_data[i][4]);
        int attack = 0;
        int defense = 0;
        int mercy_goal = stoi(monsters_data[i][3]);
        Action act1 = actions[monsters_data[i][4]];
        Action act2 = actions[monsters_data[i][5]];
        Action act3 = actions[monsters_data[i][6]];
        Action act4 = actions[monsters_data[i][7]];
        if (type == "NORMAL"){
            monsters_vector.push_back(new NormalMonster(name, hp, attack, defense, mercy_goal, act1, act2));
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


// charger les items depuis le .csv et créer leur objets
vector<Item> load_items(string file){
    vector<vector<string>> items_data = load_csv(file);

    // tableau qui contiendra tous les items
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


// charger les actions depuis la liste créée dans le main
map<string, Action> load_actions(vector<vector<string>> actions_data){
    // map qui contiendra toutes les actions (key = nom, value = objet)
    map<string, Action> actions_map;
    for (int i = 0; i < actions_data.size(); i++){
        string id = actions_data[i][0];
        string text = actions_data[i][1];
        int impact = stoi(actions_data[i][2]);
        actions_map[id] = Action(id, text, impact);
    }
    return actions_map;
}

// l'utilisateur appuie sur entrée pour avancer (cela permet de laisser afficher les infos d'une durée que l'utilisateur choisit)
void next_tour(){
    cout << "Appuyez sur 'ENTREE' pour continuer" << endl;
    string back;
    getline(cin, back);
    clear();
}

// fonction random qui retourne un entier entre 0 et max (donné en paramètre)
// grace à la librairie <random>
int random_int(int max) {
    int min = 0;
    static random_device rd;
    static mt19937 gen(rd());
    
    uniform_int_distribution<int> distrib(min, max);
    return distrib(gen);
}


// retourne si le choix est bien valide
// string choice = le choix entré par l'utilisateur (string car plus facile à gérer grâce a getline())
// int start et int end => bornes des choix valides
bool valid_choice(string choice, int start, int end){
    // on créé un tableau comprenant toutes les valeurs possibles
    // converties en string afin de comparer avec le choix
    vector<string> arr;
    for (int i = start; i <= end; i++){
        arr.push_back(to_string(i));
    }
    cout << endl;

    // si le choix fait partie du tableau, alors il est valide
    for (int i = 0; i < arr.size(); i++){
        if (arr[i] == choice){
            return true;
        }
    }

    // sinon choix invalide
    return false;
}


#endif
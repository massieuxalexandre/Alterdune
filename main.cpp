#include "player.h"
#include "monster.h"
#include "item.h"
#include "action.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

// fonction gérant le combat entre un joueur et un monstre
void fight(Player& player, Monster* monster, int damages, string tour){
    if (tour == "player"){
        // si c'est le joueur qui attaque, on modifie donc les hp du monstre (on lui retire la valeur "damages")
        monster->set_current_hp(monster->get_current_hp() - damages);
        cout << "Attaque de " << player.get_name() << " envers " << monster->get_name() << endl;
        cout << "Degats emis : " << damages << endl;

        // si le monstre est toujours en vie, on affiche ses hp restants
        if (monster->is_alive()){
            cout << "HP de " << monster->get_name() << " : " << monster->get_current_hp() << "/" << monster->get_max_hp() << endl;
        }
        // sinon, on borne ses hp afin d'afficher 0 hp (et pas une valeur négative)
        else {
            monster->cap_hp();
            cout << "HP de " << monster->get_name() << " : " << monster->get_current_hp() << "/" << monster->get_max_hp() << endl;
            // on ajoute +1 au nombre de kills du joueur
            player.set_kills(player.get_kills() + 1);
        }


    }
    else if (tour == "monster"){
        // si c'est le tour du monstre, on retire la valeur "damages" aux hp du joueur
        player.set_current_hp(player.get_current_hp() - damages);
        cout << monster->get_name() << " vous attaque !" << endl;
        cout << "Degats encaisses : " << damages << endl;

        // si le joueur est toujours en vie, on affiche ses hp restants
        if (player.is_alive()){
            cout << "Vos HP : " << player.get_current_hp() << "/" << player.get_max_hp() << endl;
        }
        // sinon, on borne ses hp afin d'afficher 0 hp (et pas une valeur négative)
        else {
            player.cap_hp();
            cout << "Vos HP : " << player.get_current_hp() << "/" << player.get_max_hp() << endl;
        }
    }
    cout << endl;
}



int main() {
    // comme indiqué dans le sujet, nous devons définir les actions du jeu sous forme de vector
    vector<vector<string>> actions_data = {
                                            {"COMPLIMENT", "Tu dis a Froggit qu'il a une jolie peau.", "10"},
                                            {"DISCUSS", "Vous parlez de la pluie et du beau temps.", "20"}, 
                                            {"OBSERVE", "Tu analyses les mouvements de la boite.", "0"},
                                            {"PET", "Tu caresses doucement le couvercle.", "40"},
                                            {"OFFER_SNACK", "Tu jettes un morceau de pain dans la boite.", "60"},
                                            {"REASON", "Tu tentes de lui expliquer que la violence est inutile.", "10"},
                                            {"DANCE", "Tu lances une battle de danse endiablee !", "30"},
                                            {"JOKE", "Tu racontes une blague sur les processeurs.", "-20"},
                                            {"INSULT", "Tu lui dis que son code est mal indente.", "-50"}
};

    // on charge les .csv puis on créé les objets Monster, Action, Item, Player.
    // les objets actions se trouvent dans un map. Cela permet de retrouver les actions par leur noms directement
    map<string, Action> actions = load_actions(actions_data);

    // les objets montres et items se trouvent dans des vecteurs. cela permet de les retrouver avec leur indices.
    // c'est utile pour tirer un monstre aléatoirement pour les combats et pour afficher et faire utiliser les items au joueur.
    vector<Monster*> monsters = load_monsters("data/monsters.csv", actions);
    vector<Item> items = load_items("data/items.csv");
    
    // histrorique des victoires (pour afficher quel monstre a été battu et par quel moyen). historique bien évidemment vide au début.
    vector<vector<string>> history;



    // on créé un objet Player avec comme nom celui entré par l'utilisateur
    cout << "Bienvenue dans Alterdune !" << endl;
    cout << "Entrez votre nom : ";
    string player_name;
    getline(cin, player_name);
    Player player(player_name, items);
    clear();
    

    // boucle principale. Tant que le joueur n'a pas 10 victoires, il peut faire un nouveau combat
    while (player.get_wins() < 10){
        // que ca soit la première partie ou une nouvelle partie, on redéfinit bien les hp du joueurs à 100
        player.set_current_hp(player.get_max_hp());
        // on lui redonne bien tous les items (car après une partie ils sont utilisés)
        player.set_items(items);

        // affichage du menu principal, le joueur à 5 choix (voir main_menu() dans utils.h)
        main_menu(player);
        string choice;
        getline(cin, choice);
        clear();

        // si l'utilisateur ne choisit pas un nombre entre 1 et 5, affichage d'erreur et il peut recommencer.
        // le "continue" permet de recommencer la boucle en ignorant tout le reste (donc ne compte pas le tour)
        if (!valid_choice(choice, 1, 5)){
            cout << "Choix invalide, veuillez reessayer." << endl;
            cout << endl;
            continue;
        }

        // choix 1 = affichage du bestiaire
        if (choice == "1"){
            bestiaire(history);
            next_tour();
        }

        // choix 2 = démarrer un combat
        else if (choice == "2"){
            // on génère un index aléatoire parmi le Vector contenant les objets Monstres
            // (voir random_int() dans utils.h)
            int random_index_monster = random_int(monsters.size()-1);
            // on selectionne donc ce monstre et on le reset avec full hp, on reset sa jauge de mercy (car ce monstre peu etre tué dans une autre partie, il faut donc tout reset)
            Monster* monster = monsters[random_index_monster];
            monster->set_current_hp(monster->get_max_hp());
            monster->set_current_mercy(monster->get_mercy_goal()/2);
            cout << "C'est parti " << player.get_name() << " ! Vous allez jouer contre le monstre " << monster->get_name() << endl;
            int tour = 0;
            int damages;

            
            while(player.is_alive() && monster->is_alive()){
                // tour pair = le joueur joue
                if (tour % 2 == 0){
                    // on affiche le menu de combat (voir match_menu() dans utils.h)
                    match_menu(monster->get_name());
                    string match_choice;
                    getline(cin, match_choice);

                    // on génère les dégats que le joueur peut faire (random entre 0 et les hp max du monstre)
                    damages = random_int(monster->get_max_hp());
                    clear();

                    // si choix invalide, on affiche l'erreur et le joueur peut réessayer
                    if (!valid_choice(match_choice, 1, 4)){
                        cout << "Choix invalide, veuillez reessayer." << endl;
                        cout << endl;
                        continue;
                    }

                    // choix 1 = combattre (voir fonction fight() en haut de ce fichier)
                    else if (match_choice == "1"){
                        fight(player, monster, damages, "player");
                    }

                    // choix 2 = action
                    else if (match_choice == "2"){
                        // on affiche les actions qu'on peut faire sur le monstre de cette partie
                        monster->print_acts();
                        cout << endl;
                        string act_choice;
                        getline(cin, act_choice);
                        clear();

                        // le joueur doit bien chosir "l'indice" de l'action qu'il veut faire
                        // si choix invalide, il peut recommencer
                        if (!valid_choice(act_choice, 1, monster->get_acts().size())){
                            cout << "Choix invalide, veuillez reessayer." << endl;
                            cout << endl;
                            continue;
                        }
                        monster->act(stoi(act_choice));
                    }

                    // choix 3 = afficher les items du joueur et il peut les utiliser
                    else if (match_choice == "3"){
                        player.print_items();
                        string item_choice;
                        getline(cin, item_choice);
                        clear();

                        // le joueur dois choisir "l'indice de l'item" (car les obets Item sont dans un Vector).
                        // si choix invalide, il peut recommencer
                        if (!valid_choice(item_choice, 1, player.get_items().size())){
                            cout << "Choix invalide, veuillez reessayer." << endl;
                            cout << endl;
                            continue;
                        }
                        else if(!player.use_item(stoi(item_choice))){

                        }
                    }

                    // choix 4 = éparger le monstre
                    else if (match_choice == "4"){

                        // on vérifie d'abord si la jauge de mercy a atteint son "mercy goal" grâce a la méthode spare() (return un boolean)
                        if (!monster->spare()){
                            cout << "Vous ne pouvez pas epargner ce monstre pour le moment : sa jauge de pitie est a " << monster->get_current_mercy() << "/" << monster->get_mercy_goal() << endl;
                        }
                        else{
                            // on ajoute le nombre de monstre épargné de "+1" au joueur
                            // et on ajoute à l'historique le monstre battu, sa catégorie et par quel moyen il est éliminé (ici Epargné)
                            player.set_spared(player.get_spared() + 1);
                            cout << "Vous avez epargne " << monster->get_name() << " !" << endl;
                            history.push_back({monster->get_name(), monster->get_category(), "Epargne"});
                        }
                        cout << endl;
                    }
                }

                // tour impair, le monstre joue (attaque)
                else{
                    damages = random_int(player.get_max_hp());
                    fight(player, monster, damages, "monster");
                }
                next_tour();
                clear();
                tour++;
            }

            // joueur mort = fin de partie et on affiche quel monstre l'a battu
            if (!player.is_alive()){
                cout << "Partie perdue ! Vous avez ete elimine par " << monster->get_name() << endl;
                cout << endl;

            }

            // monstre mort : on ajoute 1 win au joueur 
            // et on ajoute à l'historique le monstre battu, sa catégorie et par quel moyen il est éliminé (ici tué)
            else if (!monster->is_alive()){
                cout << "Vous avez tue " << monster->get_name() << ". Partie gagnee !" << endl;
                player.set_wins(player.get_wins() + 1);
                history.push_back({monster->get_name(), monster->get_category(), "Tue"});
                cout << endl;
            }
            next_tour();
        }


        // choix 3 = afficher les stats du joueur
        else if (choice == "3"){
            player.stats();
            next_tour();
        }

        // choix 4 = afficher les items du joueur et il peut les utiliser
        else if (choice == "4"){
            player.print_items();
            string item_choice;
            getline(cin, item_choice);
            clear();

            // le joueur dois choisir "l'indice de l'item" (car les obets Item sont dans un Vector).
            // si choix invalide, il peut recommencer
            if (!valid_choice(item_choice, 1, player.get_items().size())){
                cout << "Choix invalide, veuillez reessayer." << endl;
                cout << endl;
                continue;
            }
            else{
                player.use_item(stoi(item_choice));
            }
            next_tour();
        }


        // choix 5 = quitter le jeu (break = fin de la boucle principale)
        else if (choice == "5"){
            cout << "Merci d'avoir joue, au revoir !" << endl;
            cout << endl;
            break;
        }
        
    }

    // après 10 wins on définit le type de fin de partie
    // on vérifie quand même si le joueur à 10 wins car il peut choisir d'arrêter de jouer avant et donc finir la boucle while précédente
    if (player.get_wins() == 10){
        if (player.get_spared() == 0){
            cout << "Fin genocidaire ! Vous avez tue tous les monstres vaincus" << endl;
        }
        else if (player.get_kills() == 0){
            cout << "Fin pacifiste ! Vous avez epargne tous les monstres vaincus" << endl;
        }
        else{
            cout << "Fin neutre ! Vous avez a la fois tue et epargne les monstres" << endl;
        }
        cout << endl;
    }
        
    // libération de la mémoire
    for(Monster* m: monsters){
        delete m;
    }
    return 0;
}
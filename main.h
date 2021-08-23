//
// Created by kvitadmin on 23.08.2021.
//

#ifndef HOMEWORK21_5_4_MAIN_H
#define HOMEWORK21_5_4_MAIN_H
#include <vector>
#include <string>
#include <ctime>
#include <array>

struct player{
    std::string name;
    bool enemy = true;
    int armor = 0;
    int damage = 0;
    int health = 0;
    int curX = 0;
    int curY = 0;
};
bool GenerateCoordinates(std::vector<player>& players){
    std::srand(std::time(nullptr));
    bool result;
    do{
        result = true;
        players.at(players.size()-1).curX = std::rand() % 40;
        players.at(players.size()-1).curY = std::rand() % 40;
        for(int i = 0; i < players.size()-1; ++i) {
            if(players.at(i).curX == players.at(players.size()-1).curX &&
            players.at(i).curY == players.at(players.size()-1).curY){
                result = false;
                break;
            }
        }
    } while (!result);
    return true;
}
bool GenerateEnemy(std::vector<player>& players){
    std::srand(std::time(nullptr));
    if(players.empty()){
        std::cout << "Human player is empty()" << std::endl;
        return false;
    }
    player tmpPlayer;
    for(int i = 1; i < 6; ++i){
        tmpPlayer.name = "enemy#" + std::to_string(i);
        tmpPlayer.armor = std::rand() % 51;
        tmpPlayer.damage = 15 + std::rand() % 16;
        tmpPlayer.health = 50 + std::rand() % 101;
        tmpPlayer.enemy = true;
        players.push_back(tmpPlayer);
        GenerateCoordinates(players);
    }
}

void DisplayPole(std::vector<player>& players){
    std::cout << "Current position: " << std::endl;
    for(int i =0; i < 40; ++i){
        for(int j = 0; j < 40; ++j){
            bool curPos = true;
            for(auto el : players){
                if(el.curX == j && el.curY == i){
                    if(el.enemy) {std::cout <<"E"; curPos = false; break;}
                    else {std::cout << "P"; curPos = false; break;}
                }
            }
            if(curPos) std::cout << ".";
        }
        std::cout << std::endl;
    }

}

#endif //HOMEWORK21_5_4_MAIN_H

//
// Created by kvitadmin on 24.08.2021.
//

#ifndef HOMEWORK21_5_4_MAIN_H
#define HOMEWORK21_5_4_MAIN_H
#include <vector>
#include <string>
#include <ctime>
#include <array>
#include <algorithm>
#include <fstream>

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

bool CheckCommand(std::vector<std::string>& commandVector, std::string& command){
    if(std::find(commandVector.begin(),commandVector.end(), command) == commandVector.end())
        return false;
    else return true;
}

bool SaveGame(std::vector<player>& players, std::string& fileName){
    std::ofstream outFile(fileName, std::ios::binary);
    if(!outFile.is_open()) return false;
    else{
        for(int i = 0; i < players.size(); ++i){
            outFile.write(players[i].name.c_str(), sizeof(players[i].name));
            outFile.write(reinterpret_cast<char*>(&players[i].enemy), sizeof(players[i].enemy));
            outFile.write(reinterpret_cast<char*>(&players[i].armor), sizeof(players[i].armor));
            outFile.write(reinterpret_cast<char*>(&players[i].damage), sizeof(players[i].damage));
            outFile.write(reinterpret_cast<char*>(&players[i].health), sizeof(players[i].health));
            outFile.write(reinterpret_cast<char*>(&players[i].curX), sizeof(players[i].curX));
            outFile.write(reinterpret_cast<char*>(&players[i].curY), sizeof(players[i].curY));
        }
        outFile.close();
        return true;
    }
}

bool LoadGame(std::vector<player>& players, std::string& fileName){
    std::ifstream outFile(fileName, std::ios::binary);
    if(!outFile.is_open()) return false;
    else{
        for(auto el : players){
            outFile.read(const_cast<char*>(el.name.c_str()), sizeof(el.name));
            outFile.read(reinterpret_cast<char*>(&el.enemy), sizeof(el.enemy));
            outFile.read(reinterpret_cast<char*>(&el.armor), sizeof(el.armor));
            outFile.read(reinterpret_cast<char*>(&el.damage), sizeof(el.damage));
            outFile.read(reinterpret_cast<char*>(&el.health), sizeof(el.health));
            outFile.read(reinterpret_cast<char*>(&el.curX), sizeof(el.curX));
            outFile.read(reinterpret_cast<char*>(&el.curY), sizeof(el.curY));
        }
        outFile.close();
        return true;
    }
}
#endif //HOMEWORK21_5_4_MAIN_H

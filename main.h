//
// Created by kvitadmin on 24.08.2021.
//

#ifndef HOMEWORK21_5_4_MAIN_H
#define HOMEWORK21_5_4_MAIN_H
#define MAX_X   20
#define MAX_Y   20
//#define DEBUG

#include <vector>
#include <array>
#include <string>
#include <ctime>
#include <array>
#include <algorithm>
#include <fstream>

enum {
    LEFT = 0,
    RIGHT,
    TOP,
    BOTTOM
};

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
        players.at(players.size()-1).curX = std::rand() % MAX_X;
        players.at(players.size()-1).curY = std::rand() % MAX_Y;
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
void ClearScreen(){
    std::cout <<  "\033[2J";
}
void SetCursorHome(){
    std::cout <<  "\033[H";
}
void SetCursor(int x, int y){
    std::cout << "\033[" << y << ";" << x << "H";
}
void DisplayPole(std::vector<player>& players, bool& curError, std::string& errorStr){
    ClearScreen();
    SetCursorHome();
    std::cout << "Current position: " << std::endl;
    for(int i =0; i < MAX_Y; ++i){
        for(int j = 0; j < MAX_X; ++j){
            bool curPos = true;
            for(auto el : players){
                if(el.curX == j && el.curY == i && el.health > 0){
                    if(el.enemy) {std::cout <<"E"; curPos = false; break;}
                    else {std::cout << "P"; curPos = false; break;}
                }
            }
            if(curPos) std::cout << ".";
        }
        std::cout << std::endl;
    }
    if(curError){
        SetCursor(MAX_X+5, MAX_Y-7);
        std::cout << "Error: " << errorStr;
        curError = false;
    }
#ifndef DEBUG
    /*SetCursor(MAX_X+5, 2);
    std::cout << players[0].curX << "--" << players[0].curY;
    SetCursor(MAX_X+5, 3);
    std::cout << players[1].curX << "--" << players[1].curY;
    SetCursor(MAX_X+5, 4);
    std::cout << players[2].curX << "--" << players[2].curY;
    SetCursor(MAX_X+5, 5);
    std::cout << players[3].curX << "--" << players[3].curY;
    SetCursor(MAX_X+5, 6);
    std::cout << players[4].curX << "--" << players[4].curY;
    SetCursor(MAX_X+5, 7);
    std::cout << players[5].curX << "--" << players[5].curY;*/

    SetCursor(MAX_X+5, MAX_Y-5);
    std::cout << "Player : health=" << players[0].health << ", armor=" << players[0].armor
    << ", damage=" << players[0].damage;
    SetCursor(MAX_X+5, MAX_Y-4);
    if(players[1].health <= 0) std::cout << "Enemy#1 is killed!";
    else std::cout << "Enemy#1: health=" << players[1].health << ", armor=" << players[1].armor
    << ", damage=" << players[1].damage;
    SetCursor(MAX_X+5, MAX_Y-3);
    if(players[2].health <= 0) std::cout << "Enemy#2 is killed!";
    else std::cout << "Enemy#2: health="<< players[2].health << ", armor=" << players[2].armor
    << ", damage=" << players[2].damage;
    SetCursor(MAX_X+5, MAX_Y-2);
    if(players[3].health <= 0) std::cout << "Enemy#3 is killed!";
    else std::cout << "Enemy#3: health="<< players[3].health << ", armor=" << players[3].armor
    << ", damage=" << players[3].damage;
    SetCursor(MAX_X+5, MAX_Y-1);
    if(players[4].health <= 0) std::cout << "Enemy#4 is killed!";
    else std::cout << "Enemy#4: health=" << players[4].health << ", armor=" << players[4].armor
    << ", damage=" << players[4].damage;
    SetCursor(MAX_X+5, MAX_Y);
    if(players[5].health <= 0) std::cout << "Enemy#5 is killed!";
    else std::cout << "Enemy#5: health="<< players[5].health << ", armor=" << players[5].armor
    << ", damage=" << players[5].damage;
    SetCursor(0, MAX_Y+3);
#endif
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
            int num = players[i].name.size();
            outFile.write(reinterpret_cast<const char*>(&num), sizeof(num));
            outFile.write(static_cast<const char*>(players[i].name.c_str()), players[i].name.size());
            outFile.write(reinterpret_cast<const char*>(&players[i].enemy), sizeof(players[i].enemy));
            outFile.write(reinterpret_cast<const char*>(&players[i].health), sizeof(players[i].health));
            outFile.write(reinterpret_cast<const char*>(&players[i].damage), sizeof(players[i].damage));
            outFile.write(reinterpret_cast<const char*>(&players[i].armor), sizeof(players[i].armor));
            outFile.write(reinterpret_cast<const char*>(&players[i].curX), sizeof(players[i].curX));
            outFile.write(reinterpret_cast<const char*>(&players[i].curY), sizeof(players[i].curY));
        }
        outFile.close();
        return true;
    }
}
bool LoadGame(std::vector<player>& players, std::string& fileName){
    std::ifstream outFile(fileName, std::ios::binary);
    if(!outFile.is_open()) return false;
    else{

        for(int i = 0; i < players.size(); ++i){
            char tmp[32]={0};
            int num;
            outFile.read((char*)&num, sizeof(num));
            outFile.read(tmp, num);
            players[i].name = tmp;
            outFile.read(reinterpret_cast<char*>(&players[i].enemy), sizeof(players[i].enemy));
            outFile.read(reinterpret_cast<char*>(&players[i].health), sizeof(players[i].health));
            outFile.read(reinterpret_cast<char*>(&players[i].damage), sizeof(players[i].damage));
            outFile.read(reinterpret_cast<char*>(&players[i].armor), sizeof(players[i].armor));
            outFile.read(reinterpret_cast<char*>(&players[i].curX), sizeof(players[i].curX));
            outFile.read(reinterpret_cast<char*>(&players[i].curY), sizeof(players[i].curY));
        }
        outFile.close();
        return true;
    }
}
void ExecuteCommand(std::string& command, std::vector<player>& players, bool& curError, std::string& errorStr){
    int x = players[0].curX, y = players[0].curY;
    if(command == "left"){
        x = players[0].curX - 1;
        if(x < 0){
            curError = true;
            errorStr =  "Bad command. No free space!";
            return;
        }
    }
    if(command == "right"){
        x = players[0].curX + 1;
        if(x > (MAX_X-1)){
            curError = true;
            errorStr =  "Bad command. No free space!";
            return;
        }
    }
    if(command == "top"){
        y = players[0].curY - 1;
        if(y < 0){
            curError = true;
            errorStr =  "Bad command. No free space!";
            return;
        }
    }
    if(command == "bottom"){
        y = players[0].curY + 1;
        if(y > (MAX_Y-1)){
            curError = true;
            errorStr =  "Bad command. No free space!";
            return;
        }
    }
    players[0].curX = x;
    players[0].curY = y;
    for(int i = 1; i < players.size(); ++i){
        if(players[i].curX == players[0].curX && players[i].curY == players[0].curY){
            if(players[i].health <= 0) continue;
            if(players[0].damage < players[i].armor){
                players[i].armor -= players[0].damage;
            }
            else{
                players[i].health += players[i].armor - players[0].damage;
                players[i].armor = 0;
                if(players[i].health <= 0){
                    //std::cout << "enemy#" << i << " is killed!" << std::endl;
                }
            }
        }
    }

}
void CheckEndGame(bool& endGame, std::vector<player>& players){
    int sum = 5;
    if(players[0].health <= 0) endGame = true;
    else{
        for(int i = 1; i < players.size(); ++i){
            if(players[i].health <= 0) sum--;
        }
        if(!sum) endGame = true;
    }
}
bool CheckEnemyStep(int x, int y, std::vector<player>& players){
    for(int i = 1; i < players.size(); ++i){
        if(players[i].curX == x && players[i].curY == y) return false;
    }
    return true;
}
void CheckHit(std::vector<player>& players){
    for(int i = 1; i < players.size(); ++i){
        if(players[i].curX == players[0].curX && players[i].curY == players[0].curY){
            if(players[i].health <= 0) continue;
            if(players[i].damage < players[0].armor){
                players[0].armor -= players[i].damage;
            }
            else{
                players[0].health += players[0].armor - players[i].damage;
                players[0].armor = 0;
            }
        }
    }
}
void GenerateStepsEnemy(std::vector<player>& players){
    std::array<int,5> motion;
    std::srand(std::time(nullptr));
    for(int i =0; i < motion.size(); ++i) motion.at(i) = std::rand() % 4;
    for(int i = 1; i < players.size(); ++i){
        int x = players[i].curX, y = players[i].curY;
        switch(motion.at(i-1)){
            case LEFT:
                x = players[i].curX - 1;
                if(x < 0) break;
                if(CheckEnemyStep(x, y, players))
                players[i].curX = x;
                break;
            case RIGHT:
                x = players[i].curX + 1;
                if(x > (MAX_X - 1)) break;
                if(CheckEnemyStep(x, y, players))
                players[i].curX = x;
                break;
            case TOP:
                y = players[i].curY - 1;
                if(y < 0) break;
                if(CheckEnemyStep(x, y, players))
                players[i].curY = y;
                break;
            case BOTTOM:
                y = players[i].curY + 1;
                if(y > (MAX_Y - 1)) break;
                if(CheckEnemyStep(x, y, players))
                players[i].curY = y;
                break;
        }
    }
    CheckHit(players);

}
#endif //HOMEWORK21_5_4_MAIN_H

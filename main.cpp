#include <iostream>
#include "main.h"

int main() {

    std::string fileNameToSaveGame = "../game.bin", command;
    std::vector<player> players;
    player tmpPlayer;
    bool correctInput;
    std::cout << "Input your name: ";
    std::cin >> tmpPlayer.name;
    tmpPlayer.enemy = false;
    do{
        correctInput = true;
        std::cout << "Input your health (50 - 150):";
        std::cin >> tmpPlayer.health;
        if(tmpPlayer.health < 50 || tmpPlayer.health > 150){
            std::cout << "Bad input!. Try again!" << std::endl;
            correctInput =false;
        }
    }while(!correctInput);
    do{
        correctInput = true;
        std::cout << "Input your damage (15 - 30):";
        std::cin >> tmpPlayer.damage;
        if(tmpPlayer.damage < 15 || tmpPlayer.damage > 30){
            std::cout << "Bad input!. Try again!" << std::endl;
            correctInput =false;
        }
    }while(!correctInput);
    do{
        correctInput = true;
        std::cout << "Input your armor (0 - 50):";
        std::cin >> tmpPlayer.armor;
        if(tmpPlayer.armor < 0 || tmpPlayer.armor > 50){
            std::cout << "Bad input!. Try again!" << std::endl;
            correctInput =false;
        }
    }while(!correctInput);
    do{
        correctInput = true;
        std::cout << "Input your X coordinate (0 - 39):";
        std::cin >> tmpPlayer.curX;
        if(tmpPlayer.curX < 0 || tmpPlayer.curX > 39){
            std::cout << "Bad input!. Try again!" << std::endl;
            correctInput =false;
        }
    }while(!correctInput);
    do{
        correctInput = true;
        std::cout << "Input your Y coordinate (0 - 39):";
        std::cin >> tmpPlayer.curY;
        if(tmpPlayer.curY < 0 || tmpPlayer.curY > 39){
            std::cout << "Bad input!. Try again!" << std::endl;
            correctInput =false;
        }
    }while(!correctInput);

    players.push_back(tmpPlayer);
    GenerateEnemy(players);
    DisplayPole(players);
    std::cout << "Input the command (left, right, top, bottom, save, load): ";
    std::cin >> command;
    return 0;
}

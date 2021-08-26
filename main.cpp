#include <iostream>
#include "main.h"

int main() {

    std::string fileNameToSaveGame = "../game.bin", command, errStr;
    std::vector<player> players;

    player tmpPlayer;
    bool correctInput, endGame, curError;
    std::vector<std::string> commandVector{"left", "right", "top", "bottom", "save", "load"};
    std::cout <<  "\033[2J";
    std::cout <<  "\033[H";
    do{
        correctInput = true;
        std::cout << "Input your name(max 30 characters: ";
        std::cin >> tmpPlayer.name;
        if(tmpPlayer.name.size() > 30){
            correctInput = false;
            std::cout << "Bad input. Try again!" << std::endl;
        }
    }while (!correctInput);
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
        std::cout << "Input your X coordinate (0 - " << MAX_X-1 << "):";
        std::cin >> tmpPlayer.curX;
        if(tmpPlayer.curX < 0 || tmpPlayer.curX > MAX_X-1){
            std::cout << "Bad input!. Try again!" << std::endl;
            correctInput =false;
        }
    }while(!correctInput);
    do{
        correctInput = true;
        std::cout << "Input your Y coordinate (0 - " << MAX_Y-1 << "):";
        std::cin >> tmpPlayer.curY;
        if(tmpPlayer.curY < 0 || tmpPlayer.curY > MAX_Y-1){
            std::cout << "Bad input!. Try again!" << std::endl;
            correctInput =false;
        }
    }while(!correctInput);

    players.push_back(tmpPlayer);
    GenerateEnemy(players);
    do{
        DisplayPole(players,curError,errStr);
        do{
            endGame = false;
            correctInput = true;
            std::cout << "Input the command (left, right, top, bottom, save, load): ";
            std::cin >> command;
            correctInput = CheckCommand(commandVector, command);
            if(!correctInput) std::cout << "Bad command! Try again!" << std::endl;
        } while (!correctInput);
        if(command == "save"){
            if(!SaveGame(players, fileNameToSaveGame)){
                curError = true;
                errStr = "Can't save game to file!";
            }
        }
        if(command == "load"){
            if(!LoadGame(players, fileNameToSaveGame)) {
                curError = true;
                errStr = "Can't load game to file!";
            }
        }
        ExecuteCommand(command, players,curError,errStr);
        //DisplayPole(players);
        CheckEndGame(endGame, players);
        GenerateStepsEnemy(players);
        CheckEndGame(endGame, players);
    }while(!endGame);
    DisplayPole(players,curError,errStr);
    std::cout << "Game over! ";
    if(players[0].health <= 0) std::cout << "The player won!" << std::endl;
    else
        std::cout << "The player lost!" << std::endl;
    DisplayPole(players,curError,errStr);
    return 0;
}

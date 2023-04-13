#ifndef Game_hpp
#define Game_hpp
#pragma once
#include "player.hpp"
#include <vector>


namespace ariel{

class Game{
    private:
        Player * p1;    
        Player * p2;
        vector<string> log;   // vector of all the turns
        int cardsOnTable;
        string lastTurn;
        string winner;
        int drawsRate;
        int numOfTurns;


    public:
        Game(Player& p1, Player& p2);
        void beforeGame();
        void setLog(string addLog);      //function to update to log vector
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        int getDraws();
        void setDraws();
    };
      
} 
#endif

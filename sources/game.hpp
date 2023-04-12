#ifndef Game_hpp
#define Game_hpp
#pragma once
#include "player.hpp"

namespace ariel{

class Game{
    private:
        Player p1;
        Player p2;
        vector<string> log;
        int cardsOnTable;
        string lastTurn;

    public:
        Game(Player p1, Player p2);
        void beforeGame();
        void setLog();
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
    };
      
} 
#endif

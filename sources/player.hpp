#ifndef Player_hpp
#define Player_hpp
#pragma once
#include "card.hpp"
#include <string>

using namespace std;
namespace ariel{

class Player{
    
    private:
        string name;
        vector<Card> stack;    // each player begin with 26
        int _cardsTaken;        // the amount of the cards the player won
        int winsRate;
        int drawsRate;
        
    public:
        Player(string name); // constructor declaration
        Player();
        string getName();
        int stacksize();
        int cardesTaken();
        void cardOnTop();        // the next card the player play with
        vector<Card> getStack;
        void cardWin(int c);
        int getWins();
        void setWins();
        int getDraws();
        void setDraws();



    };
        

}
#endif

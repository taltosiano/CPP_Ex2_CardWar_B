#ifndef Player_hpp
#define Player_hpp
#pragma once
#include "card.hpp"
#include <string>
#include <vector>


using namespace std;
namespace ariel{

class Player{
    
    private:
        string name;
        vector<Card> stack;    // each player begin with 26
        int _cardsTaken;        // the amount of the cards the player won
        int winsRate;
        
    public:
        Player(string name); 
        Player();             // default constructor
        string getName();
        int stacksize();
        const vector<Card>& getStack() const {
          return stack;
        }
        int cardesTaken();
        void cardOnTop();        // the next card the player play with
        void addCardToStack(Card c);
        void cardWin(int c);
        int getWins();
        void setWins();




    };
        

}
#endif

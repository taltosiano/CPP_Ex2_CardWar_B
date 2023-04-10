#include "player.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace ariel;
    
    // empty constructor
     Player::Player() {}


    Player::Player(string name){
        this->name = name;
        this->_cardesTaken = 0;
        this->winsRate = 0;
        this->drawsRate = 0;
    }

    string Player::getName(){
        return this->name;
    }

    vector Player::getStack(){
        return this->stack;
    }

    //prints the amount of cards left. should be 21 but can be less if a draw was played
    int Player::stacksize(){
        return this->stack.size();
    }

    // prints the amount of cards this player has won
    int Player::cardesTaken(){
        return this->_cardsTaken;
    }

    // The card at the top of the pack (the card that player will turn over)
    void Player::cardOnTop(){
        this->stack.pop_back();
    }

    void Player::cardWin(int c){
        this->_cardesTaken += c;
    }
    int Player::getWins(){
        this->winsRate;
    }

    void Player::setWins(){
        this->winsRate++;
    }

    int Player::getDraws(){
        this->drawsRate;
    }

    void Player::setDraws(){
        this->drawsRate++;
    }
   



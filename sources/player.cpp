#include "player.hpp"
#include <iostream>
#include <string>
#include <vector>


using namespace std;
using namespace ariel;
    
    // empty constructor
     Player::Player() {}


    Player::Player(string name){
        this->name = name;
        this->_cardsTaken = 0;
        this->winsRate = 0;
    }

    string Player::getName(){
        return this->name;
    }

    void Player::addCardToStack(Card c){
         stack.push_back(c);
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
        this->_cardsTaken += c;
    }
    int Player::getWins(){
        return this->winsRate;
    }

    void Player::setWins(){
        this->winsRate++;
    }

   
   



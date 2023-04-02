#include "player.hpp"
#include <iostream>
#include <string>

using namespace std;
namespace ariel{
    
    // empty constructor
     Player::Player() {}


    Player::Player(string name){

    }

    string Player::getName(){
        return "";
    }

    //prints the amount of cards left. should be 21 but can be less if a draw was played
    int Player::stacksize(){
        return 0;
    }

    // prints the amount of cards this player has won
    int Player::cardesTaken(){
        return 0;
    }

    // The number of cards the player has
    // int Player::numOfCards(){

    // }

    // The card at the top of the pack (the card that player will turn over)
    int Player::cardOnTop(){
        return 0;
    }

    int Player::numOfCards(){
        return 0;
    }


}

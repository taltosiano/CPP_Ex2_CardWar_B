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
        
    public:
        Player(string name); // constructor declaration
        Player();
        string getName();
        int stacksize();
        int cardesTaken();
        int numOfCards();
        int cardOnTop();

    };
        

}
#endif

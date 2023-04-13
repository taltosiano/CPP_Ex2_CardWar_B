#ifndef Card_hpp
#define Card_hpp
#pragma once
#include <string>

namespace ariel{

enum Shape{
    Diamond,
    Heart,
    Clover,
    Spade
};

class Card{

private:
    int number;
    Shape shape;
public:
    Card(int number, Shape shape);
    int getCardNum();
    std::string cardToString();
    Shape getShape();
    int trumpCard(Card _card);
};    
}
#endif

#include "card.hpp"
#include <iostream>
#include <string>

using namespace std;
namespace ariel{
Card::Card(int number, Shape shape){
    this->number = number;
    this->shape = shape;
    } 

string Card::getShape(){
    string sh="";
    if (shape == Diamond)
    {
        sh = "Diamond";
    }
     if (shape == Clover)
    {
        sh = "Clover";
    }
     if (shape == Spade)
    {
        sh = "Spade";
    }
     if (shape == Heart)
    {
        sh = "Heart";
    }
    return sh;
 }   

string Card::cardToString(){
    string cardType;
     switch (this->number)
    {
    case 11:
        cardType = "Jack";
        break;
    case 12:
        cardType = "Queen";
        break;
    case 13:
        cardType = "King";
        break;
    case 1:
        cardType = "Ace";
        break;
 
    default:
        cardType = to_string(this->getCardNum);
        break;
    } 
    return cardType + "of" + this->getShape;
    
} 

int Card::trumpCard(Card _card){
   if (this->getCardNum == 1 && _card.getCardNum != 1 && _card.getCardNum != 2)
   {
       return 1;
   }
    if (_card.getCardNum == 1 && this->getCardNum != 1 && this->getCardNum != 2)
   {
       return -1;
   }
    if (this->getCardNum > _card.getCardNum)
    {
        return 1;
    }
    if (this->getCardNum > _card.getCardNum)
    {
        return -1;
    }
    else{
        return 0;        // it's a draw.
    } 
    
}


int Card::getCardNum(){
    return this->number;
    
} 

}

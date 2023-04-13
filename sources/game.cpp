#include "game.hpp"
#include "card.hpp"
#include "player.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>



using namespace std;
namespace ariel{

Game::Game(Player& p1, Player& p2){
    this->p1 = &p1;
    this->p2 = &p2;
    this->cardsOnTable = 0;
    this->lastTurn = "";
    this->beforeGame();
    this->winner = "";
    this->drawsRate = 0;
    this->numOfTurns = 0;

}

void Game::beforeGame(){
    vector<Card> deck;
    for (int num = 1; num <= 13; num++) {
        deck.push_back(Card(num, Shape::Spade));     //each number with each shape.
        deck.push_back(Card(num, Shape::Heart)); 
        deck.push_back(Card(num, Shape::Diamond)); 
        deck.push_back(Card(num, Shape::Clover)); 
     }

     // shuffle the deck
    random_device rd;                     
    mt19937 g(rd());                      //In writing this command I was helped by google
    shuffle(deck.begin(), deck.end(), g);


    // divide the deck for 2
      for(int i = 0; i < 26; i++)
        {
        p1->addCardToStack(deck.back());   // take the last card from the deck
        deck.pop_back();
        p2->addCardToStack(deck.back());   // take the last card from the deck
        deck.pop_back();

        } 
  
}

void Game::playTurn(){
    if (this->p1 == this->p2)
            throw std::exception();
    
    if (p1->stacksize() == 0 && p2->stacksize() == 0)
    {
               //checking which player won and updating the winner and the turns stack
        if(this->p1->cardesTaken() > this->p2->cardesTaken())
            {
             this->winner = this->p1->getName();
             this->setLog(lastTurn);
             throw std::exception();
            }
        else {
            if(this->p1->cardesTaken() < this->p2->cardesTaken())
             {
               this->winner = this->p2->getName();  
               this->setLog(lastTurn);
               throw std::exception();
              }
            else
             {
                    //if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
                 this->winner = "draw";
                 this->setLog(lastTurn);
                 throw std::exception();
             }          
        }
    }
    Card cp1 = p1->getStack().back();    // This function can be used to fetch the last element of a vector container. (geeksforgeeks)
    p1->cardOnTop();                     // player1 play with the top card
    Card cp2 = p2->getStack().back();
    p2->cardOnTop();                     // then player2 play with his top card
    this->setDraws();
    this->cardsOnTable += 2;
    if(cp1.trumpCard(cp2) == 1){
        p1->cardWin(this->cardsOnTable);
        p1->setWins();
        this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName()
                                     + "play with" + cp2.cardToString() + "." + this->p1->getName() + "won. ";
        this->winner = p1->getName(); 
        numOfTurns++;
    }
    if (cp1.trumpCard(cp2) == -1)
    {
        p2->cardWin(this->cardsOnTable);
        p2->setWins();
        this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName()
                                     + "play with" + cp2.cardToString() + "." + this->p2->getName() + "won. ";
        this->winner = p2->getName();                               
        p2->setWins();
        numOfTurns++;
    }
    else{                 // tie situation
         this->cardsOnTable+=2;
         numOfTurns++;
         while(!(p1->stacksize() == 0 && p2->stacksize() == 0)){
            this->p1->cardOnTop();             // down face cards
            this->p2->cardOnTop();
            this->setDraws();   
            this->cardsOnTable+=2;

            if (p1->stacksize() == 0 && p2->stacksize() == 0)
            {
                this->p1->cardWin(this->cardsOnTable\2); 
                this->p2->cardWin(this->cardsOnTable\2);   
				if(this->p1->cardesTaken() > this->p2->cardesTaken())
                {
					this->winner = this->p1->getName();
					this->setLog(lastTurn);
					break;
                }
				else {
					if(this->p1->cardesTaken() < this->p2->cardesTaken())
					{
						this->winner = this->p2->getName();  
						this->setLog(lastTurn);
						break;
					}
					else
					{
							//if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
						this->winner = "draw";
						this->setLog(lastTurn);
						break;
					}          
				}
		   }
           
            this->p1->cardOnTop();         //up face cards
            this->p2->cardOnTop();
            this->setDraws(); 
            this->cardsOnTable+=2;
            this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName() 
                          + "play with" + cp2.cardToString() + ". so that the game over in tie.";
            if(cp1.trumpCard(cp2) == 1){
                p1->cardWin(this->cardsOnTable);
                p1->setWins();
                this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName()
                                            + "play with" + cp2.cardToString() + "." + this->p1->getName() + "won. ";
                this->winner = p1->getName(); 
                break;
            }
            if (cp1.trumpCard(cp2) == -1)
            {
                p2->cardWin(this->cardsOnTable);
                p2->setWins();
                this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName()
                                            + "play with" + cp2.cardToString() + "." + this->p2->getName() + "won. ";
                this->winner = p2->getName();                               
                p2->setWins();
                break;
            }
        }
           if (p1->stacksize() == 0 && p2->stacksize() == 0)
            {
                this->p1->cardWin(this->cardsOnTable\2); 
                this->p2->cardWin(this->cardsOnTable\2); 
      
				if(this->p1->cardesTaken() > this->p2->cardesTaken())
                {
					this->winner = this->p1->getName();
					this->setLog(lastTurn);
                }
				else {
					if(this->p1->cardesTaken() < this->p2->cardesTaken())
					{
						this->winner = this->p2->getName();  
						this->setLog(lastTurn);
					}
					else
					{
							//if it's a tie will let the wu=inner be tie and we'll throw exception in the function printWiner
						this->winner = "draw";
						this->setLog(lastTurn);
					}          
				}
		   }
    }
                   
      this->cardsOnTable = 0; 
      this->setLog(lastTurn);
} 


// print the last turn stats. 
void Game::printLastTurn(){
    if(p1->stacksize() == 26){
        cout << "no turns played yet" << endl;
        throw std::exception();
    }
    cout << this->lastTurn << endl;

}

//playes the game untill the end
void Game::playAll(){
    while (this->p1->stacksize() > 0 )
    {
        this->playTurn();
    }
    cout << "Game is Done" << endl;
    
}

// prints the name of the winning player
void Game::printWiner(){
    if(this->winner == "draw")
    {
        cout << "there is no winner. its draw." << endl;
    }
   
    else{
        cout << this->winner << endl;
    }
}

void Game::setLog(string addLog){
    this->log.push_back(addLog);
}

// prints all the turns played one line per turn (same format as game.printLastTurn())
void Game::printLog(){
    if(p1->stacksize() == 26){
        cout << "no turns played yet" << endl;
        throw std::exception();
    }
    for(vector<string>::size_type i = 0; i<log.size(); i++){
       cout << this->log[i] << endl;
 }
}

// for each player prints basic statistics: win rate, cards won, <other stats you want to print>.
// Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
void Game::printStats(){
    //p1 stats
    string p1Wons = to_string(double(p1->getWins()*100)/this->numOfTurns);
    cout << "player number 1 Stats:" << endl;
    cout << p1->getName() + " wins: " + p1Wons + ", number of cards he won: " + to_string(p1->cardesTaken()) + ".";
   //p2 stats
    string p2Wons = to_string(double(p1->getWins()*100)/this->numOfTurns);
    cout << "player number 2 Stats:" << endl;
    cout << p2->getName() + "wins: " + p2Wons + ", number of cards he won: " + to_string(p2->cardesTaken()) + ".";
    string dra = to_string(double(this->getDraws()*100)/this->numOfTurns);
    cout <<  "the number of draws in this game: " + dra << endl;      
}

    int Game::getDraws(){
        return this->drawsRate;
    }

    void Game::setDraws(){
        this->drawsRate++;
    }

}

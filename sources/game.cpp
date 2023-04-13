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

//initialize a new game
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

//In this function, a pot is created and divided between the players equally
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

// activate of new turn
void Game::playTurn(){
    if (this->p1 == this->p2)
            throw std::exception();

    // Under this condition we understand that the game is over and we will check who is the winner
    if (p1->stacksize() == 0 && p2->stacksize() == 0)         
    {
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
                    //tie situation
                 this->winner = "tie";
                 this->setLog(lastTurn);
                 throw std::exception();
             }          
        }
    }
    Card cp1 = p1->getStack().back();    // This function can be used to fetch the last element of a vector container. (geeksforgeeks)
    p1->cardOnTop();                     // draw card from player 1
    Card cp2 = p2->getStack().back();
    p2->cardOnTop();                     // draw card from player 2
    this->cardsOnTable += 2;             // 2 cards on table

    //now we use the function of compare(who's won) from Player class
    if(cp1.trumpCard(cp2) == 1){         // means player 1 won
        p1->cardWin(this->cardsOnTable);
        p1->setWins();
        this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName()
                                     + "play with" + cp2.cardToString() + "." + this->p1->getName() + "won. ";
        this->winner = p1->getName(); 
        numOfTurns++;
        this->cardsOnTable = 0;           // The winner took the cards from the table
        this->setLog(lastTurn);           //We will add the turn summary to the vector
        return;
    }
    if (cp1.trumpCard(cp2) == -1)      //means player 2 won
    {
        p2->cardWin(this->cardsOnTable);
        p2->setWins();
        this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName()
                                     + "play with" + cp2.cardToString() + "." + this->p2->getName() + "won. ";
        this->winner = p2->getName();                               
        p2->setWins();
        numOfTurns++;
        this->cardsOnTable = 0; 
        this->setLog(lastTurn);
    }
    else{                 // tie situation
         numOfTurns++;
         while(!(p1->stacksize() == 0 && p2->stacksize() == 0)){     //Checking that there are cards left for the players 
            this->p1->cardOnTop();             // down face cards
            this->p2->cardOnTop();
            this->setDraws();   
            this->cardsOnTable+=2;
            
            if (p1->stacksize() == 0 && p2->stacksize() == 0)
            {
				break;
		    }
           
            this->p1->cardOnTop();         //up face cards
            this->p2->cardOnTop();
           // this->setDraws(); 
            this->cardsOnTable+=2;
            this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName() 
                          + "play with" + cp2.cardToString() + ". so that the game over in tie.";
            if(cp1.trumpCard(cp2) == 1){
                p1->cardWin(this->cardsOnTable);
                p1->setWins();
                this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName()
                                            + "play with" + cp2.cardToString() + "." + this->p1->getName() + "won. ";
                this->winner = p1->getName(); 
                cardsOnTable=0;
                this->setLog(lastTurn);
                return;
            }
            if (cp1.trumpCard(cp2) == -1)
            {
                p2->cardWin(this->cardsOnTable);
                p2->setWins();
                this->lastTurn =this->p1->getName() + "play with " + cp1.cardToString() + "and " + this->p2->getName()
                                            + "play with" + cp2.cardToString() + "." + this->p2->getName() + "won. ";
                this->winner = p2->getName();                               
                p2->setWins();
                cardsOnTable=0;
                this->setLog(lastTurn);
                return;
            }
        }
            //If we ended in a tie and ran out of cards, we will divide it among the players
           if (p1->stacksize() == 0 && p2->stacksize() == 0)     
            {
                this->p1->cardWin((this->cardsOnTable)/2); 
                this->p2->cardWin((this->cardsOnTable)/2);   //Each player gets half of the cards thrown
                
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
						this->winner = "tie";
						this->setLog(lastTurn);
					}          
				}
		   }
    }                
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
    if(this->winner == "tie") 
    {
        cout << "there is no winner. its tie." << endl;
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
    cout <<  " the draw rate is: " + dra + "and the number of draws in this game: " + to_string(double(this->getDraws()))<< endl;  
}

    int Game::getDraws(){
        return this->drawsRate;
    }

    void Game::setDraws(){
        this->drawsRate++;
    }
}

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

Game::Game(Player p1, Player p2){
    
    this->cardsOnTable = 0;
    this->lastTurn = "";
    this->winRate = 0;
    this->beforeGame();
}

void Game::beforeGame(){
    vector<Card> deck(52);
    for (int num = 1; num <= 13; num++) {
        deck.push_back(Card(num, Spade));     //each number with each shape.
        deck.push_back(Card(num, Heart)); 
        deck.push_back(Card(num, Diamond)); 
        deck.push_back(Card(num, Clover)); 
     }

      // Shuffle the deck randomly
    srand(time(NULL));  // initialize random seed
    for (int i = 0; i < deck.size(); i++) {
        int tmp = i + rand() % (n - i);
        swap(deck[tmp], deck[j]);
    }

     // shuffle the deck
    random_device rd;                     
    mt19937 g(rd());                      //In writing this command I was helped by google
    shuffle(deck.begin(), deck.end(), g);


    // divide the deck for 2
      for(int i = 0; i < 52; i++)
        {
        p1.stack.push_back(deck.back());  // take the last card from the deck
        deck.pop_back();
        p2.stack.push_back(deck.back());  // take the last card from the deck
        deck.pop_back();

            int play1 = rand() % deck.size() + 1;
            this->p1.stack(deck.at(play1));
            tempPack.erase(deck.begin() + play1);
            int play2 = rand() % deck.size() + 1;
            this->p2.stack(deck.at(play2));
            tempPack.erase(deck.begin() + play2);
        } 
  
}

void Game::playTurn(){
    if (&p1 == &p2)
    {
        throw invalid_argument("the both players are chosen there are the same one");
    }
    if (p1.stacksize() == 0 || p2.stacksize() == 0)
    {
        throw invalid_argument("The Game Is Done");
    }
    Card cp1 = p1.getStack().back();    // This function can be used to fetch the last element of a vector container. (geeksforgeeks)
    p1.cardOnTop();                     // player1 play with the top card
    Card cp2 = p2.getStack().back();
    p2.cardOnTop();                     // then player2 play with his top card
    this->cardsOnTable += 2;
    if(cp1.trumpCard(cp2) == 1){
        p1.cardWin(this->cardsOnTable);
    }
    if (cp1.trumpCard(cp2) == -1)
    {
        p2.cardWin(this->cardsOnTable);
    }
    else{                 // Draw situation
        this->p1.cardOnTop();
        this->p2.cardOnTop();
        this->cardsOnTable += 2;
        this->playTurn();
     }  
     this->lastTurn = this->printWiner() + "won." this->p1.getName() + "play with " + cp1.cardToString() + "and "
                      + this->p2.getName() + "play with" + cp2.cardToString();
     this->cardsOnTable = 0; 
     this->setLog(lastTurn);
    }
    

// print the last turn stats. 
void Game::printLastTurn(){
    if(p1.stacksize() == 26){
        cout << "no turns played yet" << endl;
    }
    cout << this->lastTurn << endl;

}

//playes the game untill the end
void Game::playAll(){
    while (this->p1.stacksize() > 0 )
    {
        this->playTurn();
    }
    cout << "Game is Done" << endl;
    
}

// prints the name of the winning player
void Game::printWiner(){
  if (this->p1.cardWin() > this->p2.cardWin())
  {
    cout << "The Winer is: " + this->p1.getName() + "!!!" << endl;
  }
  else if
  {
    cout << "The Winer is: " + this->p2.getName() + "!!!" << endl;
  }
  else
  {
    throw invalid_argument("The game done with Draw")
  }
  
}

void Game::setLog(string addLog){
    this->log.push_back(addLog);
}

// prints all the turns played one line per turn (same format as game.printLastTurn())
void Game::printLog(){
    for(int i = 0; i<log.size(); i++){
    cout << this->log[i] << endl;
 }
}

// for each player prints basic statistics: win rate, cards won, <other stats you want to print>.
// Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
void Game::printStats(){
    cout << p1.getName() + "wins: " + p1.getWins() + ", number of cards he won: " + p1.cardWin(); + "." +
            p2.getName() + "wins: " + p2.getWins() + ", number of cards he won: " + p2.cardWin(); + "." +
            "the number of draws in this game: " + p1.getDraws();
}

}

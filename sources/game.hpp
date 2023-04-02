#include "player.hpp"

namespace ariel{

class Game{
    private:
        Player p1;
        Player p2;

    public:
        Game(Player p1, Player p2);
        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();
        void printWinner();
    };
    
    game::game(/* args */)
    {
    }
    
    game::~game()
    {
    }
    
    
} // namespace ariel

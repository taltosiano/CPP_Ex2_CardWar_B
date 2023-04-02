 #include "card.hpp"

namespace ariel{
using namespace std;

class Player{
 
    private:
        std::string name;
        int numOfCards numCards;
        std::string topCard;

    public:
        Player(std::string name); // constructor declaration

        std::string getName();
        void stacksize();
        void cardesTaken();
        int numOfCards();
        std::string cardOnTop();

    };
    

}
 
#ifndef DECK_H
#define DECK_H

#include <vector>
using namespace std;
struct Card{
   int number;
   int suit;

   Card(){};

   Card(int innumber, int insuit){
       number = innumber;
       suit = insuit;
   }
};

struct Player{
   Card *hand[5];
   int number;
   string name;
   bool ai=true;
   bool hasAce=false;
   int sum;
   bool busted=false;
   int sumHand();
   int lastSummed;
   Player(){};
   Player(string inname, int innumber){
       number = innumber;
       name = inname;
   }
};

class Deck{
public:
   Deck(int Players);
   ~Deck();
   void shuffleDeck();
   void DealCards(int Players);
   bool hit(int player, int numPlayers);
   void peek(int numPlayers);
   void declare(int numPlayers);
   void printCard(int number, int suit);
   int win(int player);
   Player players[6];
   bool getWon();
   void setWon(bool winnerino);

private:
   vector<Card*> decklist;
   int topCard;
   bool won=false;
};

#endif // DECK_H

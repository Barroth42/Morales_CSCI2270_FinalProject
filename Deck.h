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
   int sum;
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
   bool hit(int player);
   void peek();
   void declare();
   void dealer();
   int win(int player);
   Player players[5];

private:
   vector<Card*> decklist;
   int topCard;
};

#endif // DECK_H

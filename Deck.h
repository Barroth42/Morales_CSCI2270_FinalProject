#ifndef DECK_H
#define DECK_H

struct Card{
    std::string number;
    int suit;

    Card(){};

    Card(std::string innumber, int insuit){
        number = innumber;
        suit = insuit;
    }
};

struct Player{
    Card hand[5];
    int number;
    std::string name;

    Player(){};
    Player(std::string inname, int innumber){
        number = innumber;
        name = inname;
    }
};

class Deck{
public:
    Deck();
    ~Deck();
    void shuffleDeck();
    void DealCards(int players);
    void hit(int player);
    int win(int player);

private:
    Card decklist[52];
};

#endif // DECK_H

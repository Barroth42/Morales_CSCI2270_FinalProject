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

class Deck{
public:
    Deck();
    ~Deck();
    void shuffleDeck();

private:
    Card decklist[52];
};

#endif // DECK_H

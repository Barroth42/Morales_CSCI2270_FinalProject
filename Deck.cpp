//Deck.cpp
//Contributors: Ben Roberts, Cory Morales, Bryce Griebenow

#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

//#include <stdlib.h>
//#include "Deck.h"
using namespace std;


void Deck::Deck()
{
	for(int i=0;i<4;i++)
	{
		for(int j=1;j<14;j++)
		{
			deckVector[13*i+j-1].number = j;
			deckVector[13*i+j-1].suit = i;
			deckVector[13*i+j-1].shuffled = false;
		}
	}
}

void Deck::shuffleDeck()
{
	//Probably horribly inefficient method:
	/*vector<Card> shuffledDeck;
	for(int i=0;i<52;i++)
	{
		int cardIndex = rand()%52;
		while(unshuffledDeck[cardIndex].shuffled = true)
		{
			cardIndex = rand()%52;
		}
		shuffledDeck[i]=unshuffledDeck[cardIndex];
	}*/
	
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();//found this method at http://www.cplusplus.com/reference/algorithm/shuffle/
	shuffle(deckVector.front(),deckVector.back(),std::default_random_engine(seed));
	//Potential problem: May need to make it an array instead of a vector, but will need to test it before knowing.
	
}


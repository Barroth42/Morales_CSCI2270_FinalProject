//Deck.cpp
//Contributors: Ben Roberts, Cory Morales, Bryce Griebenow

#include <iostream>
#include <algorithm>
//#include <vector>
#include <array>
#include <random>
#include <chrono>
#include "Deck.h"


using namespace std;

int Player::sumHand()
{
	//sum = 0;
	for(int i=lastSummed+1; i<5;i++)
	{
		if(hand[i] != NULL)
		{
			if(hand[i]->number > 1 && hand[i]->number <11)
			{
				sum += hand[i]->number;
			}
			else if(hand[i]->number == 1)
			{
				if(sum > 10)
				{
					sum += 1;
				}
				else if(sum == 10)
				{
					sum = 21;
					return sum;
				}
				else
				{
					if(ai)
					{
					    if(sum + 11 <= 21){
                            sum += 11;//There will be bugs with this. If they bust, the ace should change to mean 1.
					    }
					    else{
                            sum++;
					    }
					}
					else
					{
						string input;
						ace:
						cout << "Would you like your ace to count as 1 or 11?\n";
						cout << "1. One\n2. Eleven" << endl;
						cin >> input
						if(input == "1")
						{
							sum += 1;
						}
						else if(input == "2")
						{
							sum += 11;
						}
						else
						{
							cout << "Not a valid input" << endl;
							goto ace;
						}
					}
				}
			}
			else if(hand[i]->number >10)
			{
				sum += 10;
			}

			lastSummed = i;
		}
	}
	return sum;
}

Deck::Deck(int numPlayersInput)
{
	numPlayers = numPlayersInput;
	players[numPlayers];
	topCard =0;
	for(int i=0;i<4;i++)
	{
		for(int j=1;j<14;j++)
		{
			decklist[13*i+j-1].number = j;
			decklist[13*i+j-1].suit = i;
			decklist[13*i+j-1].shuffled = false;
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
	shuffle(decklist.begin(),decklist.end(),std::default_random_engine(seed));
	//Potential problem: May need to make it an array instead of a vector, but will need to test it before knowing.
}

void Deck::DealCards()
{
	for(int i=0; i<numPlayers;i++)
	{
		if(topCard == 52)
		{
			cout << "Unable to deal. Ran out of cards."
		}
		else
		{
			players[i].hand[0] = decklist[topCard];
			topCard++;
			players[i].hand[1] = decklist[topCard];
			topCard++;
			for (int j=2; j<5;j++)
			{
				players[i].hand[j] = NULL;
			}

		}
	}
}

void PrintHand(Player p)
{
	int loc = 0;
	while(loc < 5 && p->hand[loc] != NULL){
        if(p->hand[loc]->number <=10 && p->hand[loc]->number >0){
            cout<<p->hand[loc]->number;
        }
        else if(p->hand[loc]->number == 11){
            cout<<"J";
        }
        else if(p->hand[loc]->number == 12){
            cout<<"Q";
        }
        else if(p->hand[loc]->number == 13){
            cout<<"K";
        }
        else{
            cout<<"somethingiswrongwiththecardnumber";
        }
        if(p->hand[loc]->suit == 0){
            cout<<"♠   ";
        }
        else if(p->hand[loc]->suit == 1){
            cout<<"♣   ";
        }
        else if(p->hand[loc]->suit == 2){
            cout<<"♥   ";
        }
        else if(p->hand[loc]->suit == 3){
            cout<<"♦   ";
        }
        else{
            cout<<"something is wrong with the card suit   ";
        }
	}
	cout<<"\n"<<endl;
}
bool Deck::hit(Player p)
{
	int i = 2;
	while(p.hand[i]!= NULL)
	{
		i++;
	}
	p.hand[i] = decklist[topCard];
	topCard++;
	if(p.sumHand() < 21)
	{
		return true;
	}
	else if(p.sumHand() == 21)
	{
		//win(p);
		return false;
	}
	else
	{
		//bust(p);
		return false;
	}
}




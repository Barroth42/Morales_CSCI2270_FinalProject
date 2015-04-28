//Deck.cpp
//Contributors: Ben Roberts, Cory Morales, Bryce Griebenow

#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <random>
#include <cstdlib>
#include <ctime>
//#include <chrono>
#include "Deck.h"


using namespace std;

int Player::sumHand()
{
	sum = 0;
	hasAce=false;
	for(int i=0; i<5;i++)
	{
		if(hand[i] != NULL)
		{
			if(hand[i]->number > 1 && hand[i]->number <11)
			{
				sum += hand[i]->number;
			}
			else if(hand[i]->number == 1 && !hasAce)
			{
				if(sum > 10)
				{
					sum += 1;
				}
				else if(sum == 10)
				{
                    hasAce=true;
					sum = 21;
				}
				else
				{
                    hasAce=true;
                    sum += 11;
				}
			}
			else if(hand[i]->number == 1 && hasAce)
			{
			    sum+=1;
			}
			else if(hand[i]->number >10)
			{
				sum += 10;
			}
		}
	}
	if(sum>21&&hasAce)
        sum-=10;
	return sum;
}

Deck::Deck(int numPlayers)
{
	//players[numPlayers];
	for(int i=0;i<numPlayers+1;i++)
	{
		players[i].sum =0;
		for(int j=0; j<5; j++)
		{
			players[i].hand[j] = NULL;
		}
	}
	topCard =0;
	for(int i=0;i<4;i++)
	{
		for(int j=1;j<14;j++)
		{
			Card *c = new Card;
			c->number = j;
			c->suit = i;
			//decklist[13*i+j-1].number = j;
			//decklist[13*i+j-1].suit = i;
			decklist.push_back(c);
			//decklist[13*i+j-1].shuffled = false;
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

	/*
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();//found this method at http://www.cplusplus.com/reference/algorithm/shuffle/
	shuffle(decklist.begin(),decklist.end(),std::default_random_engine(seed));
	*///Something is wrong with this method, so I'll try another one that uses vectors instead of arrays.

    //shuffles the deck
	srand(unsigned(time(0)));
	random_shuffle(decklist.begin(), decklist.end());
}

void Deck::DealCards(int numPlayers)
{
    //creates each player's hand
	for(int i=0; i<numPlayers+1;i++)
	{
		if(topCard == 52)
		{
			cout << "Unable to deal. Ran out of cards.";
		}
		else
		{
			players[i].hand[0] = decklist[topCard];
			topCard++;
			players[i].hand[1] = decklist[topCard];
			topCard++;
			players[i].sum=players[i].sumHand();
			for (int j=2; j<5;j++)
			{
				players[i].hand[j] = NULL;
			}

		}
	}
}

/*void PrintHand(Player p)
{

}*/
bool Deck::hit(int playerInt, int numPlayers)
{
    //allows for the addition of more cards to one's hand and checks the sum to make sure no one busts
	Player *p = new Player;
	p = &players[playerInt];
	int i = 2;
	while(p->hand[i]!= NULL)
	{
		i++;
	}
	p->hand[i] = decklist[topCard];
	topCard++;
	if(p->sumHand() < 21)
	{
		return true;
	}
	else if(p->sumHand() == 21)
	{
		//win(p);
	    won=true;
	    if(playerInt==numPlayers)
            cout<<"Dealer drew a ";
		else
            cout<<"Player "<<playerInt+1<<" drew a ";
		printCard(p->hand[i]->number,p->hand[i]->suit);
	    cout<<" and won!"<<endl;
		return false;
	}
	else
	{
	    if(playerInt==numPlayers)
            cout<<"Dealer drew a ";
		else
            cout<<"Player "<<playerInt+1<<" drew a ";
	    printCard(p->hand[i]->number,p->hand[i]->suit);
	    cout<<" and busted"<<endl;
	    p->busted=true;
		//bust(p);
		return false;
	}
}
void Deck::printCard(int number, int suit)
{
    //prints out equivalent number
	switch(number){
		case 1:
			cout << "Ace ";
			break;
		case 11:
			cout << "Jack ";
			break;
		case 12:
			cout << "Queen ";
			break;
		case 13:
			cout << "King ";
			break;
		default:
			cout << number<<" ";
			break;
	}
	cout << "of ";

    //prints out suit
	switch(suit){
		case 0:
			cout << "Hearts";
			break;
		case 1:
			cout << "Diamonds";
			break;
		case 2:
			cout << "Clubs";
			break;
		case 3:
			cout << "Spades";
			break;
	}
}
void Deck::peek(int numPlayers){
    //allows one to look around the table
    for(int i=0;i<numPlayers+1;i++)
	{
		int j=0;
		if(i==numPlayers)
            cout<<"Dealer : ";
        else
            cout << "Player " << i+1 << ": ";
		if(players[i].busted){
            cout<<"Busted with ";
        }
		while(players[i].hand[j] != NULL)
		{

			if(j==0)
			{
				cout << "[Hidden], ";
			}
			else
			{
				printCard(players[i].hand[j]->number,players[i].hand[j]->suit);
				if(players[i].hand[j+1] != NULL)
					cout << ", ";
				else
				{

					cout << endl;
					//break;
				}
			}

			j++;
		}
	}
}
void Deck::declare(int numPlayers){
    //operation to check who wins
	int max = 0;
	int winner = -1;
	for(int i=0;i<numPlayers;i++)
	{
		if(players[i].sum > max && players[i].sum <= 21)//players[i].bust ==false)
		{
			max = players[i].sum;
			winner = i;
		}
	}
	if(winner == -1)
	{
		cout << "No one wins!" << endl;
	}
	else
	{
	    if(winner==numPlayers)
            cout<<"Dealer wins with a sum of "<<players[winner].sum<<endl;
		else
            cout << "Player " << winner+1 << " wins with a sum of " << players[winner].sum << endl;
	}
}
void Deck::setWon(bool winnerino){
    won=winnerino;
}
bool Deck::getWon(){
    return won;
}
Deck::~Deck(){}

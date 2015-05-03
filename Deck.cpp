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

Deck::~Deck(){
    decklist.clear();
}

/* Prototype: Deck::Deck(int);
 *
 * Description:
 * This is the constructor for the Deck class.
 * It initializes all players' hands to NULL, including
 * the dealer's. It also initializes the deck itself to
 * contain all 52 cards.
 *
 * Example:takes the number of players(not including dealer)
 * 			as a parameter.
 * Deck d;
 * d.Deck(numPlayers);
 *
 * Precondition:
 * Must have a deck object defined, and know the number of players.
 *
 * Postcondition:
 * Players vector filled with the number of players plus the dealer.
 * All hands are NULL
 * decklist is in unshuffled order with all 52 cards.
 */
Deck::Deck(int numPlayers)
{
	for(int i=0;i<numPlayers+1;i++)
	{
		players[i].sum =0;
		for(int j=0; j<5; j++)
		{
			players[i].hand[j] = NULL;
		}
	}
	topCard =0;//drawing cards doesn't delete cards from the decklist
				//it just moves where to look for the top card.
	for(int i=0;i<4;i++)
	{
		for(int j=1;j<14;j++)
		{
			Card *c = new Card;
			c->number = j;
			c->suit = i;
			decklist.push_back(c);
		}
	}
}

/* Prototype: void Deck::shuffleDeck();
 *
 * Description:
 * This method uses a built in C++ function to shuffle the
 * order of the cards in the decklist.
 * (Template found at: http://www.cplusplus.com/reference/algorithm/random_shuffle/)
 *
 * Example:
 * d.shuffleDeck();
 *
 * Precondition:
 * File needs to #include algorithm, vector, ctime, and cstdlib
 * Needs decklist to be filled with cards.
 *
 * Postcondition:
 * The order of cards in decklist is randomized.
 */
void Deck::shuffleDeck()
{
	srand(unsigned(time(0)));
	random_shuffle(decklist.begin(), decklist.end());
}

/* Prototype: void Deck::DealCards(int);
 *
 * Description:
 * This function deals the first two cards to all players
 * including the dealer, by copying the card that is at the
 * index topCard in decklist to the player's hand array,
 * and incrementing topCard.
 *
 * Example: parameter is the number of players, not including dealer.
 * Deck d;
 * int numPlayers = 1;
 * d.DealCards(numPlayers);
 *
 * Preconditions:
 * The array players must be initialized.
 * decklist must be shuffled.
 * numPlayers should be between 1 and 5.
 *
 * Postconditions:
 * Each player's hand array at index 0 and 1 will
 * now have a card rather than being NULL.
 * Each player's sum variable is updated.
 */
void Deck::DealCards(int numPlayers)
{
	for(int i=0; i<numPlayers+1;i++)
	{
		if(topCard == 52)//should never happen.
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

/* Prototype: bool Deck::hit(int, int);
 *
 * Description: Takes the card stored at the topCard index
 * of the decklist, and adds it to the next open slot in the
 * player's hand, and then increments topCard. It returns
 * a boolean to either end or continue the turn. If the player
 * busts or draws to total 21, it returns false to end the turn,
 * otherwise, it returns true.
 *
 * Example: The parameters are:first, the index of the player
 * 			in the vector of players.
 * 			Second, the number of players not including the dealer.
 * Deck d;
 * int numPlayers = 3;
 * int playerIndex = 0;
 * d.hit(playerIndex, numPlayers);
 *
 * Precondition:
 * -The player index passed is less than or equal
 * to the numPlayers.
 * -There is at least one NULL space in the player's hand
 * to be filled.
 *
 * Postcondition:
 * The first NULL space in the player's hand has been
 * replaced by a card.
 * Sums all cards in the player's hand and returns according
 * to whether the turn is over. If the turn is over
 * it prints what the player drew and if they busted or won.
 */
bool Deck::hit(int playerInt, int numPlayers)
{
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

/* Prototype: void Player::sumHand();
 *
 * Description:
 * This function adds up all of the cards in the player's
 * hand and returns the sum. It takes into account whether
 * or not they have an ace, so if they bust,
 * the ace will switch from meaning 11 to only 1.
 *
 * Example:This is a function under the player struct,
 * 			so it will be called by p. or p->
 * 			It takes no parameters.
 *
 * Player *p= &players[0];
 * if(p->sumHand() == 21)
 * ...
 *
 * Precondition:
 * -The player's hand should have cards in it
 * prior to calling this function. (meaning not
 * all slots in their hand array are NULL)
 * -The player must be a defined player in the vector "players"
 * -The numbers stored in the cards must be between 1 and 13.
 *
 * Postcondition:
 * The sum of the cards in the hand is returned.
 * The boolean hasAce is updated to true in the player
 * struct if the player has one or more ace.
 */
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
			else if(hand[i]->number == 1 && !hasAce)//if this is the first ace
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
			else if(hand[i]->number == 1 && hasAce)//if they have more than one ace.
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

/* Prototype: void Deck::printCard(int, int);
 *
 * Description: This function takes the numbers associated with
 * a card's value and suit and will print the value of the card
 * either in a number between 2 and 10, or with a string, and
 * prints the suit as a string rather than the number that is
 * stored in the card struct.
 * (For example: a card with number=13 and suit=0 will
 * be printed as King of Hearts.)
 *
 * Example: parameters are the number, then the suit associated with a card.
 * Deck d;
 * int num=1;
 * int suit=2;
 * d.printCard(num, suit);
 *
 * Preconditions: This function should be called based on
 * cards that are in a players hand array, not really with
 * directly defined ints as above in the example.
 *
 * Postconditions:Prints to the terminal the value and suit of a card.
 */
void Deck::printCard(int number, int suit)
{
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

/* Prototype: void Deck::peek(int);
 *
 * Description:
 * This function displays the cards in all players' hands,
 * except for the first card. It also displays if a player busted.
 *
 * Example: parameter is the number of players not including the dealer.
 * Deck d;
 * int numPlayers = 3;
 * d.peek(numPlayers);
 *
 * Preconditions:
 * Players' hands must have cards in them.
 *
 * Postconditions:
 * Prints player name and hand for all players including dealer.
 * The first card in the hand is hidden.
 */
void Deck::peek(int numPlayers){
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
				}
			}
			j++;
		}
	}
}

/* Prototype: void Deck::declare(int);
 *
 * Description:
 * This function declares the winner of the game
 * by comparing each player's sum with the maximum so far.
 * The player with the largest sum that did not bust is
 * the winner.
 *
 * Example: parameter is the number of players not including dealer.
 * Deck d;
 * int numPlayers = 3;
 * d.declare(numPlayers);
 *
 * Preconditions: Each player's hand needs to be summed beforehand.
 *
 * Postconditions: Prints who the winner is and their sum.
 */
void Deck::declare(int numPlayers){
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



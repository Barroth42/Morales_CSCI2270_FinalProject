#include <iostream>
#include <string>
#include "Deck.h"
#include <stdlib.h>
using namespace std;
int main(){
    string players, operation, ai, play, holder;
    int Players, Spot, AI, op, hoomans;
    bool won=false;
    start:
    playahs://identifier to go back to if the input for the next line is unacceptable
    cout<<"How many players will there be? (5 max)"<<endl;
    getline(cin,players);
    Players=stoi(players);
    if(Players<0||Players>5){//checks to see if the amount of players is acceptable
        cout<<"Not a valid number."<<endl;
        goto playahs;
    }
    ai_players://identifier to go back to if the input for the next line is unacceptable
    cout<<"How many players will be AI? (0-"<<Players<<")"<<endl;
    getline(cin,ai);
    AI=stoi(ai);
    if(AI<0||AI>Players){//checks to see if the amount of AI is acceptable
        cout<<"Not a valid number."<<endl;
        goto ai_players;
    }
    Deck d(Players);//constructs the deck to have the correct amount of players
    won=false;
    if(AI!=0){
        hoomans=Players-AI;//how many actual humans are playing
        for(int i=0;i<hoomans;i++){
            Spot=rand()%Players-1;//will randomize spot as if at an actual blackjack table
            d.players[Spot].ai=false;
        }
    }
    else{//if no AI, then make all spots human
        for(int i=0;i<Players;i++){
            d.players[i].ai=false;
        }
    }
    d.shuffleDeck();
    d.DealCards(Players);//deals the cards
    for(int i=0;i<Players+1;i++){
        bool turn=true;//resets for every player
        if(!d.players[i].ai){//for a human player
            while(turn&&!won){//will stay until they bust or win or stay
                cout<<"Player "<<i+1<<", your hand is ";
                if(d.players[i].sum==21){
                    cout<<"Blackjack! you win!"<<endl;
                    won=true;
                    d.setWon(true);
                    break;
                }
                int j=0;
                while(d.players[i].hand[j]!=NULL){
                    d.printCard(d.players[i].hand[j]->number,d.players[i].hand[j]->suit);//cout<<d.players[i].hand[j]->number<<" of "<<d.players[i].hand[j]->suit;
                    if(d.players[i].hand[j+1]!=NULL)
                        cout<<", ";
                    j++;
                }
                cout<<", for a sum of "<<d.players[i].sum<<".\nWould you like to\n1.Hit\n2.Stay\n3.See what the other hands are"<<endl;
                getline(cin,operation);
                op=stoi(operation);
                switch(op){
                    case 1:
                        turn=d.hit(i, Players);//if they bust or win it will end their turn
                        break;
                    case 2:
                        turn=false;//ends turn
                        break;
                    case 3:
                        d.peek(Players);
                        break;
                    default:
                        cout<<"That is not a valid option."<<endl;
                }
                won=d.getWon();
            }
        }
        else{//for AI
            while(turn&&!won){
                if(i==Players)
                    cout<<"Dealer's hand is [hidden], ";
                else
                    cout<<"Player "<<i+1<<"'s hand is [hidden], ";
                int j=1;
                while(d.players[i].hand[j]!=NULL){
                    d.printCard(d.players[i].hand[j]->number,d.players[i].hand[j]->suit);//cout<<d.players[i].hand[j]->number<<" of "<<d.players[i].hand[j]->suit;
                    if(d.players[i].hand[j+1]!=NULL)
                        cout<<", ";
                    j++;
                }
                if(d.players[i].sum<17){//will automatically hit if the sum is less than 17
                    if(i==Players)
                        cout<<".\nDealer hits"<<endl;
                    else
                        cout<<".\nPlayer "<<i+1<<" hits."<<endl;
                    turn=d.hit(i, Players);
                }
                else{
                    if(i==Players)
                        cout<<".\nDealer stays"<<endl;
                    else
                        cout<<".\nPlayer "<<i+1<<" stays."<<endl;
                    turn=false;
                }
            won=d.getWon();
            }
        }
    }
    if(!won){
        d.declare(Players);//declares the winner
    }
    cout<<"Would you like to play again? (Y/N)"<<endl;
    //getline(cin, holder);
    getline(cin, play);
    if(play=="y"||play=="Y")
        goto start;
    return 0;
}

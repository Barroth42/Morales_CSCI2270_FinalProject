#include <iostream>
#include <string>
#include "Deck.h"
#include <stdlib.h>
using namespace std;
int main(){
    string players, operation, ai;
    int Players, Spot, AI, op, hoomans;
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
    d.DealCards(Players);//deals the cards
    for(int i=0;i<Players;i++){
        bool turn=true;//resets for every player
        if(!d.players[i].ai){//for a human player
            while(turn){//will stay until they bust or win or stay
                cout<<"Player "<<i+1<<", your hand is "<<d.players[i].hand<<".\nWould you like to\n1.Hit\n2.Stay\n3.See what the other hands are"<<endl;
                getline(cin,operation);
                op=stoi(operation);
                switch(op){
                    case 1:
                        turn=d.hit(i);//if they bust or win it will end their turn
                        break;
                    case 2:
                        turn=false;//ends turn
                        break;
                    case 3:
                        d.peek();
                        break;
                    default:
                        cout<<"That is not a valid option."<<endl;
                }
            }
        }
        else{//for AI
            while(turn){
                cout<<"Player "<<i+1<<"'s hand is "<<d.players[i].hand<<endl;
                if(d.players[i].sum<17){//will automatically hit if the sum is less than 17
                    cout<<"Player "<<i+1<<" hits."<<endl;
                    turn=d.hit(i);
                }
                else{
                    cout<<"Player "<<i+1<<" stays."<<endl;
                    turn=false;
                }
            }
        }
    }
    d.dealer();//plays for the dealer
    d.declare();//declares the winner
    return 0;
}

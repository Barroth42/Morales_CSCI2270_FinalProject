#include <iostream>
#include <string>
#include "Deck.h"
#include <stdlib.h>
using namespace std;
int main(){
    string players, operation, ai;
    int Players, Spot, AI, op, hoomans;
    playahs:
    cout<<"How many players will there be? (5 max)"<<endl;
    getline(cin,players);
    Players=stoi(players);
    if(Players<0||Players>5){
        cout<<"Not a valid number."<<endl;
        goto playahs;
    }
    ai_players:
    cout<<"How many players will be AI? (0-"<<Players<<")"<<endl;
    getline(cin,ai);
    AI=stoi(ai);
    if(AI<0||AI>Players){
        cout<<"Not a valid number."<<endl;
        goto ai_players;
    }
    Deck d(Players);
    if(AI!=0){
        hoomans=Players-AI;
        for(int i=0;i<hoomans;i++){
            Spot=rand()%Players-1;
            d.player[Spot].ai=false;
        }
    }
    else{
        for(int i=0;i<Players;i++){
            d.player[i].ai=false;
        }
    }
    d.DealCards(Players);
    for(int i=0;i<Players;i++){
        bool turn=true;
        if(!d.player[i].ai){
            while(turn){
                cout<<"Player "<<i+1<<", your hand is "<<d.player[i].hand<<".\nWould you like to\n1.Hit\n2.Stay\n3.See what the other hands are"<<endl;
                getline(cin,operation);
                op=stoi(operation);
                switch(op){
                    case 1:
                        turn=d.hit(i);
                        break;
                    case 2:
                        turn=false;
                        break;
                    case 3:
                        d.peek();
                        break;
                    default:
                        cout<<"That is not a valid option."<<endl;
                }
            }
        }
        else{
            while(turn){
                cout<<"Player "<<i+1<<"'s hand is "<<d.player[i].hand<<endl;
                if(d.player[i].sum()<17){
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
    d.dealer();
    d.declare();
    return 0;
}

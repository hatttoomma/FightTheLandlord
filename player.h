
#ifndef PLAYER_H
#define PLAYER_H

#include <fstream>
#include <algorithm>
#include <cstring>
class player{
public:
    int cardNumber;
    int cards[20];
    bool landlord;
    bool active;
    int turns;
    player(){
        cardNumber=17;
        memset(cards,0,sizeof(cards));
        landlord=0;
        turns=0;
        active=1;
    }

    //输出状态，用于存档
    void print(){
        std::ofstream outFile;
        outFile<<cardNumber<<" "<<std::endl;
        for(int i=0;i<20;i++)outFile<<cards[i]<<" ";
        outFile<<std::endl;
        outFile<<landlord<<std::endl;
        outFile<<active<<std::endl;
        outFile<<turns<<std::endl;
    }
    player (player &o){
        cardNumber=o.cardNumber;
        std::copy(std::begin(o.cards),std::end(o.cards),std::begin(cards));
        landlord=o.landlord;
        active=o.active;
        turns=o.turns;
    }

};

player Player[3];

#endif // PLAYER_H

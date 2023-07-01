
#ifndef PLAYER_H
#define PLAYER_H

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
};

player Player[3];

#endif // PLAYER_H

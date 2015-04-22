#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <vector>

class Player
{
public:
    Player();
    virtual ~Player();
protected:
private:
    int curId; // Id of current node
    int curIndex; // Index of current node
};

#endif //PLAYER_H

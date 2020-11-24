//
// Created by oushi on 2020/8/17.
//

#ifndef Q_LEARNING_ENV_H
#define Q_LEARNING_ENV_H

#include <vector>
#include <iostream>

struct MyPlayer{
    std::vector<int> State;
    std::vector<std::vector<int> > Actions;
    int Size;
    std::vector<std::vector<int> > Holes;
};

class env {
public:
    MyPlayer myPlayer;

    void NewPlayer();
    int step(int);
    bool isHole(int,int);
    std::vector<int> getState();
    std::string getString(int,int);
    void Render();
    void Reset();
    bool GameDone(int,int);
};


#endif //Q_LEARNING_ENV_H

//
// Created by oushi on 2020/8/17.
//

#include "env.h"


void env::NewPlayer() {
    myPlayer.State.resize(2,0);
    int tempActions [4][2] ={
            {-1, 0},//上
            {0, -1},//左
            {1, 0},//下
            {0, 1},//右
    };
    myPlayer.Actions.resize(4,std::vector<int>(2, 0));
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            myPlayer.Actions[i][j] = tempActions[i][j];
        }
    }
    myPlayer.Size = 6;
    int tempHoles[3][2] = {
            {1,1},
            {2,2},
            {3,3},
    };
    myPlayer.Holes.resize(3,std::vector<int>(2,0));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            myPlayer.Holes[i][j] = tempHoles[i][j];
        }
    }
}

bool env::isHole(int x,int y){
    for (int i = 0; i < 3; i++) {
        if (myPlayer.Holes[i][0] == x && myPlayer.Holes[i][1] == y){
            return true;
        }
    }
    return false;
}

int env::step(int actionIndex){
    std::vector<int> actions = myPlayer.Actions[actionIndex];
    myPlayer.State[0] += actions[0];
    myPlayer.State[1] += actions[1];

    if (myPlayer.State[0] < 0) {
        myPlayer.State[0] = 0;
    }
    if (myPlayer.State[1] < 0) {
        myPlayer.State[1] =0;
    }
    if (myPlayer.State[0] >= myPlayer.Size){
        myPlayer.State[0] = myPlayer.Size - 1;
    }
    if (myPlayer.State[1] >= myPlayer.Size){
        myPlayer.State[1] = myPlayer.Size - 1;
    }

    if (isHole(myPlayer.State[0],myPlayer.State[1])){
        return -100;
    }
    if (myPlayer.State[0] == myPlayer.Size -1 && myPlayer.State[1] == myPlayer.Size -1){
        return 100;
    }
    return -1;
}

std::vector<int> env::getState() {
    std::vector<int> result;
    result.resize(2,0);
    for (int i =0; i < 2 ;i++){
        result[i] = myPlayer.State[i];
    }
    return result;
}

std::string env::getString(int x,int y){
//    if (x == 0 && y ==0 ){
//        return "S";
//    }
    if (x == myPlayer.State[0] && y == myPlayer.State[1] ){
        return "~";
    }
    if (x == myPlayer.Size-1 && y == myPlayer.Size-1 ){
        return "G";
    }
    if ( isHole(x,y)){
        return "H";
    }
    return "O";
}

void env::Render() {
    std::string graph = "\n";
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++ ){
            graph += getString(i, j);
        }
        graph += "\n";
    }
    std::cout << graph ;
}

void env::Reset() {
    myPlayer.State[0] = 0;
    myPlayer.State[1] = 0;
}

bool env::GameDone(int x,int y) {
    if (x == myPlayer.Size-1 && y == myPlayer.Size-1 ){
        return true;
    }
    return false;
}
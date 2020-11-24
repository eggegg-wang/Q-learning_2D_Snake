//
// Created by oushi on 9/28/2020.
//

#include "Vector2D.h"
#include "Q.h"
#include "env.h"


void Vector2D::run(){

    Q q;
    env envc;
    bool isDone;
    std::vector<int> oldState;
    std::vector<int> newState;
    int action;
    int reward;
    std::string myMapKey;
    std::string myMapVal;
    int count = 0;
/*--------------------------------------------------------------------*/
//    std::vector<int> tempKey;
//    std::vector<double> tempVal;
//    std::ifstream ins("D:\\Ademo\\C++\\98Test\\map.txt");
//    while(!ins.eof()){
//        std::string temp;
//        ins >> temp;
//        std::vector<std::string> tempstr = split(temp ,"=");
//
//        std::string key = tempstr[0].c_str();
//        std::vector<std::string> tempk = split(key,",");
//        std::string value = tempstr[1].c_str();
//        std::vector<std::string> tempv = split(value,",");
//
//        tempKey.resize(2,0);
//        for (int i = 0; i < 2; i++) {
//            tempKey[i] = convertStringToInt(tempk[i]);
//        }
//        tempVal.resize(4,0);
//        for (int i = 0; i < 4; i++) {
//            tempVal[i] = convertStringToDouble(tempv[i]);
//        }
//        q.myAgent.Qtable[tempKey].resize(4,0);
//        q.myAgent.Qtable[tempKey] = tempVal;
//    }
    //read(q);

/*--------------------------------------------------------------------*/


    envc.NewPlayer();
    q.NewAgent(3);

    for (int i = 0; i < 20; i++) {
        envc.Reset();
        isDone = false;
        while ( !isDone ) {
            count ++;
            oldState = envc.getState();
            //oldState = {envc.player.State[0],envc.player.State[0]};
            action = q.ChooseAction(oldState);

            std::cout << action << std::endl;

            reward = envc.step(action);
            newState = envc.getState();

            std::cout << oldState[0] << "," << oldState[1] << std::endl;

            q.UpdataQ(oldState, action, reward, newState);
            for(int i =0 ; i<4 ;i++){
                std::cout << q.myAgent.Qtable[oldState][i] << " ";
            }
            std::cout << std::endl;

            myMapKey = q.convertIntToString(oldState[0]) + "," + q.convertIntToString(oldState[1]);
            myMapVal = q.convertDoubleToString(q.myAgent.Qtable[oldState][0]) + "," +
                       q.convertDoubleToString(q.myAgent.Qtable[oldState][1]) + "," +
                       q.convertDoubleToString(q.myAgent.Qtable[oldState][2]) + "," +
                       q.convertDoubleToString(q.myAgent.Qtable[oldState][3]);
            if (q.myMap.count(myMapKey) > 0){
                q.myMap[myMapKey] = myMapVal;
            }else{
                q.myMap.insert(make_pair(myMapKey,myMapVal));
            }

            envc.Render();
            isDone = envc.GameDone(newState[0],newState[1]);
            //Sleep(1000);
            if (isDone) {
                //Sleep(2000);
                std::cout << "GAME OVER" << std::endl;
/*-------------------------------------------------------*/
//                std::ofstream ous("D:\\Ademo\\C++\\98Test\\map.txt");
//                std::map<std::string,std::string >::iterator iter= q.myMap.begin();
//                for(;iter!=q.myMap.end();iter++){
//                    ous<< iter->first << "=" << iter->second << std::endl;
//                }
                q.save();
/*-------------------------------------------------------*/
                std::cout << "count: " <<count << std::endl;
            }
        }
    }
}

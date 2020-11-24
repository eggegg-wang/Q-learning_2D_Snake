//
// Created by oushi on 2020/6/3.
//

#include "Q.h"
#include <iostream>
#include <cstring>
#include <strstream>

std::vector<std::string> Q::split(const std::string& str, const std::string& delim){
    std::vector<std::string> res;
    if("" == str) return res;
    //先将要切割的字符串从string类型转换为char*类型
    char * strs = new char[str.length() + 1];
    strcpy(strs, str.c_str());
    char * d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());
    char *p = strtok(strs, d);
    while(p){
        std::string s = p;  //分割得到的字符串转换为string类型
        res.push_back(s); //存入结果数组
        p = strtok(NULL, d);
    }
    return res;
}

std::string Q::convertDoubleToString(const double val)
{
    std::string s;
    std::strstream ss;
    ss << val;
    ss >> s;
    return s;
}

std::string Q::convertIntToString(const int val)
{
    std::string s;
    std::strstream ss;
    ss << val;
    ss >> s;
    return s;
}

int Q::convertStringToInt(const std::string &s)
{
    int val;
    std::strstream ss;
    ss << s;
    ss >> val;
    return val;
}

double Q::convertStringToDouble(const std::string &s)
{
    double val;
    std::strstream ss;
    ss << s;
    ss >> val;
    return val;
}

double maxQ(std::vector<double> &Qtable){
    double biggest = *std::max_element(Qtable.begin(), Qtable.end());
    return biggest;
}

int randomInt(){
    return (rand() % (4));
}

double randomDouble(){
    return rand() / double(RAND_MAX);
}


void Q::save() {
    std::ofstream ous("D:\\Ademo\\C++\\98Test\\map.txt");
    std::map<std::string,std::string >::iterator iter= myMap.begin();
    for(;iter!=myMap.end();iter++){
        ous<< iter->first << "=" << iter->second << std::endl;
    }
}


std::map<std::vector<int>,std::vector<double> > Q::getQtable(){
    return myAgent.Qtable;
};

void Q::read(){
    std::vector<int> tempKey;
    std::vector<double> tempVal;
    std::ifstream ins("D:\\Ademo\\C++\\98Test\\map.txt");
    while(!ins.eof()){
        std::string temp;
        ins >> temp;
        std::vector<std::string> tempstr = split(temp ,"=");

        std::string key = tempstr[0].c_str();
        std::vector<std::string> tempk = split(key,",");
        std::string value = tempstr[1].c_str();
        std::vector<std::string> tempv = split(value,",");

        tempKey.resize(2,0);
        for (int i = 0; i < 2; i++) {
            tempKey[i] = convertStringToInt(tempk[i]);
        }
        tempVal.resize(4,0);
        for (int i = 0; i < 4; i++) {
            tempVal[i] = convertStringToDouble(tempv[i]);
        }
        myAgent.Qtable[tempKey].resize(4,0);
        myAgent.Qtable[tempKey] = tempVal;
    }
}

void Q::NewAgent(int actionSpace) {
    myAgent.Alpha = 0.2;
    myAgent.Gamma = 0.8;
    myAgent.Eposilon = 0.7;
    myAgent.ActionSpace = actionSpace;
    read();
}

int Q::ChooseAction(std::vector<int> state) {


    if (randomDouble() < myAgent.Eposilon){
        return randomInt();
    } else{
        std::vector<double> actions = getActionByState(state);
//        std::vector<double>::iterator biggest = std::max_element(std::begin(actions),std::end(actions));
        int maxActionIndex = (int)(std::max_element(actions.begin(),
                                                    actions.end()) -
                                                            (actions.begin()));

        return maxActionIndex;
    }
}


std::vector<double> Q::getActionByState(std::vector<int>state){
    if (myAgent.Qtable.count(state) == 0) {
        myAgent.Qtable[state].resize(4,0);
        return myAgent.Qtable[state];
    }
    return myAgent.Qtable[state];
}

void Q::UpdataQ(std::vector<int>& state,int action,double reward,std::vector<int> &newstate){
    std::vector<double> currentQ = getActionByState(state);
    std::vector<double> NextStatQVal = getActionByState(newstate);
    double maxNextStatQVal = maxQ(NextStatQVal);
    double oldQVal = currentQ[action];
    myAgent.Qtable[state][action] = (1 - myAgent.Alpha) * oldQVal + myAgent.Alpha * (reward + myAgent.Gamma * maxNextStatQVal);
}

void Q::saveQtable(std::map<std::vector<int>,std::vector<double> >){
    std::ifstream ins("text.txt");
    std::ofstream ous("text.txt");
}

//
// Created by oushi on 10/19/2020.
//
//int main(){
////根据key从文件中读出相应的value
//    map<string, string > myMap;
//    ifstream ous("D:\\Ademo\\C++\\98Test\\demo\\text.txt");
//
//
//    while(!ous.eof()){
//        string temp;
//        ous>>temp;
//        vector<string> tempstr = split(temp ,"=");
//
//        string key = tempstr[0].c_str();
//       // vector<string> tempkey = split(key,",");
//        string value = tempstr[1].c_str();
//        //vector<string> tempv = split(value,",");
////        vector<int> haha;
////        haha.resize(2,0);
////        for (int i = 0; i < 2; ++i) {
////            haha[i] = convertStringToInt(tempv[i]);
////        }
//
//        myMap.insert(make_pair(key,value)); //将字符串转换为键值对
//    }
//    for(map<string,string>::iterator itr=myMap.begin();itr!=myMap.end();itr++){
//        cout<< itr->second <<endl; //
//    }
//
//
//    return 0;
//}
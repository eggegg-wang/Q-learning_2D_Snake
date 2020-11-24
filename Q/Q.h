//
// Created by oushi on 2020/6/3.
//

#ifndef Q_LEARNING_Q_H
#define Q_LEARNING_Q_H
#include <iostream>
#include <map>
#include <vector>
#include<fstream>
#include <ctime>
#include <algorithm>
#include <cstdlib>

struct MyAgent{
    double Alpha;
    double Gamma;
    double Eposilon;
    int ActionSpace;
    std::map<std::vector<int>,std::vector<double> > Qtable;
};

class Q {
public:
    MyAgent myAgent;

    std::map<std::vector<int>,std::vector<double> > getQtable();
    std::map<std::string, std::string > myMap;
    //std::map<std::vector<int>,std::vector<double> > Qtable;
    void NewAgent(int actionSpace);
    int ChooseAction(std::vector<int> state);
    std::vector<double> getActionByState(std::vector<int>);
    void UpdataQ(std::vector<int>&,int,double ,std::vector<int>&);
    void save();
    void read();

    std::vector<std::string> split(const std::string& str, const std::string& delim);
    std::string convertDoubleToString(const double val);
    std::string convertIntToString(const int val);
    int convertStringToInt(const std::string &s);
    double convertStringToDouble(const std::string &s);

    std::map<std::vector<int>,std::vector<double> > readQtable();
    void saveQtable(std::map<std::vector<int>,std::vector<double> >);
};


#endif //Q_LEARNING_Q_H

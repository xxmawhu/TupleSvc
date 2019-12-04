#include "HadronInfo/DecayInf.h"
#include <iostream>
#include "math.h"
using namespace std;
vector<int> DecayInf::getChildren(int pid){
    int PID = pid>0 ? pid: -pid;
    vector<int> children;
    if(PID==223){
        children.push_back(211);
        children.push_back(211);
        children.push_back(111);
        return children;
    }
    if(PID==3212){
        children.push_back(11);
        children.push_back(3122);
        return children;
    }
}

DecayInf::DecayInf(){
}
DecayInf::~DecayInf(){
}

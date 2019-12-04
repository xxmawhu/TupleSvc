/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin Ma
#   Email         : xxmawhu@163.com
#   File Name     : DecayMode.h
#   Create Time   : 2019-12-04 14:39
#   Last Modified : 2019-12-04 14:39
#   Describe      :
#
# ====================================================*/
#ifndef  _DECAYMODE_H
#define  _DECAYMODE_H
#include <vector>
class DecayMode{
public:
    DecayMode(std::vector<int> fid);
    virtual ~DecayMode();
    // the particle name with index, such as pion, pion2
    string ParicleName(const int&);

private:
    /* data */
};
#endif // _DECAYMODE_H



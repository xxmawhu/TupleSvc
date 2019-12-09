/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin Ma
#   Email         : xxmawhu@163.com
#   File Name     : DecayTree.h
#   Create Time   : 2019-12-04 14:39
#   Last Modified : 2019-12-09 13:23
#   Describe      :
#
# ====================================================*/
#ifndef TupleSvc_DecayTree_H
#define TupleSvc_DecayTree_H
#include "HadronInfo/ParticleInf.h"
#include <vector>
using std::vector;
class DecayTree {
   public:
    DecayTree();
    DecayTree(const vector<int>& fid);
    virtual ~DecayTree();
    // the particle name with index, such as pion, pion2
    const string& ParicleName(const int&);
    // return the index, input the particle name
    const int& index(const string& particle_name);
    // the length of particle list
    const int& size();
    const int& PID(const int&);
    // the the decay mode of the mode of particle `i`
    const DecayTree& decay(const int& i);

   private:
    vector<int> m_finalParticleID;
    vector<int> m_particleIndex;
    vector<string> m_particleName;
    vector<DecayTree> m_childDecayTree;
    ParticleInf m_particleInfo;
};
#endif  // _DECAYMODE_H

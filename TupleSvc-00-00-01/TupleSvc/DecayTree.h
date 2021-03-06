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
    const vector<int>& GetFID() const;
    string GetName(const int& i) const;
    int PID(const int&) const;
    // return the index, input the particle name
    int Index(const string& particle_name);
    // the length of particle list
    int size() const;
    bool SelfConjugate() const;
    // the the decay mode of the mode of particle `i`
    const DecayTree& decay(const int& i);
    const DecayTree& GetChannelCC() const;
    friend bool operator==(const DecayTree&, const DecayTree&);
    friend std::ostream& operator<<(std::ostream& os, const DecayTree& dt);

   private:
    vector<int> m_finalParticleID;
    vector<int> m_particleIndex;
    vector<string> m_particleName;
    vector<DecayTree> m_childDecayTree;
    ParticleInf m_particleInfo;
};
#endif  // _DECAYMODE_H

/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin Ma
#   Email         : xxmawhu@163.com
#   File Name     : DecayTree.cxx
#   Create Time   : 2019-12-04 14:39
#   Last Modified : 2019-12-09 13:27
#   Describe      :
#
# ====================================================*/
#include "HadronInfo/ParticleInf.h"
#include "TupleSvc/DecayTree.h"
#include <vector>
using std::vector;
DecayTree::DecayTree(const vector<int> &fid) {
    m_finalParticaleID = fid;
    // obtain the particle index
    for (int i = 0; i < fid.size(); ++i) {
        m_particleIndex.push_back(0);
        for (int j = 0; j <= i; ++j) {
            if (fid[i] == fid[j]) m_particleIndex[i]++;
        }
    }
    // set the particle name
    string name(""), dd;
    for (int i = 0; i < fid.size(); ++i) {
        m_particleInfo.SetChildren(fid[i]);
        name = m_particleInfo.Name(fid[i]);
        if (index[i] > 1) {
            stringstream ss;
            ss << m_particleIndex[i];
            ss >> dd;
            name += dd;
        }
        m_particleName.push_back(name);
    }
}
virtual DecayTree::~DecayTree() {
    m_finalParticaleID.clear();
    m_particleIndex.clear();
    m_particleName.clear();
}
// the particle name with index, such as pion, pion2
const string &DecayTree::ParicleName(const int &i) { return m_particleName[i]; }

const int &DecayTree::index(const string &particle_name) {
    vector<string>::iterator p =
        std::find(m_particleName.begin(), m_particleName.end(), particle_name);
    if (p != m_particleName.end()) {
        return p - m_particleName.begin();
    } else {
        return -1;
    }
}

const int &DecayTree::size() { return m_finalParticaleID.size(); }

const DecayTree &DecayTree::decay(const int &i) {
    vector<int> m_tmp;
    m_tmp.push_back(m_finalParticaleID[i]);
    return DecayTree(m_tmp);
}

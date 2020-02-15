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
#include "HadronInfo/Majorana.h"
#include "TupleSvc/DecayTree.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using std::vector;
DecayTree::DecayTree() {}

DecayTree::DecayTree(const vector<int> &fid) {
    m_finalParticleID = fid;
    // obtain the particle index
    for (int i = 0; i < fid.size(); ++i) {
        m_particleIndex.push_back(0);
        for (int j = 0; j <= i; ++j) {
            if (fid[i] == fid[j]) m_particleIndex[i]++;
        }
    }
    // set the particle name
    string name, dd;
    m_particleInfo.SetChildren(fid);
    for (int i = 0; i < fid.size(); ++i) {
        name = m_particleInfo.Name(fid[i]);
        if (m_particleIndex[i] > 1) {
            std::stringstream ss;
            ss << m_particleIndex[i];
            ss >> dd;
            name += dd;
        }
        m_particleName.push_back(name);
    }
}

DecayTree::~DecayTree() {
    m_finalParticleID.clear();
    m_particleIndex.clear();
    m_particleName.clear();
}

const vector<int> &DecayTree::GetFID() const { return m_finalParticleID; }

// the particle name with index, such as pion, pion2
string DecayTree::GetName(const int &i) const {
    return m_particleName[i];
}

int DecayTree::Index(const string &particle_name) {
    vector<string>::iterator p =
        std::find(m_particleName.begin(), m_particleName.end(), particle_name);
    if (p != m_particleName.end()) {
        return p - m_particleName.begin();
    } else {
        return -1;
    }
}

int DecayTree::size() const { return m_finalParticleID.size(); }

int DecayTree::PID(const int &i) const {
    return m_finalParticleID[i];
}

const DecayTree &DecayTree::decay(const int &i) {
    vector<int> m_tmp;
    m_tmp.push_back(m_finalParticleID[i]);
    return DecayTree(m_tmp);
}
const DecayTree& DecayTree::GetChannelCC() const {
    vector<int> fidcc;
    for (vector<int>::const_iterator itr = m_finalParticleID.begin(); 
            itr != m_finalParticleID.end(); ++itr) {
        if (majorana.contained(*itr)) {
            fidcc.push_back(*itr);
        } else {
            fidcc.push_back((*itr) * (-1));
        }
    }
    return DecayTree(fidcc);
}
bool operator==(const DecayTree& a, const DecayTree&b) {
    vector<int> a_fid = a.GetFID();
    vector<int> b_fid = b.GetFID();
    if (a_fid.size() != b_fid.size()) return false;
    std::sort(a_fid.begin(), a_fid.end());
    std::sort(b_fid.begin(), b_fid.end());
    for(int i=0; i< a_fid.size(); ++i) {
        if (a_fid[i] != b_fid[i]) return false;
    }
    return true;
}

bool DecayTree::SelfConjugate() const{
    const DecayTree& conjugate = this->GetChannelCC();
    return (conjugate == *this);
}

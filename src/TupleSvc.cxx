/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : TupleSvc.cxx
#   Create Time   : 2019-12-09 12:58
#   Last Modified : 2019-12-09 12:58
#   Describe      :
#
# ====================================================*/
#include <iostream>
#include "HadronInfo/TrackInfo.h"
#include "HadronInfo/Pi0Info.h"
#include "HadronInfo/EtaInfo.h"
#include "HadronInfo/LamInfo.h"
#include "HadronInfo/KsInfo.h"
#include "HadronInfo/OmegaInfo.h"
#include "TupleSvc/TupleSvc.h"
#include "TupleSvc/DecayTree.h"
#include <cstdlib>

using std::string;
using std::cout;
using std::endl;
TupleSvc::TupleSvc() : m_intItemItr(0), m_doubleItemItr(0), m_arrayItemItr(0) {
    vector<int> fid;
    m_decayMode = DecayTree(fid);
}

TupleSvc::~TupleSvc() {}

void TupleSvc::SetItemAddress(const string& type_name,
        NTuple::Item<double>* m_tuple,
        const int& max_length) {
    m_doubleItemItr = m_tuple;
    m_doubleLength = max_length;
}

void TupleSvc::SetItemAddress(const string& type_name,
        NTuple::Item<int>* m_tuple,
        const int& max_length) {
    m_intItemItr = m_tuple;
    m_intLength = max_length;
}

void TupleSvc::SetArrayAddress(const string& type_name,
        NTuple::Array<double>* m_tuple,
        const int& max_length) {
    m_arrayItemItr = m_tuple;
    m_arrayLength = max_length;
}

void TupleSvc::SetDecayTree(const DecayTree& decayMode) {
    m_decayMode = decayMode;
}

bool TupleSvc::InitTuple(NTuple::Tuple* tuple) {
    this->InitItemIndex();
    if (m_doubleItemIndex.size() > m_doubleLength) {
        cout << "Error: the length of NTuple::Item<double> is larger than " 
            << m_doubleLength << endl
            << "the length should be larger than  " 
            <<m_doubleItemIndex.size() << endl;
        std::exit(1);
    }
    if (m_intItemIndex.size() > m_intLength) {
        cout << "Error: the length of NTuple::Item<int> is larger than " 
            << m_doubleLength << endl
            << "the length should be larger than  " 
            <<m_intItemIndex.size() << endl;
        std::exit(1);
    }
    if (m_ArrayIndex.size() > m_arrayLength) {
        cout << "Error: the length of NTuple::Array<double> is larger than " 
            << m_arrayLength << endl
            << "the length should be larger than  " 
            <<m_ArrayIndex.size() << endl;
        std::exit(1);
    }
    // add int
    for(map<string, int>::iterator itr=m_intItemIndex.begin();
            itr!= m_intItemIndex.end();
            ++itr){
        tuple->addItem(itr->first, m_intItemItr[itr->second]);
    }

    // add double
    for(map<string, int>::iterator itr=m_doubleItemIndex.begin();
            itr!= m_doubleItemIndex.end();
            ++itr){
        tuple->addItem(itr->first, m_doubleItemItr[itr->second]);
    }

    // add p4
    for(map<string, int>::iterator itr=m_ArrayIndex.begin();
            itr!= m_ArrayIndex.end();
            ++itr){
        tuple->addItem(itr->first, 4, m_arrayItemItr[itr->second]);
    }
}

void TupleSvc::InitItemIndex() {
    // only consider the following case: KsInfo, LamInfo, OmegaInfo,
    // TrackInfo: pion, kaon, proton, photon
    // Pi0Info, EtaInfo
    int int_tmp_index = 0, double_tmp_index = 0, array_tmp_index = 0;
    int PID;
    for (int i = 0; i < m_decayMode.size(); ++i) {
        const string& name = m_decayMode.ParicleName(i);
        PID = m_decayMode.PID(i);
        AvailableInfo avaiableInfo;
        if (PID == 310) {
            KsInfo ksInfo;
            avaiableInfo = ksInfo;
        }
        if (PID == 3122) {
            LamInfo lamInfo;
            avaiableInfo = lamInfo;
        }
        if (PID == 11 || PID == 2212 || PID == 22 || PID == 211 || PID == 312) {
            TrackInfo trackInfo(PID);
            avaiableInfo = trackInfo;
        }
        if (PID == 221) {
            Pi0Info pi0Info;
            avaiableInfo = pi0Info;
        }
        if (PID == 322) {
            EtaInfo etaInfo;
            avaiableInfo = etaInfo;
        }
        const vector<string>& doubleList = avaiableInfo.GetDoubleInf();
        for (vector<string>::const_iterator itr = doubleList.begin();
                itr != doubleList.end(); ++itr) {
            m_doubleItemIndex.insert(
                    pair<string, int>(name + (*itr), double_tmp_index++));
        }
        const vector<string>& intList = avaiableInfo.GetIntInf();
        for (vector<string>::const_iterator itr = intList.begin();
                itr != intList.end(); ++itr) {
            m_intItemIndex.insert(
                    pair<string, int>(name + (*itr), int_tmp_index++));
        }
        const vector<string>& arrayList = avaiableInfo.GetP4Inf();
        for (vector<string>::const_iterator itr = arrayList.begin();
                itr != arrayList.end(); ++itr) {
            m_ArrayIndex.insert(
                    pair<string, int>(name + (*itr), array_tmp_index));
        }
    }
}

void TupleSvc::Fill(const string& particle_name, 
        const string& observable,
        const int& value){
    int i  =  m_intItemIndex[particle_name+observable];
    m_intItemItr[i] = value;
}


void TupleSvc::Fill(const string& particle_name, 
        const string& observable,
        const double& value){
    int i  =  m_doubleItemIndex[particle_name+observable];
    m_doubleItemItr[i] = value;
}


void TupleSvc::Fill(const string& particle_name, 
        const string& observable,
        const HepLorentzVector& p4){
    int index  =  m_ArrayIndex[particle_name+observable];
    for(int i=0; i< 4; ++i ) {
        m_arrayItemItr[index][i] = p4[i];
    }
}


void TupleSvc::Fill(const int& particle_index, const string& observable,
        const double& value){
    Fill(m_decayMode.ParicleName(particle_index), observable, value);
}
void TupleSvc::Fill(const int& particle_index, const string& observable,
        const int& value){
    Fill(m_decayMode.ParicleName(particle_index), observable, value);

}
void TupleSvc::Fill(const int& particle_index, const string& observable,
        const HepLorentzVector& p4){
    Fill(m_decayMode.ParicleName(particle_index), observable, p4);

}

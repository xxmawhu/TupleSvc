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
#include "TupleSvc/TupleSvc.h"

using std::string;
using std::cout;
using std::endl;
TupleSvc::TupleSvc() : m_intItemItr(0), m_doubleItemItr(0), m_arrayItemItr(0) {}

TupleSvc::~TupleSvc() {}

void TupleSvc::SetItemAddress(string type_name, NTuple::Item<double> *m_tuple,
                              int max_length) {
    m_doubleItemItr = m_tuple;
    m_doubleLength = max_length;
}

void TupleSvc::SetItemAddress(string type_name, NTuple::Item<int> *m_tuple,
                              int max_length) {
    m_intItemItr = m_tuple;
    m_intLength = max_length;
}

void TupleSvc::SetArrayAddress(string type_name, NTuple::Array<double> *m_tuple,
                               int max_length) {
    m_arrayItemItr = m_tuple;
    m_arrayLength = max_length;
}

void TupleSvc::SetDecayMode(const DecayMode &decayMode) {
    m_decayMode = decayMode;
}

bool TupleSvc::InitTuple(NTuple::Tuple *tuple) {}

void TupleSvc::InitItemIndex() {
    // only consider the following case: KsInfo, LambInfo, OmegaInfo,
    // TrackInfo: pion, kaon, proton, photon
    // Pi0Info, EtaInfo
}

void TupleSvc::InitArrayIndex() {}

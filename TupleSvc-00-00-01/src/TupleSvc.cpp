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
#include "HadronInfo/ShowerInfo.h"
#include "HadronInfo/ElectronInfo.h"
#include "HadronInfo/KaonInfo.h"
#include "HadronInfo/PionInfo.h"
#include "HadronInfo/ProtonInfo.h"
#include "HadronInfo/Pi0Info.h"
#include "HadronInfo/EtaInfo.h"
#include "HadronInfo/LamInfo.h"
#include "HadronInfo/KsInfo.h"
#include "HadronInfo/OmegamInfo.h"
#include "TupleSvc/TupleSvc.h"
#include "TupleSvc/DecayTree.h"
#include <cstdlib>

using std::string;
using std::map;
using std::cout;
using std::endl;

TupleSvc::TupleSvc(int maxI, int maxD, int maxVi, int maxVd)
    : m_tp(0) {
 //  I_Ptr = new NTuple::Item<int>[maxI];
 //  std::cout << "Info in <TupleSvc::TupleSvc>:"
 //     <<" maxI = " << maxI<< std::endl;
   m_MaxSizeI = maxI;
   D_Ptr = new NTuple::Item<double>[maxD];
   m_MaxSizeD = maxD;
  Vi_Ptr = new NTuple::Array<int>[maxVi];
   m_MaxSizeVi = maxVi;
 //  Vd_Ptr = new NTuple::Array<double>[maxVd];
   m_MaxSizeVd = maxVd;
}

TupleSvc::~TupleSvc() {
   //delete[] I_Ptr;
   //delete[] D_Ptr;
   //delete[] Vi_Ptr;
   //delete[] Vd_Ptr;
}

bool TupleSvc::BindTuple(NTuple::Tuple *tuple) {
    if (m_tp) {
        cout << "Error:: this TupleSvc is binding with a TupleSvc already!!!"
             << endl;
        return false;
    }
    m_tp = tuple;
    return true;
}

void TupleSvc::Write() {
    if (m_tp) {
        m_tp->write();
    } else {
        cout << "The TupleSvc is not binded properly" << endl;
    }
}

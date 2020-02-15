/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin Ma
#   Email         : xxmawhu@163.com
#   File Name     : DecayChainSvc.h
#   Create Time   : 2019-12-04 14:39
#   Last Modified : 2020-02-14 09:37
#   Describe      :
#
# ====================================================*/
#ifndef TupleSvc_DecayChainSvc_H
#define TupleSvc_DecayChainSvc_H
#include "BesDChain/CDCandidate.h"
#include "BesDChain/CDDecay.h"
#include "HadronInfo/ParticleInf.h"
#include "HadronInfo/util.h"
#include "TupleSvc/DecayTree.h"
#include "TupleSvc/TupleSvc.h"
#include <vector>
#include <string>
#include "BesDChain/CDDecayList.h"
class DecayChainSvc {
   public:
    DecayChainSvc();
    ~DecayChainSvc() {};
    void SetDecayTree(const DecayTree decayTree) { m_decayTree = decayTree; }
    void SetTitle(const std::string& title) { m_title = title; }
    template <class T>
    bool SubRegister(T& aInfo, TupleSvc& tupleSvc) {
        return tupleSvc.Register(aInfo);
    }
    bool BulkRegister(const DecayTree& decayTree, TupleSvc&);
    bool BulkRegister(TupleSvc& tupleSvc) {
        return this->BulkRegister(m_decayTree, tupleSvc);
    }

    void Express(const CDCandidate& best, TupleSvc& tupleSvc);

   private:
    DecayTree m_decayTree;
    std::string m_title;
};
static DecayChainSvc gDecayChainSvc;
#endif  // _DECAYMODE_H


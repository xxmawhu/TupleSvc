/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin Ma
#   Email         : xxmawhu@163.com
#   File Name     : DecayChainSvc.h
#   Create Time   : 2019-12-04 14:39
#   Last Modified : 2020-02-06 20:02
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
#include "BesDChain/CDDecayList.h"
class DecayChainSvc {
   public:
    DecayChainSvc() {};
    ~DecayChainSvc() {};
    void SetDecayTree(const DecayTree& decayTree) { m_decayTree = decayTree; }
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
    // CDDecayList::iterator m_BestCandidate;
};
#endif  // _DECAYMODE_H

static DecayChainSvc gDecayChainSvc;

/* ====================================================
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : DecayChainSvc.cpp
#   Create Time   : 2020-02-06 17:46
#   Last Modified : 2020-02-14 09:37
#   Describe      :
#
# ====================================================*/
#include <iostream>
#include <string>
#include "TupleSvc/DecayChainSvc.h"
using std::string;
using std::cout;
using std::endl;
DecayChainSvc::DecayChainSvc() {
    m_title = "";
}

DecayChainSvc::~DecayChainSvc() {
}

int DecayChainSvc::GetCC(const CDCandidate& tag, 
                         const DecayTree& decayTree) {
    if (decayTree.SelfConjugate()) return 0;
    if (decayTree.size() == 1) {
        int pid = abs(decayTree.PID(0));
        vector<int> tmp;
        if (pid == 3122) {
            tmp.push_back(2212 * pid/decayTree.PID(0));
            tmp.push_back(-211 * pid/decayTree.PID(0));
            return GetCC(tag, DecayTree(tmp));
        }
        if (pid == 3112) {
            tmp.push_back(2212 * pid/decayTree.PID(0));
            tmp.push_back(111 * pid/decayTree.PID(0));
            return GetCC(tag, DecayTree(tmp));
        }
        if (pid == 3212) {
            tmp.push_back(3122 * pid/decayTree.PID(0));
            tmp.push_back(22 * pid/decayTree.PID(0));
            return GetCC(tag, DecayTree(tmp));
        }
        if (pid == 3312) {
            tmp.push_back(3122 * pid/decayTree.PID(0));
            tmp.push_back(111 * pid/decayTree.PID(0));
            return GetCC(tag, DecayTree(tmp));
        }
        if (pid == 3312) {
            tmp.push_back(3122 * pid/decayTree.PID(0));
            tmp.push_back(-211 * pid/decayTree.PID(0));
            return GetCC(tag, DecayTree(tmp));
        }
        if (pid == 3334) {
            tmp.push_back(3122 * pid/decayTree.PID(0));
            tmp.push_back(321* pid/decayTree.PID(0));
            return GetCC(tag, DecayTree(tmp));
        }
    } 
    for (int i = 0; i < decayTree.size(); ++i ) {
        if (tag.decay().child(i).charge() * decayTree.PID(i) < 0) {
            return -1;
        } 
        if (tag.decay().child(i).charge() * decayTree.PID(i) > 0) {
            return 1;
        }
    }
}

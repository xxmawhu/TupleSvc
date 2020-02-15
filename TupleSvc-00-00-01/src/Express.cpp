/* ====================================================
# Generate by genExpress.py
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
# ====================================================*/
#include <iostream>
#include <string>
#include "HadronInfo/gHadronInfo.h"
#include "TupleSvc/DecayChainSvc.h"

void DecayChainSvc::Express(const CDCandidate& best, TupleSvc& tupleSvc) {
    std::string name;
    int pid;
    for (int i = 0; i < m_decayTree.size(); ++i) {
        pid = abs(m_decayTree.PID(i));
        name = m_decayTree.GetName(i);
        if (pid == Type::ElectronInfo) {
            gElectronInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gElectronInfo.Feed(best);
            if (m_decayTree.size() > 1)
                gElectronInfo.Feed(best.decay().child(i));
            tupleSvc << gElectronInfo;
            continue;
        }
        if (pid == Type::ShowerInfo) {
            gShowerInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gShowerInfo.Feed(best);
            if (m_decayTree.size() > 1) gShowerInfo.Feed(best.decay().child(i));
            tupleSvc << gShowerInfo;
            continue;
        }
        if (pid == Type::Pi0Info) {
            gPi0Info.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gPi0Info.Feed(best);
            if (m_decayTree.size() > 1) gPi0Info.Feed(best.decay().child(i));
            tupleSvc << gPi0Info;
            continue;
        }
        if (pid == Type::PionInfo) {
            gPionInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gPionInfo.Feed(best);
            if (m_decayTree.size() > 1) gPionInfo.Feed(best.decay().child(i));
            tupleSvc << gPionInfo;
            continue;
        }
        if (pid == Type::EtaInfo) {
            gEtaInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gEtaInfo.Feed(best);
            if (m_decayTree.size() > 1) gEtaInfo.Feed(best.decay().child(i));
            tupleSvc << gEtaInfo;
            continue;
        }
        if (pid == Type::OmegaInfo) {
            gOmegaInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gOmegaInfo.Feed(best);
            if (m_decayTree.size() > 1) gOmegaInfo.Feed(best.decay().child(i));
            tupleSvc << gOmegaInfo;
            continue;
        }
        if (pid == Type::KsInfo) {
            gKsInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gKsInfo.Feed(best);
            if (m_decayTree.size() > 1) gKsInfo.Feed(best.decay().child(i));
            tupleSvc << gKsInfo;
            continue;
        }
        if (pid == Type::KaonInfo) {
            gKaonInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gKaonInfo.Feed(best);
            if (m_decayTree.size() > 1) gKaonInfo.Feed(best.decay().child(i));
            tupleSvc << gKaonInfo;
            continue;
        }
        if (pid == Type::PhiInfo) {
            gPhiInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gPhiInfo.Feed(best);
            if (m_decayTree.size() > 1) gPhiInfo.Feed(best.decay().child(i));
            tupleSvc << gPhiInfo;
            continue;
        }
        if (pid == Type::ProtonInfo) {
            gProtonInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gProtonInfo.Feed(best);
            if (m_decayTree.size() > 1) gProtonInfo.Feed(best.decay().child(i));
            tupleSvc << gProtonInfo;
            continue;
        }
        if (pid == Type::LambdaInfo) {
            gLambdaInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gLambdaInfo.Feed(best);
            if (m_decayTree.size() > 1) gLambdaInfo.Feed(best.decay().child(i));
            tupleSvc << gLambdaInfo;
            continue;
        }
        if (pid == Type::SigmapInfo) {
            gSigmapInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gSigmapInfo.Feed(best);
            if (m_decayTree.size() > 1) gSigmapInfo.Feed(best.decay().child(i));
            tupleSvc << gSigmapInfo;
            continue;
        }
        if (pid == Type::Sigma0Info) {
            gSigma0Info.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gSigma0Info.Feed(best);
            if (m_decayTree.size() > 1) gSigma0Info.Feed(best.decay().child(i));
            tupleSvc << gSigma0Info;
            continue;
        }
        if (pid == Type::XimInfo) {
            gXimInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gXimInfo.Feed(best);
            if (m_decayTree.size() > 1) gXimInfo.Feed(best.decay().child(i));
            tupleSvc << gXimInfo;
            continue;
        }
        if (pid == Type::Xi0Info) {
            gXi0Info.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gXi0Info.Feed(best);
            if (m_decayTree.size() > 1) gXi0Info.Feed(best.decay().child(i));
            tupleSvc << gXi0Info;
            continue;
        }
        if (pid == Type::OmegamInfo) {
            gOmegamInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gOmegamInfo.Feed(best);
            if (m_decayTree.size() > 1) gOmegamInfo.Feed(best.decay().child(i));
            tupleSvc << gOmegamInfo;
            continue;
        }
        if (pid == Type::EtaV3PiInfo) {
            gEtaV3PiInfo.SetName(name);
            if (m_decayTree.size() == 1 && best.decay().children().size() > 1)
                gEtaV3PiInfo.Feed(best);
            if (m_decayTree.size() > 1)
                gEtaV3PiInfo.Feed(best.decay().child(i));
            tupleSvc << gEtaV3PiInfo;
            continue;
        }
    }
    return;
}
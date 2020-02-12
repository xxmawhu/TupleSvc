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
 ///   cout << "m_decayTree.size() = " << m_decayTree.size() << endl;
    for (int i = 0; i < m_decayTree.size(); ++i) {
        pid = abs(m_decayTree.PID(i));
    ///   cout << "i = " << i << endl;
    ///   cout << "pid  = " << pid << endl;
        name = m_decayTree.GetName(i);
    ///    cout << "name  = " << name << endl;
        if (pid == Type::ElectronInfo) {
            gElectronInfo.SetName(name);
            gElectronInfo.Feed(best.decay().child(i));
            tupleSvc << gElectronInfo;
            continue;
        }
        if (pid == Type::ShowerInfo) {
            gShowerInfo.SetName(name);
            gShowerInfo.Feed(best.decay().child(i));
            tupleSvc << gShowerInfo;
            continue;
        }
        if (pid == Type::Pi0Info) {
            gPi0Info.SetName(name);
            gPi0Info.Feed(best.decay().child(i));
            tupleSvc << gPi0Info;
            continue;
        }
        if (pid == Type::PionInfo) {
            gPionInfo.SetName(name);
            gPionInfo.Feed(best.decay().child(i));
            tupleSvc << gPionInfo;
            continue;
        }
        if (pid == Type::EtaInfo) {
            gEtaInfo.SetName(name);
            gEtaInfo.Feed(best.decay().child(i));
            tupleSvc << gEtaInfo;
            continue;
        }
        if (pid == Type::OmegaInfo) {
            gOmegaInfo.SetName(name);
            gOmegaInfo.Feed(best.decay().child(i));
            tupleSvc << gOmegaInfo;
            continue;
        }
        if (pid == Type::KsInfo) {
            gKsInfo.SetName(name);
            gKsInfo.Feed(best.decay().child(i));
            tupleSvc << gKsInfo;
            continue;
        }
        if (pid == Type::KaonInfo) {
            gKaonInfo.SetName(name);
            gKaonInfo.Feed(best.decay().child(i));
            tupleSvc << gKaonInfo;
            continue;
        }
        if (pid == Type::PhiInfo) {
            gPhiInfo.SetName(name);
            gPhiInfo.Feed(best.decay().child(i));
            tupleSvc << gPhiInfo;
            continue;
        }
        if (pid == Type::ProtonInfo) {
            gProtonInfo.SetName(name);
            gProtonInfo.Feed(best.decay().child(i));
            tupleSvc << gProtonInfo;
            continue;
        }
        if (pid == Type::LambdaInfo) {
            gLambdaInfo.SetName(name);
            gLambdaInfo.Feed(best.decay().child(i));
            tupleSvc << gLambdaInfo;
            continue;
        }
        if (pid == Type::SigmapInfo) {
            gSigmapInfo.SetName(name);
            gSigmapInfo.Feed(best.decay().child(i));
            tupleSvc << gSigmapInfo;
            continue;
        }
        if (pid == Type::Sigma0Info) {
            gSigma0Info.SetName(name);
            gSigma0Info.Feed(best.decay().child(i));
            tupleSvc << gSigma0Info;
            continue;
        }
        if (pid == Type::XimInfo) {
            gXimInfo.SetName(name);
            gXimInfo.Feed(best.decay().child(i));
            tupleSvc << gXimInfo;
            continue;
        }
        if (pid == Type::Xi0Info) {
            gXi0Info.SetName(name);
            gXi0Info.Feed(best.decay().child(i));
            tupleSvc << gXi0Info;
            continue;
        }
        if (pid == Type::OmegamInfo) {
            gOmegamInfo.SetName(name);
            gOmegamInfo.Feed(best.decay().child(i));
            tupleSvc << gOmegamInfo;
            continue;
        }
        if (pid == Type::EtaV3PiInfo) {
            gEtaV3PiInfo.SetName(name);
            gEtaV3PiInfo.Feed(best.decay().child(i));
            tupleSvc << gEtaV3PiInfo;
            continue;
        }
    }
    return;
}

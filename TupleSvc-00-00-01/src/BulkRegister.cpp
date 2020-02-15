/* ====================================================
# Generate by genBulkRegister.py
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
# ====================================================*/
#include <iostream>
#include <string>
#include "HadronInfo/gHadronInfo.h"
#include "TupleSvc/DecayChainSvc.h"

bool DecayChainSvc::BulkRegister(const DecayTree& decayTree,
                                 TupleSvc& tupleSvc) {
    bool status = true;
    std::string name;
    int pid;
    for (int i = 0; i < decayTree.size(); ++i) {
        pid = abs(decayTree.PID(i));
        name = m_title + decayTree.GetName(i);
        if (pid == Type::ElectronInfo) {
            gElectronInfo.SetName(name);
            status = status && SubRegister(gElectronInfo, tupleSvc);
            continue;
        }
        if (pid == Type::ShowerInfo) {
            gShowerInfo.SetName(name);
            status = status && SubRegister(gShowerInfo, tupleSvc);
            continue;
        }
        if (pid == Type::Pi0Info) {
            gPi0Info.SetName(name);
            status = status && SubRegister(gPi0Info, tupleSvc);
            continue;
        }
        if (pid == Type::PionInfo) {
            gPionInfo.SetName(name);
            status = status && SubRegister(gPionInfo, tupleSvc);
            continue;
        }
        if (pid == Type::EtaInfo) {
            gEtaInfo.SetName(name);
            status = status && SubRegister(gEtaInfo, tupleSvc);
            continue;
        }
        if (pid == Type::OmegaInfo) {
            gOmegaInfo.SetName(name);
            status = status && SubRegister(gOmegaInfo, tupleSvc);
            continue;
        }
        if (pid == Type::KsInfo) {
            gKsInfo.SetName(name);
            status = status && SubRegister(gKsInfo, tupleSvc);
            continue;
        }
        if (pid == Type::KaonInfo) {
            gKaonInfo.SetName(name);
            status = status && SubRegister(gKaonInfo, tupleSvc);
            continue;
        }
        if (pid == Type::PhiInfo) {
            gPhiInfo.SetName(name);
            status = status && SubRegister(gPhiInfo, tupleSvc);
            continue;
        }
        if (pid == Type::ProtonInfo) {
            gProtonInfo.SetName(name);
            status = status && SubRegister(gProtonInfo, tupleSvc);
            continue;
        }
        if (pid == Type::LambdaInfo) {
            gLambdaInfo.SetName(name);
            status = status && SubRegister(gLambdaInfo, tupleSvc);
            continue;
        }
        if (pid == Type::SigmapInfo) {
            gSigmapInfo.SetName(name);
            status = status && SubRegister(gSigmapInfo, tupleSvc);
            continue;
        }
        if (pid == Type::Sigma0Info) {
            gSigma0Info.SetName(name);
            status = status && SubRegister(gSigma0Info, tupleSvc);
            continue;
        }
        if (pid == Type::XimInfo) {
            gXimInfo.SetName(name);
            status = status && SubRegister(gXimInfo, tupleSvc);
            continue;
        }
        if (pid == Type::Xi0Info) {
            gXi0Info.SetName(name);
            status = status && SubRegister(gXi0Info, tupleSvc);
            continue;
        }
        if (pid == Type::OmegamInfo) {
            gOmegamInfo.SetName(name);
            status = status && SubRegister(gOmegamInfo, tupleSvc);
            continue;
        }
        if (pid == Type::EtaV3PiInfo) {
            gEtaV3PiInfo.SetName(name);
            status = status && SubRegister(gEtaV3PiInfo, tupleSvc);
            continue;
        }
    }
    return status;
}
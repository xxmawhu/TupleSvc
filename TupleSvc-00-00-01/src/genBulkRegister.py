#!/usr/bin/env python3
# encoding: utf-8
# coding style: pep8
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : genBulkRegister.py
#   Create Time   : 2020-02-06 19:34
#   Last Modified : 2020-02-07 13:01
#   Describe      :
#
# ====================================================*/

import os
include = """/* ====================================================
# Generate by genBulkRegister.py
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
# ====================================================*/
#include <iostream>
#include <string>
#include "HadronInfo/gHadronInfo.h"
#include "TupleSvc/DecayChainSvc.h"

bool DecayChainSvc::BulkRegister(const DecayTree& decayTree, TupleSvc& tupleSvc) {
    bool status = true;
    std::string name;
    int pid;
    for(int i=0; i< decayTree.size(); ++i){
        pid = abs(decayTree.PID(i));
        name =  m_title + decayTree.GetName(i);
"""


allInfo= [  "ElectronInfo" ,
        "ShowerInfo",
        "Pi0Info",
        "PionInfo",
        "EtaInfo",
        "OmegaInfo",
        "KsInfo",
        "KaonInfo",
        "PhiInfo",
        "ProtonInfo",
        "LambdaInfo",
        "SigmapInfo",
        "Sigma0Info",
        "XimInfo",
        "Xi0Info",
        "OmegamInfo",
        "EtaV3PiInfo",
        ]


def gen(info='KsInfo'):
    s=""
    s += "if (pid == Type::%s){"%(info)
    s += "g{}.SetName(name);".format(info)
    s += 'status = status && SubRegister(g{}, tupleSvc);'.format(info)
    s += 'continue;}\n'
    return s


def main(include):
    f=open("BulkRegister.cpp", 'w')
    for i in allInfo:
        include += gen(i)
    include += "} return status; }"
    f.write(include)   
    f.close()

if __name__ == "__main__":
    main(include)
    os.system("clang-format -i BulkRegister.cpp")

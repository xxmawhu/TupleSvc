#!/usr/bin/env python3
# encoding: utf-8
# coding style: pep8
#   Copyright (C)2020 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : genExpress.py
#   Create Time   : 2020-02-06 19:34
#   Last Modified : 2020-02-07 15:35
#   Describe      :
#
# ====================================================*/
import os
from allInfo import *
include = """/* ====================================================
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
    for(int i=0; i< m_decayTree.size(); ++i){
        pid = abs(m_decayTree.PID(i));
        name =  m_decayTree.GetName(i);
"""

def gen(info='KsInfo'):
    s=""
    s += "if (pid == Type::%s){"%(info)
    s += "g{}.SetName(name);".format(info)
    s += "g{}.Feed(best.decay().child(i));".format(info)
    s += 'tupleSvc << g{};'.format(info)
    s += 'continue;}\n'
    return s


def main(include, name="BulkRegister.cpp"):
    f=open(name, 'w')
    for i in allInfo:
        include += gen(i)
    include += "} return; }"
    f.write(include)   
    f.close()
    os.system("clang-format -i {}".format(name))

if __name__ == "__main__":
    main(include, "Express.cpp")

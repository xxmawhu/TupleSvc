/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : TupleSvc.h
#   Create Time   : 2019-12-04 14:09
#   Last Modified : 2019-12-04 14:09
#   Describe      :
#
# ====================================================*/
#ifndef TUPLESVC_H
#define TUPLESVC_H
#include "GaudiKernel/NTuple.h"
#include "TupleSvc/DecayMode.h"
#include <map>
#include <string>
using std::string;
class TupleSvc {
   public:
    TupleSvc();
    ~TupleSvc();
    // define only one double type Item, such as
    //   `NTuple::Item<double> m_doubleInfo[100]` in the head file,
    // then use this address to store and write all `double` information,
    // such as `mass`, `chisq`, `decay length`
    // the default length is `100`
    // It seems that only `double` is possible, so drop the template
    // template <class TYPE>
    SetItemAddress(std::string type_name, NTuple::Item<double>*,
                   int max_length = 100);
    // template <class TYPE>
    SetArrayAddress(std::string type_name, NTuple::Array<double>*,
                    int max_length = 100);
    SetDecayMode(const DecayMode&);
    InitTuple(NTuple:Tuple* tp);

   private:
    map<std::string, int> m_ItemIndex, m_ArrayIndex;
    InitItemIndex();
    InitArrayIndex();
    DecayMode m_decayMode;
};
#endif

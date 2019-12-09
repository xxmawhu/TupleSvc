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
#include "CLHEP/Vector/LorentzVector.h"
#include "TupleSvc/DecayMode.h"
#include <map>
#include <string>

using std::string;
using CLHEP::HepLorentzVector;
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
    void SetItemAddress(const string& type_name, NTuple::Item<double>*,
                        const int& max_length = 100);
    void SetItemAddress(const string& type_name, NTuple::Item<int>*,
                        const int& max_length = 100);
    // template <class TYPE>
    void SetArrayAddress(const string& type_name, NTuple::Array<double>*,
                         const int& max_length = 100);
    void SetDecayMode(const DecayMode&);
    bool InitTuple(NTuple::Tuple* tp);
    void Fill(const string& particle_name, const string& observable,
              const double& value);
    void Fill(const string& particle_name, const string& observable,
              const int& value);
    void Fill(const string& particle_name, const string& observable,
              const HepLorentzVector& p4);

    void Fill(const int& particle_index, const string& observable,
              const double& value);
    void Fill(const int& particle_index, const string& observable,
              const int& value);
    void Fill(const int& particle_index, const string& observable,
              const HepLorentzVector& p4);

   private:
    Tuple::Item<int>* m_intItemItr;
    Tuple::Item<double>* m_doubleItemItr;
    Tuple::Array<double>* m_arrayItemItr;
    int m_intLength, m_doubleLength, m_arrayLength;
    map<std::string, int> m_ItemIndex, m_ArrayIndex;
    DecayMode m_decayMode;
    void InitItemIndex();
    void InitArrayIndex();
};
#endif

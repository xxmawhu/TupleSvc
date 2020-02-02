/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : TupleSvc.h
#   Create Time   : 2019-12-04 14:09
#   Last Modified : 2019-12-09 13:53
#   Describe      :
#
# ====================================================*/
#ifndef TUPLESVC_H
#define TUPLESVC_H
#include "GaudiKernel/NTuple.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "HadronInfo/AvailableInfo.h"
#include "TupleSvc/DecayTree.h"
#include <map>
#include <string>
using CLHEP::HepLorentzVector;
using std::string;
using std::map;
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
    void SetDecayTree(const DecayTree&);
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
    void SaveInfo(const CDCandidate& signal);
    template <class ParticleInfo>
    void SaveInfo(ParticleInfo particleinfo, const int&i){
        vector<string> intInf = particleinfo.GetIntInf(); 
        vector<string> doubleInf = particleinfo.GetDoubleInf(); 
        vector<string> arrayInf = particleinfo.GetP4Inf(); 
        vector<string>::const_iterator itr = doubleInf.begin();
        for(; itr != doubleInf.end(); itr++){
            Fill(i, *itr, particleinfo.GetDoubleInfo(*itr));
        }
        for(itr=arrayInf.begin(); itr != arrayInf.end(); itr++){
            Fill(i, *itr, particleinfo.GetLorentzVector(*itr));
        }
    }

   private:
    NTuple::Item<int>* m_intItemItr;
    NTuple::Item<double>* m_doubleItemItr;
    NTuple::Array<double>* m_arrayItemItr;
    int m_intLength, m_doubleLength, m_arrayLength;
    map<std::string, int> m_doubleItemIndex, m_ArrayIndex, m_intItemIndex;
    DecayTree m_decayMode;
    void InitItemIndex();
    // void InitArrayIndex();
    const AvailableInfo getAvialInfo(const int&);
};
#endif

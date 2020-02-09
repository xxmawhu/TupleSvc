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
#include "TupleSvc/DecayTree.h"
#include <map>
#include <string>
using CLHEP::HepLorentzVector;
using std::string;
using std::map;
class TupleSvc {
   public:
    // define only one double type Item, such as
    //   `NTuple::Item<double> m_doubleInfo[100]` in the head file,
    // then use this address to store and write all `double` information,
    // such as `mass`, `chisq`, `decay length`
    // the default length is `100`
    // It seems that only `double` is possible, so drop the template
    TupleSvc(int maxI = 20, int maxD = 200, int maxVi = 10, int maxVd = 20);
    ~TupleSvc();
    bool BindTuple(NTuple::Tuple* tp);
    void Write();

    template <class T>
    bool Register(T&);
    // over load the operator <<
    // usage: tupleSvc << hadronInfo
    // function: save all aviable information to the tupleSvc
    template <class T>
    TupleSvc& operator<<(T& y);

   private:
    NTuple::Tuple* m_tp;
    NTuple::Item<int>* I_Ptr;
    NTuple::Item<double>* D_Ptr;
    NTuple::Array<double>* Vd_Ptr;
    NTuple::Array<int>* Vi_Ptr;
    int m_MaxSizeI, m_MaxSizeD, m_MaxSizeVd, m_MaxSizeVi;
    map<std::string, int> i_D, i_Vd, i_I, i_Vi;
};

template <class InfoT>
bool TupleSvc::Register(InfoT& gInfo) {
    if (m_tp == NULL) {
        return false;
    }
    // store the int type variable
    std::vector<std::string> tmpAllInfo = gInfo.GetType("int");
    std::vector<std::string>::iterator itr;
    int intP = i_I.size(), VintP = i_Vi.size();
    // first deal with the un-index item
    for (itr = tmpAllInfo.begin(); itr != tmpAllInfo.end(); ++itr) {
        if (gInfo.GetIndex(*itr) != std::string("NULL")) {
            continue;
        }
        if (i_I.size() >= m_MaxSizeI) {
            std::cout << "Error, the maximum Item<int> size is " << m_MaxSizeI
                      << ", but now we are adding the " << m_MaxSizeI + 1
                      << "-th Item" << std::endl;
            return false;
        }
        m_tp->addItem(*itr, I_Ptr[intP]);
        i_I.insert(std::make_pair(*itr, intP));
        intP += 1;
    }
    // add the indexTerm
    for (itr = tmpAllInfo.begin(); itr != tmpAllInfo.end(); ++itr) {
        if (gInfo.GetIndex(*itr) == std::string("NULL")) {
            continue;
        }
        const string& index = gInfo.GetIndex(*itr);
        if (i_I.find(index) == i_I.end()) {
            std::cout << "Error, When add item " << *itr
                      << ", we are told need one  Item<int> " << index
                      << "but, we can't find it now!" << std::endl;
            return false;
        }
        int i = i_I[index];
        if (i_Vi.size() >= m_MaxSizeVi) {
            std::cout << "Error, the maximum Array<double> size is "
                      << m_MaxSizeVi << ", but now we are adding the "
                      << m_MaxSizeVi + 1 << "-th Item" << std::endl;
            return false;
        }
        m_tp->addIndexedItem(*itr, I_Ptr[i], Vi_Ptr[VintP]);
        i_Vi.insert(std::make_pair(*itr, VintP));
        VintP += 1;
    }
    // add double type
    tmpAllInfo = gInfo.GetType("double");
    int dI = i_D.size(), dVI = i_Vd.size();
    for (itr = tmpAllInfo.begin(); itr != tmpAllInfo.end(); ++itr) {
        const string& index = gInfo.GetIndex(*itr);
        int length = gInfo.GetLength(*itr);
        if (length == 1) {
            if (i_D.size() >= m_MaxSizeD) {
                std::cout << "Error, the maximum Item<double> size is "
                          << m_MaxSizeD << ", but now we are adding the "
                          << m_MaxSizeD + 1 << "-th Item" << std::endl;
                return false;
            }
            m_tp->addItem(*itr, D_Ptr[dI]);
            i_D.insert(std::make_pair(*itr, dI));
            dI += 1;
            continue;
        }
        if (index == "NULL") {
            if (i_Vd.size() >= m_MaxSizeVd) {
                std::cout << "Error, the maximum Array<double> size is "
                          << m_MaxSizeVd << ", but now we are adding the "
                          << m_MaxSizeVd + 1 << "-th Item" << std::endl;
                return false;
            }
            m_tp->addItem(*itr, length, Vd_Ptr[dVI]);
            i_Vd.insert(std::make_pair(*itr, dVI));
            dVI += 1;
            continue;
        }
        // index info
        if (i_I.find(index) == i_I.end()) {
            std::cout << "Error, When add item " << *itr
                      << ", we are told need one  Item<int> " << index
                      << "but, we can't find it now!" << std::endl;
            return false;
        }
        if (i_Vd.size() >= m_MaxSizeVd) {
            std::cout << "Error, the maximum Array<double> size is "
                      << m_MaxSizeVd << ", but now we are adding the "
                      << m_MaxSizeVd + 1 << "-th Item" << std::endl;
            return false;
        }
        int i = i_I[index];
        m_tp->addIndexedItem(*itr, I_Ptr[i], Vd_Ptr[dVI]);
        i_Vd.insert(std::make_pair(*itr, dVI));
        dVI += 1;
    }
    // add LorentzVector
    tmpAllInfo = gInfo.GetType("double");
    dVI = i_Vd.size();
    for (itr = tmpAllInfo.begin(); itr != tmpAllInfo.end(); ++itr) {
        if (i_Vd.size() >= m_MaxSizeVd) {
            std::cout << "Error, the maximum Array<double> size is "
                      << m_MaxSizeVd << ", but now we are adding the "
                      << m_MaxSizeVd + 1 << "-th Item" << std::endl;
            return false;
        }
        m_tp->addItem(*itr, 4, Vd_Ptr[dVI]);
        i_Vd.insert(std::make_pair(*itr, dVI));
        dVI += 1;
    }
    // done
    // check the length
}
template <class InfoT>
TupleSvc& TupleSvc::operator<<(InfoT& gInfo) {
    // double
    vector<string> allInfo = gInfo.GetType("double");
    vector<string>::iterator itr;
    int index, length, iInfo;
    double tmpInfo;
    vector<double> Vd;
    string gIndex;
    int i;
    for (itr = allInfo.begin(); itr != allInfo.end(); itr++) {
        int length = gInfo.GetLength(*itr);
        string gIndex = gInfo.GetIndex(*itr);
        // check the index, if the index exist, the assign index first!
        if (gIndex != "NULL") {
            gInfo.GetInfoI(gIndex, i);
            I_Ptr[i_I[gIndex]] = i;
        }
        // check the length, if the length is 1, then choose D_Ptr,
        // and i_D to store the target value
        // if not, choose the assgin to a list
        if (length == 1) {
            // check exist
            if (i_D.find(*itr) == i_D.end()) {
                cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                     << "\". " << *itr << "()"
                     << ", you should Register it first at Initial()" << endl;
                continue;
            }
            index = i_D[*itr];
            gInfo.GetInfoD(*itr, tmpInfo);
            this->D_Ptr[index] = tmpInfo;
        } else {
            // check exist
            if (i_Vd.find(*itr) == i_Vd.end()) {
                cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                     << "\". " << *itr << "()"
                     << ", you should Register it first at Initial()" << endl;
                continue;
            }
            index = i_Vd[*itr];
            gInfo.GetInfoVd(*itr, Vd);
            for (int i = 0; i < Vd.size(); ++i) {
                this->Vd_Ptr[index][i] = Vd[i];
            }
        }
    }
    // int
    vector<int> Vi;
    allInfo = gInfo.GetType("int");
    for (itr = allInfo.begin(); itr != allInfo.end(); ++itr) {
        gIndex = gInfo.GetIndex(*itr);
        if (gIndex != "NULL") {
            gInfo.GetInfoI(gIndex, i);
            I_Ptr[i_I[gIndex]] = i;
        }
        length = gInfo.GetLength(*itr);
        if (length == 1) {
            // check exist
            if (i_I.find(*itr) == i_I.end()) {
                cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                     << "\". " << *itr << "()"
                     << ", you should Register it first at Initial()" << endl;
                continue;
            }
            index = i_I[*itr];
            gInfo.GetInfoI(*itr, i);
            this->I_Ptr[index] = i;
            // check exist
        } else {
            if (i_I.find(*itr) == i_I.end()) {
                cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                     << "\". " << *itr << "()"
                     << ", you may be need to Register it first at Initial()"
                     << endl << ", or check the type: <int> or <double>"
                     << endl;
                continue;
            }
            index = i_Vi[*itr];
            gInfo.GetInfoVi(*itr, Vi);
            for (int i = 0; i < Vi.size(); ++i) {
                this->Vi_Ptr[index][i] = Vi[i];
            }
        }
    }
    // HepLorentzVector
    allInfo = gInfo.GetType("HepLorentzVector");
    HepLorentzVector p4;
    for (itr = allInfo.begin(); itr != allInfo.end(); itr++) {
        if (i_Vd.find(*itr) == i_Vd.end()) {
            cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                 << "\". " << *itr << "()"
                 << ", you should Register it first at Initial()" << endl;
            continue;
        }
        gInfo.GetInfoH(*itr, p4);
        index = i_Vd[*itr];
        for (int i = 0; i < 4; ++i) {
            this->Vd_Ptr[index][i] = p4[i];
        }
    }
    return *this;
}

static TupleSvc gTupleSvc;
#endif

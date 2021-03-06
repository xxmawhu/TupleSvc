/* ====================================================
#   Copyright (C)2019 All rights reserved.
#
#   Author        : Xin-Xin MA
#   Email         : xxmawhu@163.com
#   File Name     : TupleSvc.h
#   Create Time   : 2019-12-04 14:09
#   Last Modified : 2019-12-09 13:53
#   Describe      :
#Debug tip:

* replace "///" with "///"
  %s%///%///
* recovery
  %s%///%///
# ====================================================*/
#ifndef TUPLESVC_H
#define TUPLESVC_H
#include "GaudiKernel/NTuple.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "TupleSvc/DecayTree.h"
#include <map>
#include <string>
using CLHEP::HepLorentzVector;
using std::cout;
using std::endl;
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
    NTuple::Item<int> *I_Ptr;
    NTuple::Item<double> *D_Ptr;
    NTuple::Array<double> *Vd_Ptr;
    NTuple::Array<int> *Vi_Ptr;
    int m_MaxSizeI, m_MaxSizeD, m_MaxSizeVd, m_MaxSizeVi;
    map<std::string, int> i_D, i_Vd, i_I, i_Vi;
};

template <class InfoT>
bool TupleSvc::Register(InfoT& gInfo) {
    if (!m_tp) {
        std::cout << "Error in <TupleSvc::Register>: "
            << "Please BindTuple a tuple first!"
            << std::endl;
        return false;
    }
    StatusCode status;
    std::string infoname = gInfo.GetName();
    // store the int type variable
    std::cout << "Info in <TupleSvc::Register>: "; 
    std::cout  << "Input is " << gInfo.GetName()<< std::endl;
    std::vector<std::string> tmpAllInfo = gInfo.GetType("int");
    std::vector<std::string>::iterator itr;
    int intP = i_I.size(), VintP = i_Vi.size();

    // first deal with the un-index item
    for (itr = tmpAllInfo.begin(); itr != tmpAllInfo.end(); ++itr) {
        // std::cout << "Info in <TupleSvc::Register>: " 
        //     << "name = " << *itr << std::endl;
        const string& index = gInfo.GetIndex(*itr);
        //  std::cout << "Info in <TupleSvc::Register>: " 
        //      << "index = " << index << std::endl;
        int length = gInfo.GetLength(*itr);
        const vector<string>& allIndex = gInfo.GetAllIndex();
        //   std::cout << "allIndex.size() = " <<allIndex.size() << std::endl;
        //  add Item without index,
        if (index == "NULL" && length == 1) {
            if (i_I.size() >= m_MaxSizeI) {
                std::cout << "Error, the maximum Item<int> size is " << m_MaxSizeI
                    << ", but now we are adding the " << m_MaxSizeI + 1
                    << "-th Item" << std::endl;
                return false;
            }
            //  std::cout << "Info in <TupleSvc::Register>: " 
            //      << ", intP = " << intP << std::endl;
            if (std::find(allIndex.begin(), allIndex.end(), 
                        *itr) == allIndex.end()) {
                status = m_tp->addItem(*itr+infoname, I_Ptr[intP]);
                std::cout << "\t" <<"tuple->addItem(\""
                    << *itr +infoname <<"\", I_Ptr["
                    << intP << "])" << std::endl;
                if (!status) {
                    return false;
                }
                i_I.insert(std::make_pair((*itr)+infoname, intP));
                intP += 1;
            } else {
                // std::cout << "this is an index item!!!" << std::endl;
                // std::cout << "set the range [0, 100]" << std::endl;
                status = m_tp->addItem(*itr+infoname, I_Ptr[intP], 0, 100);
                std::cout << "\ttuple->addItem(\""
                    << *itr + infoname << ", I_Ptr["
                    << intP << "], 0, 100)" << std::endl;
                if (!status) {
                    return false;
                }
                i_I.insert(std::make_pair((*itr)+infoname, intP));
                intP += 1;
            }
            continue;
        }
        // fixed size array
        if (index == "NULL" && length > 1) {
            if (i_Vi.size() >= m_MaxSizeVi) {
                std::cout << "Error, the maximum Array<double> size is "
                    << m_MaxSizeVi << ", but now we are adding the "
                    << m_MaxSizeVi + 1 << "-th Item" << std::endl;
                return false;
            }
            status = m_tp->addItem(*itr+infoname, length, Vi_Ptr[VintP]);
            if (!status) {
                return false;
            }
            std::cout << "\t" << "tuple->addIndexedItem(\""
                << *itr+infoname << ", " <<
                length << ", Vi_Ptr[" << VintP << "])" << std::endl;
            i_Vi.insert(std::make_pair((*itr)+infoname, VintP));
            VintP += 1;
            continue;
        }
        // indexed array
        if (index != "NULL") {
            if (i_I.find(index+infoname) == i_I.end()) {
                std::cout << "Error, When add item " << *itr
                    << ", we are told need one  Item<int> " << index
                    << " but, we can't find it now!" << std::endl;
                return false;
            }
            if (i_Vi.size() >= m_MaxSizeVi) {
                std::cout << "Error, the maximum Array<double> size is "
                    << m_MaxSizeVi << ", but now we are adding the "
                    << m_MaxSizeVi + 1 << "-th Item" << std::endl;
                return false;
            }
            int i = i_I.find(index+infoname)->second;
            // std::cout << "Info in <TupleSvc::Register>: " 
            //     << " i = " << i << ", VintP = " << VintP << std::endl;
            m_tp->addIndexedItem(*itr+infoname, I_Ptr[i], Vi_Ptr[VintP]);
            std::cout << "\t" << "tuple->addIndexedItem(\""
                << *itr+infoname << ", I_Ptr[" <<
                i << "], Vi_Ptr[" << VintP << "])" << std::endl;
            i_Vi.insert(std::make_pair((*itr)+infoname, VintP));
            VintP += 1;
            continue;
        }
    }
    // add double type
    tmpAllInfo = gInfo.GetType("double");
    int dI = i_D.size(), dVI = i_Vd.size();
    for (itr = tmpAllInfo.begin(); itr != tmpAllInfo.end(); ++itr) {
        const string& index = gInfo.GetIndex(*itr);
        int length = gInfo.GetLength(*itr);
        // std::cout << "Info in <TupleSvc::Register>: "
        //     << "name = " << *itr << std::endl;
        // std::cout << "Info in <TupleSvc::Register>: "
        //    << "length = " << length << std::endl; 
        if (index == "NULL" && length == 1) {
            if (i_D.size() >= m_MaxSizeD) {
                std::cout << "Error, the maximum Item<double> size is "
                    << m_MaxSizeD << ", but now we are adding the "
                    << m_MaxSizeD + 1 << "-th Item" << std::endl;
                return false;
            }
            // std::cout << "Info in <TupleSvc::Register>: "
            //       << "dI =   " << dI << std::endl;
            // cout << "temp Item<double> = " << (*D_Ptr) << std::endl;
            status = m_tp->addItem((*itr)+infoname, D_Ptr[dI]);
            std::cout << "\ttuple->addItem(\""
                <<(*itr)+infoname << ", D_Ptr[" 
                << dI << "])" << std::endl;
            if (!status) {
                std::cout <<"Error in <TupleSvc::Register>: "
                    << "Can't addItem " << *itr << std::endl;
                return false;
            }
            //   std::cout << gInfo.GetName() <<  " addItem "
            //       << *itr << " double " << " index = " << dI 
            //       << std::endl;
            i_D.insert(std::make_pair((*itr)+infoname, dI));
            dI += 1;
            continue;
        }
        // fixed size array
        if (index == "NULL" && length > 1) {
            if (i_Vd.size() >= m_MaxSizeVd) {
                std::cout << "Error, the maximum Array<double> size is "
                    << m_MaxSizeVd << ", but now we are adding the "
                    << m_MaxSizeVd + 1 << "-th Item" << std::endl;
                return false;
            }
            m_tp->addItem((*itr)+infoname, length, Vd_Ptr[dVI]);
            std::cout <<"\ttuple->addItem(\""
                << (*itr)+infoname << "\"," << length 
                << ", Vd_Ptr[" << dVI << "]) " << std::endl;
            //   std::cout << gInfo.GetName() <<  " addItem "
            //       << *itr << " Array<double>, length = "  << length
            //       << " index = " << dVI << std::endl;
            i_Vd.insert(std::make_pair((*itr)+infoname, dVI));
            dVI += 1;
            continue;
        }
        // indexed array
        if (index != "NULL") {
            if (i_I.find(index + infoname) == i_I.end()) {
                std::cout << "Error, When add item " << *itr
                    << ", we are told need one  Item<int> " << index
                    << " but, we can't find it now!" << std::endl;
                return false;
            }
            if (i_Vd.size() >= m_MaxSizeVd) {
                std::cout << "Error, the maximum Array<double> size is "
                    << m_MaxSizeVd << ", but now we are adding the "
                    << m_MaxSizeVd + 1 << "-th Item" << std::endl;
                return false;
            }
            int i = i_I[index+infoname];
            m_tp->addIndexedItem((*itr)+infoname, I_Ptr[i], Vd_Ptr[dVI]);
            std::cout << "\ttuple->addIndexedItem(\""
                << (*itr)+infoname << ", "
                << index << ", Vd_Ptr[" << dVI << "])" << std::endl;
            //  std::cout << gInfo.GetName() <<  " addIndexedItem"
            //          << *itr << " Array<double> "  
            //          << "length = " << index 
            //          << " index = " << dVI 
            //          << std::endl;
            i_Vd.insert(std::make_pair((*itr)+infoname, dVI));
            dVI += 1;
            continue;
        }
    }
    // add LorentzVector
    tmpAllInfo = gInfo.GetType("HepLorentzVector");
    dVI = i_Vd.size();
    //        std::cout << " index = " << dVI << std::endl;

    for (itr = tmpAllInfo.begin(); itr != tmpAllInfo.end(); ++itr) {
        //  std::cout << "[Info] process HepLorentzVector Add Item for " 
        //      << *itr << std::endl
        //     << " length = " << gInfo.GetLength(*itr); 
        //      std::cout << " index = " << dVI << std::endl;
        if (i_Vd.size() >= m_MaxSizeVd) {
            std::cout << "Error, the maximum Array<double> size is "
                << m_MaxSizeVd << ", but now we are adding the "
                << m_MaxSizeVd + 1 << "-th Item" << std::endl;
            return false;
        }
        m_tp->addItem((*itr)+infoname, 4, Vd_Ptr[dVI]);
        std::cout<< "\ttuple->addItem(\"" 
            << (*itr)+infoname <<"\", 4, Vd_Ptr["
            <<dVI<<"])" << std::endl;
        //   std::cout << " type = Array<double> "
        //       << std::endl;
        i_Vd.insert(std::make_pair((*itr)+infoname, dVI));
        dVI += 1;
    }
    // done
    // check the length
}


template <class InfoT>
TupleSvc& TupleSvc::operator<<(InfoT& gInfo) {
    // double
    string infoname = gInfo.GetName();
    /// cout << "Info in TupleSvc::operator<< infoname=" << infoname << endl;
    vector<string> allInfo = gInfo.GetType("double");
    vector<string>::iterator itr;
    int index, length, iInfo;
    double tmpInfo;
    vector<double> Vd;
    string gIndex;
    int i;
    ///  cout << "Info in TupleSvc::operator<< double" << endl;
    for (itr = allInfo.begin(); itr != allInfo.end(); itr++) {
        int length = gInfo.GetLength(*itr);
        string gIndex = gInfo.GetIndex(*itr);
        ///  cout << "in TupleSvc::operator<<: name = " << *itr << endl;
        // check the index, if the index exist, the assign index first!
        // if (gIndex != "NULL") {
        //     gInfo.GetInfoI(gIndex, i);
        //     I_Ptr[i_I[gIndex]] = i;
        // }
        // check the length, if the length is 1, then choose D_Ptr,
        // and i_D to store the target value
        // if not, choose the assgin to a list
        if (length == 1 && gIndex == "NULL") {
            // check exist
            /// cout << "info in <TupleSvc::operator<< double>:"; 
            /// cout << " name  = " << *itr << endl;
            if (i_D.find((*itr) + infoname) == i_D.end()) {
                cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                     << "\". " << *itr << "()"
                     << ", you should Register it first at Initial()" << endl;
                continue;
            }
            index = i_D[(*itr) + infoname];
            gInfo.GetInfoD(*itr, tmpInfo);
            /// cout << "Info: value = " << tmpInfo << endl;
            D_Ptr[index] = tmpInfo;
            /// cout <<"D_Ptr[" << index << "] = " << tmpInfo << endl;
        } else {
            // check exist
            if (i_Vd.find((*itr)+infoname) == i_Vd.end()) {
                cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                     << "\". " << *itr << "()"
                     << ", you should Register it first at Initial()" << endl;
                continue;
            }
            index = i_Vd[(*itr)+infoname];
            gInfo.GetInfoVd(*itr, Vd);
            for (int i = 0; i < Vd.size(); ++i) {
                this->Vd_Ptr[index][i] = Vd[i];
            }
        }
    }
    // int
    vector<int> Vi;
    allInfo = gInfo.GetType("int");
    /// cout << "Info in TupleSvc::operator<< int" << endl;
    for (itr = allInfo.begin(); itr != allInfo.end(); ++itr) {
        gIndex = gInfo.GetIndex(*itr);
        length = gInfo.GetLength(*itr);
        /// cout << "info in <TupleSvc::operator<<int >:" ; 
        /// cout << " name  = " << *itr << endl;
        /// cout << "info in <TupleSvc::operator<<int >:";
        /// cout << " length  = " << length << endl;
        // Item without index
        if (length == 1 && gIndex == "NULL") {
            // check exist
            if (i_I.find((*itr)+infoname) == i_I.end()) {
                cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                     << "\". " << *itr << "()"
                     << ", you should Register it first at Initial()" << endl;
                continue;
            }
            index = i_I[(*itr)+infoname];
            gInfo.GetInfoI(*itr, i);
            ///  cout << "\tI_Ptr["<< index << " ] = " << i << endl;
            I_Ptr[index] = i;
            continue;
        }
        // array wiout index with fixed size 
        if (length > 1 || gIndex != "NULL") {
            // check exist
            if (i_Vi.find((*itr)+infoname) == i_Vi.end()) {
                cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                     << "\". " << (*itr) + infoname << "()"
                     << ", you may be need to Register it first at Initial()"
                     << endl << ", or check the type: <int> or <double>"
                     << endl;
                continue;
            }
            gInfo.GetInfoVi(*itr, Vi);
            index = i_Vi[(*itr)+infoname];
            for (int i = 0; i < Vi.size(); ++i) {
                this->Vi_Ptr[index][i] = Vi[i];
            }
           /// cout << "\tVi_Ptr["<< index << " ] = ... " << endl;
            continue;
        }
    }
    // HepLorentzVector
    allInfo = gInfo.GetType("HepLorentzVector");
    HepLorentzVector p4;
    for (itr = allInfo.begin(); itr != allInfo.end(); itr++) {
        /// cout << "info in <TupleSvc::operator<< HepLorentzVector>:"; 
        /// cout << " name  = " << *itr << endl;
        if (i_Vd.find((*itr)+infoname) == i_Vd.end()) {
            cout << "Error, sorry we didn't find \"" << gInfo.GetName()
                 << "\". " << *itr << "()"
                 << ", you should Register it first at Initial()" << endl;
            continue;
        }
        /// cout << "info in <TupleSvc::operator<< HepLorentzVector>:"; 
        /// cout << " begin GetInfoH for " << *itr << endl;
        gInfo.GetInfoH(*itr, p4);
        index = i_Vd[(*itr) + infoname];
        /// cout << "index = " << index << endl;
        for (int i = 0; i < 4; ++i) {
            this->Vd_Ptr[index][i] = p4[i];
        }
    }
    return *this;
}
#endif

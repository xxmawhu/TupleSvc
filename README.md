# TupleSvc
## What's TupleSvc

TupleSvc is a package to provide useful services for writing into 
a Tuple. The typical way to writing some inforamtion of HadronInfo is 
very complex, we need create some Items with type int or double, 
then add them one by one to a sepcial tuple. 
```c++
Ntuple::Item<int> m_tracks;
Ntuple::Item<double> m_mass;
....

m_tuple->addItem("tracks", m_tracks);
m_tuple->addItem("mass", m_mass);
...
```  
With TupleSvc, the process becomes very simple and repliable.
The typical usage is 
## Create a TupleSvc and bind it with a tuple

```c++
TupleSvc m_tupleSvc;
m_tupleSvc.BindTuple(atuple);
```
## Register necessary HadronInfo

You can register any class that buind on the base class "AviableInfo".
for example:
```c++
m_tupleSvc.Register(aPionInfo);
m_tupleSvc.Register(aBeamInfo);
m_tupleSvc.Register(aMCTruthInfo);
```
## Write into the tuple

The operation "<<" is overloaded, which will get all aviable information that
registered already. You can write all information about one hadron.
```c++
aPionInfo.Feed(aCandidate);
m_tupleSvc << aPionInfo;
```
You can also write beam information, such as the beam energy, run ID, etc.
```c++
m_tupleSvc << aBeamInfo;
```

## Too boring?

If you feel too boring to register the HadronInfo one by one, 
I suggest you choose the "DecayChainSvc", in which one only nedd provide the
decay chain, then it will automatically register all associated information.
```c++
// DecayTree is a struct that represents the decay chain.
// you can initialize a DecayTree with a vector of integers.
// such as vector<int> fianlPID;
// ...
// DecayTree decayTree(fianlPID);
gDecayChainSvc.SetDecayTree(signalDecayTree);
gDecayChainSvc.BulkRegister(aTupleSvc);
...
// the way to fill alll information
// the decay tree must keep same with that registered at the TupleSvc
gDecayChainSvc.SetDecayTree(signalDecayTree);
gDecayChainSvc.Express(aCandidate, aTupleSvc);
```

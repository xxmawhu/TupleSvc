# TupleSvc
## usage
### Set up the decay tree
```c++
DecayTree decayTree(fid);
```
### feed the tuple
```
TupleSvc tuplsvc;
```
* bind the Item address
```c++
// NTuple::Item<int> *itemAdress;
tuplsvc.SetItemAddress("int", itemAdress, 100);
// NTuple::Item<double> itemAdress;
tuplsvc.SetItemAddress("double", itemAdress, 100);
// NTuple::Array<double> itemAdress;
tuplsvc.SetItemAddress("array", itemAdress, 100);
```
* initial one tuple

```c++
// NTuple *tp;
tuple.InitTuple(tuple);
```

* save the signal inforamtion
``c++
const CDCandidate& signal=...;
tuple.SaveInfo(signal);
```

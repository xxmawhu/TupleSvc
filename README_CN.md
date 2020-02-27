# TupleSvc
## 名字的由来

“Svc”是英文单词service的简称，“Tuple”是最常见的存储事例数据的结构，
可以放长度唯一的量，比如编号，粒子不变质量；可以放长度固定的数据，
比如粒子的位置坐标，长度为3，粒子的动量值，长度为4；还可以放长度
可变的数组，比如所有末态粒子的能量等。然而，当处理的对象多而杂时，
单单是声明和创建就需要一百多行代码，工作耗时而费力，出了错更为麻烦，
故早早有了这些计划，今天
终于将它变成了现实，特性和用法在下面将详细叙述。

## 有哪些干货

* 向一个tuple里自动的加东西写东西
* 批量的处理末态粒子信息

## 先睹为快
### 灵活的加入

声明并向tuple里添加一个末态粒子所有的信息，包括质量，动量，位置等等，
由接口`Register`实现，简单而好用，比如
```c++
m_tupleSvc.Register(aPionInfo);
m_tupleSvc.Register(aBeamInfo);
m_tupleSvc.Register(aMCTruthInfo);
```
第一行就将pion的所有信息加入到了tuple里，第二行则加入了束流的所有可能信息，
保留run的编号，事例的编号，带电径迹数目等等，第三行则加入了蒙特卡洛样本里
所有的粒子真实信息，比如粒子初始的位置和动量，粒子衰变时刻的位置和时间。

### 写入方便

为了写入的方便，流运算符"<<"被重载了，因为它的样子太形象了，用起来格外的方便。
```c++
aPionInfo.Feed(aTrk);
m_tupleSvc << aPionInfo;
m_tupleSvc << aBeamInfo;
m_tupleSvc << aMCTruthInfo;
```

## 更进一步
### 批量注册与写入

一个类"DecayChainSvc"提供了这种功能，即批量的注册（Register）所有的末态粒子，
并批量的写入。“DecayTree”是用来描述末态粒子的类，通过整型矢量来初始化。
```c++
vector<int> fid;
...
DecayTree decayTree(fid);
```
其中数组存储末态粒子的编号。使用“DecayChainSvc”是手续如下
* 声明和定义
```c++
DecayChainSvc gDecayChainSvc;
```
* 设置“DecayTree”
```c++
gDecayChainSvc.DecayTree(decayTree);
```
* 注册
```
gDecayChainSvc.BulkRegister(aTupleSvc);
```

* 写入
```c++
gDecayChainSvc.Express(aCandidate, aTupleSvc);
```

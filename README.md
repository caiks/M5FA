# M5FA - Kaggle Competition - M5 Forecasting - Accuracy

https://www.kaggle.com/c/m5-forecasting-accuracy

This repository depends on the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC). The AlignmentRepaC repository is a fast C++ implementation of some of the *practicable inducers* described in the paper *The Theory and Practice of Induction by Alignment* at https://greenlake.co.uk/. 

## Download

The `M5FA` executable requires the `AlignmentRepa` module which is in the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC). See the AlignmentRepaC repository for installation instructions of the C++ compiler.

Download the zip files or use git to get the `M5FA` repository, its workspace repository, and the underlying rapidjson, `AlignmentC` and `AlignmentRepaC` repositories -
```
cd
git clone https://github.com/Tencent/rapidjson.git
git clone https://github.com/caiks/AlignmentC.git
git clone https://github.com/caiks/AlignmentRepaC.git
git clone https://github.com/caiks/M5FA.git
git clone https://github.com/caiks/M5FA_ws.git

```
Then download the dataset files to a workspace, 
```
cd M5FA_ws
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
gunzip *.gz
cd ..

```

## Build

Ubuntu release -
```sh
mkdir AlignmentC_build AlignmentRepaC_build M5FA_build
cd M5FA_build
cmake -DCMAKE_BUILD_TYPE=RELEASE ../M5FA
make

```

## Usage

Ubuntu -
```sh
cd ../M5FA_ws
ln -s ../M5FA_build/M5FA M5FA
export PATH=$PATH:./
/usr/bin/time -v M5FA induce model112 >model112.log 2>&1

```
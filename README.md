# M5FA - Kaggle Competition - M5 Forecasting - Accuracy

https://www.kaggle.com/c/m5-forecasting-accuracy

https://mofc.unic.ac.cy/m5-competition/

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
Then download the dataset files `m5-forecasting-accuracy.zip` at https://www.kaggle.com/c/m5-forecasting-accuracy/data to the workspace, 
```
cd M5FA_ws
ls -l *.csv

head *.csv

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
ln -s ../M5FA_build/main main
export PATH=$PATH:./
./main

```
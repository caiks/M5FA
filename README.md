# M5FA - MOFC M5 Forecasting

The [M Open Forecasting Center (MOFC) M5 Competition](https://mofc.unic.ac.cy/m5-competition/) aims to forecast the unit sales of Walmart retail goods. It is being run using the [Kaggle Platform](https://www.kaggle.com/c/m5-forecasting-accuracy). The data consists of 1913 days of sales volumes of around 30,000 items over 10 stores in 3 states of USA. This repository explores creating *induced* and *conditioned models* from this *history*. 

This repository depends on the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC). The AlignmentRepaC repository is a fast C++ implementation of some of the *practicable inducers* described in the paper *The Theory and Practice of Induction by Alignment* at https://greenlake.co.uk/. 

## Download

The `M5FA` executable requires the `AlignmentRepa` module which is in the [AlignmentRepaC repository](https://github.com/caiks/AlignmentRepaC). See the AlignmentRepaC repository for installation instructions of the C++ compiler.

Download the zip files or use git to get the `M5FA` repository, its workspace repository, and the underlying `rapidjson`, `AlignmentC` and `AlignmentRepaC` repositories,
```
cd
git clone https://github.com/Tencent/rapidjson.git
git clone https://github.com/caiks/AlignmentC.git
git clone https://github.com/caiks/AlignmentRepaC.git
git clone https://github.com/caiks/M5FA.git
git clone https://github.com/caiks/M5FA_ws.git

```
Then download the dataset files `m5-forecasting-accuracy.zip` from [Kaggle](https://www.kaggle.com/c/m5-forecasting-accuracy/data) and unzip them to the workspace, 
```
cd ~/M5FA_ws

ls -l *.csv
-rw-r--r-- 1 caiks caiks    103469 Mar  2 01:48 calendar.csv
-rw-r--r-- 1 caiks caiks 120007726 Mar  2 01:48 sales_train_validation.csv
-rw-r--r-- 1 caiks caiks   5228786 Mar  2 01:48 sample_submission.csv
-rw-r--r-- 1 caiks caiks 203395785 Mar  2 01:48 sell_prices.csv

head *.csv

```

## Build

```
cd
mkdir AlignmentC_build AlignmentRepaC_build M5FA_build
cd M5FA_build
cmake -DCMAKE_BUILD_TYPE=RELEASE ../M5FA
make

```

## Discussion

To run the main executable, change directory to the workspace and create a link to the executable,
```
cd ~/M5FA_ws
ln -s ../M5FA_build/main main

```
`dev.h` defines a function `recordSalesListIO` to load the `RecordSalesList` from `sales_train_validation.csv`,
```cpp
std::unique_ptr<RecordSalesList> recordSalesListIO();
```
We can view the contents,
```
./main sales | head -1
*records: (HOBBIES_1_001_CA_1_validation,HOBBIES_1_001,HOBBIES_1,HOBBIES,CA_1,CA,(0,0,0,0,0,0, ... 1,3,0,1,1,1,3,0,1,1))
```
Analyse the items by category and store
```
./main sales_counts2
FOODS,CA_1: 1437
FOODS,CA_2: 1437
FOODS,CA_3: 1437
FOODS,CA_4: 1437
FOODS,TX_1: 1437
FOODS,TX_2: 1437
FOODS,TX_3: 1437
FOODS,WI_1: 1437
FOODS,WI_2: 1437
FOODS,WI_3: 1437
HOBBIES,CA_1: 565
HOBBIES,CA_2: 565
HOBBIES,CA_3: 565
HOBBIES,CA_4: 565
HOBBIES,TX_1: 565
HOBBIES,TX_2: 565
HOBBIES,TX_3: 565
HOBBIES,WI_1: 565
HOBBIES,WI_2: 565
HOBBIES,WI_3: 565
HOUSEHOLD,CA_1: 1047
HOUSEHOLD,CA_2: 1047
HOUSEHOLD,CA_3: 1047
HOUSEHOLD,CA_4: 1047
HOUSEHOLD,TX_1: 1047
HOUSEHOLD,TX_2: 1047
HOUSEHOLD,TX_3: 1047
HOUSEHOLD,WI_1: 1047
HOUSEHOLD,WI_2: 1047
HOUSEHOLD,WI_3: 1047
```
Now define a function to read the `RecordSalesList` and create a *history* with *variables* bucketed by sorting the sales for each item and selecting percentiles, 
```cpp
SystemHistoryRepaTuple trainBucketedCategoryStoreIO(int, std::string, std::string);
```
View the first *event* for category `FOODS` and store `CA_1` with up to 10 buckets,
```
./main view_category_store FOODS CA_1

sorted(*uvars(*uu)): {FOODS_1_001_CA_1_validation,FOODS_1_002_CA_1_validation,FOODS_1_003_CA_1_validation, ...
hr->dimension: 1437
hr->size: 1913
*hrsel(*hr, SizeList{0}): (1437,[0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, ... ,1432,1433,1434,1435,1436],[4,4,4,8,5, ... 7,6,4,8,4,4,5,5,3],1,false,[3,0,0,0,3,0,0,0,0,2,0,2, ... 2,0,1,0,0,0])
```
Now *induce* some *models* with various sets of parameters,
```
./main induce_category_store model001 FOODS CA_1 >model001.log

hr->dimension: 1437
hr->size: 1913

>>> applicationer
...
<<< applicationer 6.48995s

treesSize(*dr->slices): 641
frder(*dr->fud)->size(): 515
frund(*dr->fud)->size(): 311
frvars(*dr->fud)->size(): 2878
```
We can roughly gauge the *likelihood* of the *model* by examining the log for `derived impl bi-valency percent:` or the *diagonal percentage*. The average *diagonal percentage* for `model001` is 16.67.
```
./main induce_category_store2 model002 FOODS CA_1 >model002.log

hr->dimension: 1437
hr->size: 1913

>>> applicationer
...
<<< applicationer 767.849s

treesSize(*dr->slices): 515
frder(*dr->fud)->size(): 389
frund(*dr->fud)->size(): 372
frvars(*dr->fud)->size(): 3719
```
The average *diagonal percentage* for `model002` is 24.36. The *slice tree* is more regular and the set of *underlying* is larger.

Now test to see how well the *model slices* work in a perfect *derived conditional model*. That is, determine the *slice* an *event* is in and then for each item calculate the ratio of (a) the daily variance of the difference between (1) the *event's* sales and (2) *slice's* average sales, to (b) the historical daily variance,
```
./main model_error_category_store model001 FOODS CA_1
hr->dimension: 1437
hr->size: 1913
treesSize(*dr->slices): 641
treesLeafElements(*dr->slices)->size(): 515
frder(*dr->fud)->size(): 515
frund(*dr->fud)->size(): 311
frvars(*dr->fud)->size(): 2878
...
FOODS_3_823_CA_1_validation:    1.38388 1.22837 1.1266
FOODS_3_824_CA_1_validation:    1.34843 1.5099  0.893055
FOODS_3_825_CA_1_validation:    1.53134 1.57617 0.97156
FOODS_3_826_CA_1_validation:    1.7372  1.70588 1.01836
FOODS_3_827_CA_1_validation:    2.79143 2.27146 1.22892
err: 1.00756
```
An average variance ratio of around 1 suggests that the *slices* are too large to make predictions better than the strategy of simply taking the yesterday's sales as the forecast for today. 
```
./main model_error_category_store model002 FOODS CA_1
hr->dimension: 1437
hr->size: 1913
treesSize(*dr->slices): 515
treesLeafElements(*dr->slices)->size(): 389
frder(*dr->fud)->size(): 389
frund(*dr->fud)->size(): 372
frvars(*dr->fud)->size(): 3719
...
FOODS_3_823_CA_1_validation:    1.43286 1.22837 1.16648
FOODS_3_824_CA_1_validation:    1.37774 1.5099  0.912468
FOODS_3_825_CA_1_validation:    1.50724 1.57617 0.956266
FOODS_3_826_CA_1_validation:    1.85988 1.70588 1.09028
FOODS_3_827_CA_1_validation:    2.92528 2.27146 1.28784
err: 1.01771
```
Although `model002` is more *likely* than `model001` the variance ratio is little different. 

In `model003` we increase the depth of the *model* by increasing `fmax` from 128 to 1914,
```
./main induce_category_store3 model003 FOODS CA_1 >model003.log

treesSize(*dr->slices): 3919
frder(*dr->fud)->size(): 2706
frund(*dr->fud)->size(): 1195
frvars(*dr->fud)->size(): 13564
```
but now the *slices* are too small,
```
./main model_error_category_store model003 FOODS CA_1
hr->dimension: 1437
hr->size: 1913
treesSize(*dr->slices): 3919
treesLeafElements(*dr->slices)->size(): 2706
frder(*dr->fud)->size(): 2706
frund(*dr->fud)->size(): 1195
frvars(*dr->fud)->size(): 13564
...
FOODS_3_823_CA_1_validation:    1.70855 1.22837 1.39091
FOODS_3_824_CA_1_validation:    1.62955 1.5099  1.07924
FOODS_3_825_CA_1_validation:    1.8554  1.57617 1.17716
FOODS_3_826_CA_1_validation:    2.1614  1.70588 1.26702
FOODS_3_827_CA_1_validation:    3.38477 2.27146 1.49013
err: 1.21323
```
In `model004` we increase the number of buckets from 10 to 20,
```
./main induce_category_store4 model004 FOODS CA_1 >model004.log

./main model_error_category_store model004 FOODS CA_1
hr->dimension: 1437
hr->size: 1913
treesSize(*dr->slices): 533
treesLeafElements(*dr->slices)->size(): 407
frder(*dr->fud)->size(): 407
frund(*dr->fud)->size(): 582
frvars(*dr->fud)->size(): 3742
...
FOODS_3_823_CA_1_validation:    1.47909 1.22837 1.20411
FOODS_3_824_CA_1_validation:    1.36104 1.5099  0.901408
FOODS_3_825_CA_1_validation:    1.51014 1.57617 0.95811
FOODS_3_826_CA_1_validation:    1.73505 1.70588 1.0171
FOODS_3_827_CA_1_validation:    3.00531 2.27146 1.32308
err: 1.02174
```
but there is no improvement over 10 buckets.

Try a different categories and stores,
```
./main induce_category_store model005 HOUSEHOLD TX_3 >model005.log

./main model_error_category_store model005 HOUSEHOLD TX_3
hr->dimension: 1047
hr->size: 1913
treesSize(*dr->slices): 626
treesLeafElements(*dr->slices)->size(): 500
frder(*dr->fud)->size(): 500
frund(*dr->fud)->size(): 203
frvars(*dr->fud)->size(): 3012
...
HOUSEHOLD_2_512_TX_3_validation:        0.713884        0.888678        0.80331
HOUSEHOLD_2_513_TX_3_validation:        0.9555  0.988691        0.966429
HOUSEHOLD_2_514_TX_3_validation:        0.366564        0.477529        0.767627
HOUSEHOLD_2_515_TX_3_validation:        0.248856        0.315234        0.789434
HOUSEHOLD_2_516_TX_3_validation:        0.387246        0.473127        0.818482
err: 0.873123

./main induce_category_store model006 HOBBIES WI_2 >model006.log

./main model_error_category_store model006 HOBBIES WI_2
hr->dimension: 565
hr->size: 1913
treesSize(*dr->slices): 627
treesLeafElements(*dr->slices)->size(): 501
frder(*dr->fud)->size(): 501
frund(*dr->fud)->size(): 148
frvars(*dr->fud)->size(): 2996
...
HOBBIES_2_145_WI_2_validation:  0.634806        0.826787        0.767798
HOBBIES_2_146_WI_2_validation:  0.521576        0.635426        0.820829
HOBBIES_2_147_WI_2_validation:  0.552236        0.683793        0.807606
HOBBIES_2_148_WI_2_validation:  0.547398        0.688367        0.795212
HOBBIES_2_149_WI_2_validation:  0.575687        0.658069        0.874812
err: 0.821158
```
We can speculate that 1913 *events* is too few for the *unsupervised model* to be very accurate without restricting to smaller *substrates* or adding further information such as calendar or holidays. 

Consider if simply *scaling* the *history* would improve matters. Here we repeat `model001` with ten times the *events*,
```
./main induce_category_store model007 FOODS CA_1 10 >model007.log

./main model_error_category_store model007 FOODS CA_1 10
hr->dimension: 1437
hr->size: 19130
treesSize(*dr->slices): 690
treesLeafElements(*dr->slices)->size(): 564
frder(*dr->fud)->size(): 564
frund(*dr->fud)->size(): 285
frvars(*dr->fud)->size(): 2415
...
err: 1.00975
```
There is little change, as we would expect for an `fmax` of 128. Now repeat `model003` with its `fmax` of 1914,
```
./main induce_category_store3 model008 FOODS CA_1 10 >model008.log

./main model_error_category_store model008 FOODS CA_1 10
hr->dimension: 1437
hr->size: 19130
treesSize(*dr->slices): 3690
treesLeafElements(*dr->slices)->size(): 2657
frder(*dr->fud)->size(): 2657
frund(*dr->fud)->size(): 1241
frvars(*dr->fud)->size(): 17322
...
err: 1.22374
```
Again, there is little change. Clearly most of the *alignments* relevant to prediction are already in the *model*.

Regardless of an implied position that would be a long way down the [Kaggle leaderboard](https://www.kaggle.com/c/m5-forecasting-accuracy/leaderboard), we shall go on to consider constructing a time-wise set of *frames* with copies of the *induced model* in each *frame*. The *slice variables* of these *model applications* will then form the *substrate* of a *conditional model* where the label is the set of *slice variables* in the next *frame*. This *2-level model* then can be rolled daily to provide a *simulation* of the short term future.



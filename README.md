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

Regardless of an implied position that would be a long way down the [Kaggle leaderboard](https://www.kaggle.com/c/m5-forecasting-accuracy/leaderboard), we shall go on to consider constructing a time-wise set of past *frames* with copies of the *induced model* in each *frame*. The *slice variables* of these *model applications* will then form the *substrate* of a *conditioned model* where the label is the set of *slice variables* in the current *frame*. If desired, this *2-level model* then could be rolled *frame* by *frame* to provide a *simulation* of the short term future.

The `condition_category_store` process constructs time-wise *frames* from successive *events* and copies the given *model* to each *frame*. In the example below 10 *frames* are constructed, the current *frame* and 9 past *frames*. Then it runs the *multinomial conditioner* for 512 *fuds* in a second *level* where the *underlying level* consists of the *leaf slices* of just the 9 past *frames*. The label is a *partition variable* of *valency* equal to the cardinality of *leaf slices* of the current *frame*. It then saves the resultant *model* joined with the *underlying level*,
```
./main condition_category_store model001 model009 FOODS CA_1 10 512 >model009.log
hr1->dimension: 14370
hr1->size: 1904
treesSize(*dr1.slices): 6410
treesLeafElements(*dr1.slices)->size(): 5150
frder(*dr1.fud)->size(): 5150
frund(*dr1.fud)->size(): 3110
frvars(*dr1.fud)->size(): 28780
hr2->dimension: 40040
hr2->size: 1904
>>> applicationer
>>> searcher 
<<< searcher 0.0623936s
>>> transer 
fud: 1
fud slice size: 1904
sized entropy label : 10236.9
sized conditional entropy: 9528.73
sized entropy decrease: 708.218
entropy variable: <<<1,2>,s>,10>
<<< transer 2.11e-05s
...
>>> slicer 
slice size: 5
slice variable: <<<11,305>,s>,1>
<<< slicer 0.0021237s
>>> searcher 
<<< searcher 0.040869s
>>> transer 
fud: 512
fud slice size: 5
sized entropy label : 4.78749
sized conditional entropy: 2.48491
sized entropy decrease: 2.30259
entropy variable: <<<1,3>,s>,9>
fud slice cardinality: 2
<<< transer 1.5e-05s
<<< applicationer 23.0629s
treesSize(*dr3->slices): 1024
treesLeafElements(*dr3->slices)->size(): 513
frder(*dr3->fud)->size(): 513
frund(*dr3->fud)->size(): 490
frvars(*dr3->fud)->size(): 4085
```
Over the 512 *fuds* the *label entropy* is reduced from 10236.9 to 4.78749, with the last *slice size* of 5 *events*. Let us increase the `fmax` to completely resolve the label,
```
./main condition_category_store model001 model010 FOODS CA_1 10 2048 >model010.log
>>> transer 
...
fud: 1
fud slice size: 1904
sized entropy label : 10236.9
sized conditional entropy: 9528.73
sized entropy decrease: 708.218
entropy variable: <<<1,2>,s>,10>
<<< transer 1.83e-05s
...
>>> slicer 
slice size: 2
slice variable: <<<11,407>,s>,2>
<<< slicer 0.0047459s
>>> searcher 
<<< searcher 0.0039961s
>>> transer 
fud: 1718
fud slice size: 2
sized entropy label : 0.693147
sized conditional entropy: 0
sized entropy decrease: 0.693147
entropy variable: <<<1,115>,s>,2>
fud slice cardinality: 2
<<< transer 1.82e-05s
treesSize(*dr3->slices): 3436
treesLeafElements(*dr3->slices)->size(): 1719
frder(*dr3->fud)->size(): 1719
frund(*dr3->fud)->size(): 797
frvars(*dr3->fud)->size(): 8913
```
The *conditioner* requires 1719 leaf nodes to completely *partition* 1904 *events*, i.e. around 1.1 *events* per *slice*. So it does not seem to be very predictive with 9 past *frames*.

Now compare the process with `model002` as the *underlying model* instead of `model001`,
```
./main condition_category_store model002 model011 FOODS CA_1 10 2048 >model011.log
hr1->dimension: 14370
hr1->size: 1904
treesSize(*dr1.slices): 5150
treesLeafElements(*dr1.slices)->size(): 3890
frder(*dr1.fud)->size(): 3890
frund(*dr1.fud)->size(): 3720
frvars(*dr1.fud)->size(): 37190
hr2->dimension: 47840
hr2->size: 1904
>>> applicationer
>>> searcher 
<<< searcher 0.0435397s
>>> transer 
fud: 1
fud slice size: 1904
sized entropy label : 9571.59
sized conditional entropy: 8397.02
sized entropy decrease: 1174.57
entropy variable: <<<1,3>,s>,10>
<<< transer 1.81e-05s
...
>>> slicer 
slice size: 2
slice variable: <<<11,193>,s>,2>
<<< slicer 0.0026758s
>>> searcher 
<<< searcher 0.0026168s
>>> transer 
fud: 1280
fud slice size: 2
sized entropy label : 0.693147
sized conditional entropy: 0
sized entropy decrease: 0.693147
entropy variable: <<<2,38>,s>,2>
fud slice cardinality: 2
<<< transer 1.41e-05s
>>> slicer 
no slices
<<< applicationer 22.9586s
treesSize(*dr3->slices): 2560
treesLeafElements(*dr3->slices)->size(): 1281
frder(*dr3->fud)->size(): 1281
frund(*dr3->fud)->size(): 2307
frvars(*dr3->fud)->size(): 20779
```
This requires 1281 leaf nodes to completely partition 1904 *events*, i.e. 1.5 *events* per *slice*. This is because `model001` has 515 `leaf slices` versus only 389 in `model002`, which means that the starting *label entropy* is lower at 9571.59. The initial decrease is also greater. `model002` has a larger *underlying* and longer *implied diagonal* so it is a more *likely model* than `model001`. The *unsupervised alignments* are more *aligned* with the *label variable*. 

Now consider if 20 *frames* improves the *accuracy*,
```
./main condition_category_store model002 model012 FOODS CA_1 20 2048 >model012.log
hr1->dimension: 28740
hr1->size: 1894
treesSize(*dr1.slices): 10300
treesLeafElements(*dr1.slices)->size(): 7780
frder(*dr1.fud)->size(): 7780
frund(*dr1.fud)->size(): 7440
frvars(*dr1.fud)->size(): 74380
hr2->dimension: 95680
hr2->size: 1894
>>> applicationer
>>> searcher 
<<< searcher 0.0923371s
>>> transer 
fud: 1
fud slice size: 1894
sized entropy label : 9520.76
sized conditional entropy: 8350.58
sized entropy decrease: 1170.18
entropy variable: <<<1,3>,s>,10>
<<< transer 0.0240461s
...
>>> slicer 
slice size: 2
slice variable: <<<21,282>,s>,2>
<<< slicer 0.0022175s
>>> searcher 
<<< searcher 0.0023998s
>>> transer 
fud: 1175
fud slice size: 2
sized entropy label : 0.693147
sized conditional entropy: 0
sized entropy decrease: 0.693147
entropy variable: <<<2,38>,s>,2>
fud slice cardinality: 2
<<< transer 1.45e-05s
>>> slicer 
no slices
<<< applicationer 39.2629s
treesSize(*dr3->slices): 2350
treesLeafElements(*dr3->slices)->size(): 1176
frder(*dr3->fud)->size(): 1176
frund(*dr3->fud)->size(): 3325
frvars(*dr3->fud)->size(): 26046
```
With 20 *frames* there is a further improvement to 1176 *slices*, i.e. to 1.6 *events* per *slice*.

Now consider which *slices* of the *underlying level* are chosen as the *conditioned model tree* is constructed. As we would expect the first nodes tend to copy the previous day's *slice tree*, until *fud* 8 which then accesses the second day in the past, *frame* 2,
```
>>> slicer 
slice size: 298
slice variable: <<<21,5>,s>,2>
<<< slicer 4.16e-05s
>>> searcher 
<<< searcher 0.0515161s
>>> transer 
fud: 8
fud slice size: 298
sized entropy label : 1098.16
sized conditional entropy: 986.513
sized entropy decrease: 111.646
entropy variable: <<<2,9>,s>,6>
fud slice cardinality: 2
<<< transer 1.6e-05s
```
It is not until *fud* 62 that *frame* 1 is no longer used much,
```
>>> slicer 
slice size: 52
slice variable: <<<21,43>,s>,1>
<<< slicer 0.0002215s
>>> searcher 
<<< searcher 0.0477149s
>>> transer 
fud: 62
fud slice size: 52
sized entropy label : 98.0634
sized conditional entropy: 81.3265
sized entropy decrease: 16.7369
entropy variable: <<<17,35>,s>,2>
fud slice cardinality: 2
<<< transer 1.87e-05s
```
From this point on the *slices* seem to be taken from all of the *frames* uniformly, so perhaps it is here that time-wise periodic *alignments* with the label become visible.

From *fud* 433 there is a drop in the *slice size* from 16 to 5. Thereafter, the *slices* tend to come from the first *frame* suggesting that they are more randomly chosen and have little predictive quality,
```
>>> slicer 
slice size: 16
slice variable: <<<21,106>,s>,2>
<<< slicer 0.0014706s
>>> searcher 
<<< searcher 0.0492072s
>>> transer 
fud: 432
fud slice size: 16
sized entropy label : 4.78749
sized conditional entropy: 2.70805
sized entropy decrease: 2.07944
entropy variable: <<<7,23>,s>,1>
fud slice cardinality: 2
<<< transer 1.72e-05s
>>> slicer 
slice size: 5
slice variable: <<<21,283>,s>,1>
<<< slicer 0.001409s
>>> searcher 
<<< searcher 0.049314s
>>> transer 
fud: 433
fud slice size: 5
sized entropy label : 4.78749
sized conditional entropy: 2.48491
sized entropy decrease: 2.30259
entropy variable: <<<1,9>,s>,1>
fud slice cardinality: 2
<<< transer 1.58e-05s
```
If we take the effective *slices* to be 433 that suggests around 4.4 *events* per *slice*.
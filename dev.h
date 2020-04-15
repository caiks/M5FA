#ifndef M5FADEV_H
#define M5FADEV_H

#include "AlignmentUtil.h"
#include "Alignment.h"
#include "AlignmentApprox.h"
#include "AlignmentAeson.h"
#include "AlignmentRepa.h"
#include "AlignmentAesonRepa.h"
#include "AlignmentRandomRepa.h"
#include "AlignmentPracticableRepa.h"
#include "AlignmentPracticableIORepa.h"

#include <iomanip>
#include <set>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <thread>
#include <chrono>
#include <ctime>
#include <string>


namespace M5FA
{
    struct Record
    {
		std::string id;
		std::string item_id;
		std::string dept_id;
		std::string cat_id;
		std::string store_id;
		std::string state_id;
		std::vector<int> d;
    };
    typedef std::vector<Record> RecordList;




	typedef std::tuple<std::unique_ptr<Alignment::System>, std::unique_ptr<Alignment::SystemRepa>, std::unique_ptr<Alignment::HistoryRepa>> SystemHistoryRepaTuple;

	// trainBucketedIO :: Int -> IO (System, HistoryRepa)
	SystemHistoryRepaTuple trainBucketedIO(int);

	// trainBucketedAffineIO :: Int -> Int -> Double -> Int -> IO (System, HistoryRepa)
	SystemHistoryRepaTuple trainBucketedAffineIO(int, int, double, int);

	// trainBucketedIO :: Int -> IO (System, HistoryRepa)
	SystemHistoryRepaTuple trainBucketedRegionRandomIO(int,int,int);

	// testBucketedIO :: Int -> IO (System, HistoryRepa)
	SystemHistoryRepaTuple testBucketedIO(int);

}


#endif
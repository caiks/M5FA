﻿#ifndef M5FADEV_H
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
	struct RecordSales
	{
		std::string id;
		std::string item_id;
		std::string dept_id;
		std::string cat_id;
		std::string store_id;
		std::string state_id;
		std::vector<int> d;
	};
	typedef std::vector<RecordSales> RecordSalesList;
	
	std::unique_ptr<RecordSalesList> recordSalesListIO();

	typedef std::tuple<std::unique_ptr<Alignment::System>, std::unique_ptr<Alignment::SystemRepa>, std::unique_ptr<Alignment::HistoryRepa>, std::unique_ptr<RecordSalesList>> SystemHistoryRepaTuple;

	SystemHistoryRepaTuple trainBucketedCategoryStoreIO(int, std::string, std::string);

}

std::ostream& operator<<(std::ostream& out, const M5FA::RecordSales&);
std::ostream& operator<<(std::ostream& out, const M5FA::RecordSalesList&);


#endif
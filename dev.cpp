#include "dev.h"

#include <stdlib.h>
#include <random>

using namespace Alignment;
using namespace M5FA;
using namespace std;

#define ECHO(x) cout << #x << endl; x
#define EVAL(x) cout << #x << ": " << (x) << endl

std::ostream& operator<<(std::ostream& out, const RecordSales& r)
{
    out << "(" << r.id 
		<< "," << r.item_id 
		<< "," << r.dept_id
		<< "," << r.cat_id
		<< "," << r.store_id
		<< "," << r.state_id 
		<< ",(";
    for (std::size_t i = 0; i < r.d.size(); i++)
		out << (i ? "," : "") << r.d[i];
    out << "))";
    return out;
}

std::ostream& operator<<(std::ostream& out, const RecordSalesList& rr)
{
    for (auto& r : rr)
		out << r << std::endl;
    return out;
}

std::unique_ptr<RecordSalesList> M5FA::recordSalesListIO()
{
	auto records = std::make_unique<RecordSalesList>();
	try
	{
		ifstream file("sales_train_validation.csv");
		if (!file.is_open())
		{
			cout << "recordSalesListIO : cannot open files" << endl;
			return records;
		}
		std::string line = "";
		getline(file, line);
		while (getline(file, line))
		{
			//EVAL(line);
			std::stringstream lineStream(line);
            std::string cell;
			std::vector<std::string> vec;
            while(std::getline(lineStream, cell, ','))
                vec.push_back(cell);
            if (!lineStream && cell.empty())
                vec.push_back("");
			if (vec.size() < 7)
			{
				cout << "recordSalesListIO : vec too small : " << vec.size() << endl;
				return records;
			}
			RecordSales record;
			record.id = vec[0];
			record.item_id = vec[1];
			record.dept_id = vec[2];
			record.cat_id = vec[3];
			record.store_id = vec[4];
			record.state_id = vec[5];
			for (std::size_t i = 6; i < vec.size(); i++)
				record.d.push_back(std::stoi(vec[i]));
			records->push_back(record);
		}
	}
	catch (const exception& e)
	{
		cout << "recordSalesListIO : " << e.what() << endl;
		return records;
	}
	return records;
}

SystemHistoryRepaTuple M5FA::trainBucketedCategoryStoreIO(int d, std::string cat_id, std::string store_id)
{
	auto lluu = listsSystem_u;
	auto uuur = systemsSystemRepa;

	auto records = recordSalesListIO();
	std::vector<VarValSetPair> ll;
	RecordSalesList records1;
	std::vector<std::vector<int>> listBuckets;
	for (auto& record : *records)
		if (record.cat_id == cat_id && record.store_id == store_id)
		{
			records1.push_back(record);
			std::vector<int> buckets;
			RecordSales record1(record);
			std::sort(record1.d.begin(), record1.d.end());
			for (int i = 0; i < d; i++)
				buckets.push_back(record1.d[i * record1.d.size() / d]);
			buckets.push_back(record1.d.back());
			auto last = std::unique(buckets.begin(), buckets.end());
			buckets.erase(last, buckets.end());
			listBuckets.push_back(buckets);
			ValSet valSetBuckets;
			for (int i = 0; i < buckets.size(); i++)
				valSetBuckets.insert(Value(i));
			ll.push_back(VarValSetPair(Variable(record.id), valSetBuckets));
		}
	auto uu = lluu(ll);
	auto ur = uuur(*uu);
	auto hr = make_unique<HistoryRepa>();
	hr->dimension = records1.size();
	auto n = hr->dimension;
	hr->vectorVar = new size_t[n];
	auto vv = hr->vectorVar;
	hr->shape = new size_t[n];
	auto sh = hr->shape;
	size_t z = records1.front().d.size();
	hr->size = z;
	hr->evient = false;
	hr->arr = new unsigned char[n * z];
	auto rr = hr->arr;
	for (size_t i = 0; i < n; i++)
	{
		vv[i] = i;
		sh[i] = listBuckets[i].size();
	}
	for (size_t i = 0; i < n; i++)
	{
		auto record = records1[i];
		auto buckets = listBuckets[i];
		size_t iz = i * z;
		for (size_t j = 0; j < z; j++)
			for (size_t k = 0; k < buckets.size(); k++)
				if (record.d[j] <= buckets[k])
				{
					rr[iz + j] = (unsigned char)k;
					break;
				}
	}
	return SystemHistoryRepaTuple(move(uu), move(ur), move(hr));
}




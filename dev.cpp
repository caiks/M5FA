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

// // trainBucketedAffineIO :: Int -> Int -> Double -> Int -> IO (System, HistoryRepa)
// SystemHistoryRepaTuple M5FA::trainBucketedAffineIO(int d, int r, double af, int s)
// {
	// auto lluu = listsSystem_u;
	// auto uuur = systemsSystemRepa;

	// const int a = 28;
	// const int z = 60000;
	// unsigned char* images = new unsigned char[z*a*a];
	// unsigned char* labels = new unsigned char[z];
	// try
	// {
		// ifstream fimages("train-images-idx3-ubyte", ios::binary);
		// ifstream flabels("train-labels-idx1-ubyte", ios::binary);
		// if (!fimages.is_open() || !flabels.is_open())
		// {
			// cout << "trainBucketedIO : cannot open files" << endl;
			// delete[] images;
			// delete[] labels;
			// return SystemHistoryRepaTuple();
		// }
		// fimages.read((char*)images, 16);
		// fimages.read((char*)images, z*a*a);
		// fimages.close();
		// flabels.read((char*)labels, 8);
		// flabels.read((char*)labels, z);
		// flabels.close();
	// }
	// catch (const exception& e)
	// {
		// cout << "trainBucketedIO : " << e.what() << endl;
		// delete[] images;
		// delete[] labels;
		// return SystemHistoryRepaTuple();
	// }
	// ValSet digits;
	// for (int i = 0; i < 10; i++)
		// digits.insert(Value(i));
	// ValSet buckets;
	// for (int i = 0; i < d; i++)
		// buckets.insert(Value(i));
	// vector<VarValSetPair> ll;
	// ll.push_back(VarValSetPair(Variable("digit"), digits));
	// for (int i = 0; i < a; i++)
		// for (int j = 0; j < a; j++)
			// ll.push_back(VarValSetPair(Variable(Variable(i + 1), Variable(j + 1)), buckets));
	// auto uu = lluu(ll);
	// auto ur = uuur(*uu);
	// auto hr = make_unique<HistoryRepa>();
	// hr->dimension = a*a + 1;
	// auto n = hr->dimension;
	// hr->vectorVar = new size_t[n];
	// auto vv = hr->vectorVar;
	// hr->shape = new size_t[n];
	// auto sh = hr->shape;
	// hr->size = r*z;
	// hr->evient = true;
	// hr->arr = new unsigned char[r*z*n];
	// auto rr = hr->arr;
	// for (size_t i = 0; i < n; i++)
		// vv[i] = i;
	// sh[0] = 10;
	// for (size_t i = 1; i < n; i++)
		// sh[i] = d;
	// size_t k = 0;
	// for (size_t j = 0; j < z; j++)
	// {
		// size_t jn = j*n;
		// rr[jn] = labels[j];
		// for (size_t i = 1; i < n; i++)
		// {
			// rr[jn + i] = images[k];
			// k++;
		// }
	// }
	// mt19937 gen(s); 
	// uniform_real_distribution<> dis(-af, af);
	// for (size_t j = z; j < r*z; j++)
	// {
		// size_t jn = j*n;
		// rr[jn] = rr[(j%z)*n];
		// double afw = dis(gen);
		// double afa = dis(gen);
		// double afb = dis(gen);
		// double afh = dis(gen);
		// for (int x = 0; x < a; x++)
			// for (int y = 0; y < a; y++)
			// {
				// double x1 = (1.0+afw)*(x-a/2) + afa*(y-a/2) + a/2;
				// double y1 = afb*(x-a/2) + (1.0+afh)*(y-a/2) + a/2;
				// double a1 = (int)floor(x1) < 0 || (int)floor(x1) >= a || (int)floor(y1) < 0 || (int)floor(y1) >= a ? 0.0 : (double)rr[(j%z)*n + 1 + a*(int)floor(x1) + (int)floor(y1)];
				// double a2 = (int)ceil(x1) < 0 || (int)ceil(x1) >= a || (int)floor(y1) < 0 || (int)floor(y1) >= a ? 0.0 : (double)rr[(j%z)*n + 1 + a*(int)ceil(x1) + (int)floor(y1)];
				// double a3 = (int)floor(x1) < 0 || (int)floor(x1) >= a || (int)ceil(y1) < 0 || (int)ceil(y1) >= a ? 0.0 : (double)rr[(j%z)*n + 1 + a*(int)floor(x1) + (int)ceil(y1)];
				// double a4 = (int)ceil(x1) < 0 || (int)ceil(x1) >= a || (int)ceil(y1) < 0 || (int)ceil(y1) >= a ? 0.0 : (double)rr[(j%z)*n + 1 + a*(int)ceil(x1) + (int)ceil(y1)];
				// double dx = x1 - floor(x1);
				// double dy = y1 - floor(y1);
				// double a5 = a1*(1.0-dx) + a2*dx;
				// double a6 = a3*(1.0-dx) + a4*dx;
				// double a7 = a5*(1.0-dy) + a6*dy;
				// if (a7 < 0.0)
					// a7 = 0.0;
				// if (a7 > 255.0)
					// a7 = 255.0;
				// rr[jn + 1 + a*x + y] = (int)a7;
			// }
	// }
	// for (size_t j = 0; j < r*z; j++)
	// {
		// size_t jn = j*n;
		// for (size_t i = 1; i < n; i++)
				// rr[jn + i] = rr[jn + i] * d / 256;
	// }
	// hr->transpose();
	// delete[] images;
	// delete[] labels;
	// return SystemHistoryRepaTuple(move(uu), move(ur), move(hr));
// }



// // trainBucketedRegionRandomIO :: Int -> Int -> Int -> IO (System, HistoryRepa)
// SystemHistoryRepaTuple M5FA::trainBucketedRegionRandomIO(int d, int b, int s)
// {
	// auto lluu = listsSystem_u;
	// auto uuur = systemsSystemRepa;

	// const int a = 28;
	// const int z = 60000;
	// unsigned char* images = new unsigned char[z*a*a];
	// unsigned char* labels = new unsigned char[z];
	// try
	// {
		// ifstream fimages("train-images-idx3-ubyte", ios::binary);
		// ifstream flabels("train-labels-idx1-ubyte", ios::binary);
		// if (!fimages.is_open() || !flabels.is_open())
		// {
			// cout << "trainBucketedIO : cannot open files" << endl;
			// delete[] images;
			// delete[] labels;
			// return SystemHistoryRepaTuple();
		// }
		// fimages.read((char*)images, 16);
		// fimages.read((char*)images, z*a*a);
		// fimages.close();
		// flabels.read((char*)labels, 8);
		// flabels.read((char*)labels, z);
		// flabels.close();
	// }
	// catch (const exception& e)
	// {
		// cout << "trainBucketedIO : " << e.what() << endl;
		// delete[] images;
		// delete[] labels;
		// return SystemHistoryRepaTuple();
	// }
	// ValSet digits;
	// for (int i = 0; i < 10; i++)
		// digits.insert(Value(i));
	// ValSet buckets;
	// for (int i = 0; i < d; i++)
		// buckets.insert(Value(i));
	// vector<VarValSetPair> ll;
	// ll.push_back(VarValSetPair(Variable("digit"), digits));
	// for (int i = 0; i < b; i++)
		// for (int j = 0; j < b; j++)
			// ll.push_back(VarValSetPair(Variable(Variable(i + 1), Variable(j + 1)), buckets));
	// auto uu = lluu(ll);
	// auto ur = uuur(*uu);
	// auto hr = make_unique<HistoryRepa>();
	// hr->dimension = b*b + 1;
	// auto n = hr->dimension;
	// hr->vectorVar = new size_t[n];
	// auto vv = hr->vectorVar;
	// hr->shape = new size_t[n];
	// auto sh = hr->shape;
	// hr->size = z;
	// hr->evient = true;
	// hr->arr = new unsigned char[z*n];
	// auto rr = hr->arr;
	// for (size_t i = 0; i < n; i++)
		// vv[i] = i;
	// sh[0] = 10;
	// for (size_t i = 1; i < n; i++)
		// sh[i] = d;
	// srand(s);
	// for (size_t j = 0; j < z; j++)
	// {
		// auto ox = rand() % (a-b+1);
		// auto oy = rand() % (a-b+1);
		// rr[j*n] = labels[j];
		// for (size_t ix = 0; ix < b; ix++)
			// for (size_t iy = 0; iy < b; iy++)
				// rr[j*n + 1 + ix*b + iy] = images[j*a*a + (ox+ix)*a + oy + iy] * d / 256;
	// }
	// hr->transpose();
	// delete[] images;
	// delete[] labels;
	// return SystemHistoryRepaTuple(move(uu), move(ur), move(hr));
// }


// // testBucketedIO :: Int -> IO (System, HistoryRepa)
// SystemHistoryRepaTuple M5FA::testBucketedIO(int d)
// {
	// auto lluu = listsSystem_u;
	// auto uuur = systemsSystemRepa;

	// const int a = 28;
	// const int z = 10000;
	// unsigned char* images = new unsigned char[z*a*a];
	// unsigned char* labels = new unsigned char[z];
	// try
	// {
		// ifstream fimages("t10k-images-idx3-ubyte", ios::binary);
		// ifstream flabels("t10k-labels-idx1-ubyte", ios::binary);
		// if (!fimages.is_open() || !flabels.is_open())
		// {
			// cout << "testBucketedIO : cannot open files" << endl;
			// delete[] images;
			// delete[] labels;
			// return SystemHistoryRepaTuple();
		// }
		// fimages.read((char*)images, 16);
		// fimages.read((char*)images, z*a*a);
		// fimages.close();
		// flabels.read((char*)labels, 8);
		// flabels.read((char*)labels, z);
		// flabels.close();
	// }
	// catch (const exception& e)
	// {
		// cout << "testBucketedIO : " << e.what() << endl;
		// delete[] images;
		// delete[] labels;
		// return SystemHistoryRepaTuple();
	// }
	// ValSet digits;
	// for (int i = 0; i < 10; i++)
		// digits.insert(Value(i));
	// ValSet buckets;
	// for (int i = 0; i < d; i++)
		// buckets.insert(Value(i));
	// vector<VarValSetPair> ll;
	// ll.push_back(VarValSetPair(Variable("digit"), digits));
	// for (int i = 0; i < a; i++)
		// for (int j = 0; j < a; j++)
			// ll.push_back(VarValSetPair(Variable(Variable(i + 1), Variable(j + 1)), buckets));
	// auto uu = lluu(ll);
	// auto ur = uuur(*uu);
	// auto hr = make_unique<HistoryRepa>();
	// hr->dimension = a*a + 1;
	// auto n = hr->dimension;
	// hr->vectorVar = new size_t[n];
	// auto vv = hr->vectorVar;
	// hr->shape = new size_t[n];
	// auto sh = hr->shape;
	// hr->size = z;
	// hr->evient = true;
	// hr->arr = new unsigned char[z*n];
	// auto rr = hr->arr;
	// for (size_t i = 0; i < n; i++)
		// vv[i] = i;
	// sh[0] = 10;
	// for (size_t i = 1; i < n; i++)
		// sh[i] = d;
	// size_t k = 0;
	// for (size_t j = 0; j < z; j++)
	// {
		// size_t jn = j*n;
		// rr[jn] = labels[j];
		// for (size_t i = 1; i < n; i++)
		// {
			// rr[jn + i] = images[k] * d / 256;
			// k++;
		// }
	// }
	// hr->transpose();
	// delete[] images;
	// delete[] labels;
	// return SystemHistoryRepaTuple(move(uu), move(ur), move(hr));
// }


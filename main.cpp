#include "dev.h"

using namespace Alignment;
using namespace M5FA;
using namespace std;

typedef std::chrono::duration<double> sec; 
typedef std::chrono::high_resolution_clock clk;

#define ECHO(x) cout << #x << endl; x
#define EVAL(x) cout << #x << ": " << (x) << endl
#define EVALL(x) cout << #x << ": " << endl << (x) << endl
#define TRUTH(x) cout << #x << ": " << ((x) ? "true" : "false") << endl

int main(int argc, char **argv)
{
	if (argc == 2 && string(argv[1]) == "sales")
	{
		auto records = recordSalesListIO();
		EVAL(*records);
	}

	if (argc >= 3 && string(argv[1]) == "sales_buckets")
	{
		int bucketMax = 0;
		int buckets = atoi(argv[2]);
		auto records = recordSalesListIO();
		RecordSalesList records1;
		for (auto& record : *records)
		{ 
			RecordSales record1(record);
			record1.d.clear();
			std::sort(record.d.begin(), record.d.end());
			record1.d.push_back(record.d.front());
			for (int i = 0; i < buckets; i++)
				record1.d.push_back(record.d[i * record.d.size() / buckets]);
			record1.d.push_back(record.d.back());
			if (record.d.back() > bucketMax)
				bucketMax = record.d.back();
			auto last = std::unique(record1.d.begin(), record1.d.end());
			record1.d.erase(last, record1.d.end());
			records1.push_back(record1);
		}
		EVAL(bucketMax);
		EVAL(records1);
	}

	if (argc == 2 && string(argv[1]) == "sales_counts")
	{
		auto records = recordSalesListIO();
		std::map<std::pair<std::string, std::string>, int> map1;
		for (auto& record : *records)
		{
			map1[std::pair<std::string, std::string>(record.store_id, record.dept_id)]++;
		}
		for (auto p : map1)
			std::cout << p.first.first << "," << p.first.second << ": " << p.second << endl;
	}

	if (argc == 2 && string(argv[1]) == "sales_counts2")
	{
		auto records = recordSalesListIO();
		std::map<std::pair<std::string, std::string>, int> map1;
		for (auto& record : *records)
		{
			map1[std::pair<std::string, std::string>(record.cat_id, record.store_id)]++;
		}
		for (auto p : map1)
			std::cout << p.first.first << "," << p.first.second << ": " << p.second << endl;
	}

	if (argc >= 4 && string(argv[1]) == "view_category_store")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};

		string cat_id = string(argv[2]);
		string store_id = string(argv[3]);

		auto xx = trainBucketedCategoryStoreIO(10, cat_id, store_id);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		EVAL(sorted(*uvars(*uu)));

		EVAL(hr->dimension);
		EVAL(hr->size);
		EVAL(*hrsel(*hr, SizeList{0}));
	}

	if (argc >= 5 && string(argv[1]) == "induce_category_store")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		string model = string(argv[2]);
		string cat_id = string(argv[3]);
		string store_id = string(argv[4]);
		size_t scale = argc >= 6 ? atoi(argv[5]) : 1;

		auto xx = trainBucketedCategoryStoreIO(10, cat_id, store_id);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr0 = std::get<2>(xx);

		auto vv = *uvars(*uu);
		
		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t j = 0; j < scale; j++)
				for (size_t i = 0; i < hr0->size; i++)
					ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hr0);
		}

		EVAL(hr->dimension);
		EVAL(hr->size);

		auto& vvi = ur->mapVarSize();
		auto vv0 = sorted(vv);
		SizeList vv1;
		for (auto& v : vv0)
			vv1.push_back(vvi[v]);

		size_t wmax = 18;
		size_t lmax = 8;
		size_t xmax = 128;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 127;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vv1, *hr, *ur);
		std::ofstream out(model+".bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();
		EVAL(treesSize(*dr->slices));
		EVAL(frder(*dr->fud)->size());
		EVAL(frund(*dr->fud)->size());
		EVAL(frvars(*dr->fud)->size());
	}
	
	if (argc >= 5 && string(argv[1]) == "induce_category_store2")
	{
		auto uvars = systemsSetVar;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		string model = string(argv[2]);
		string cat_id = string(argv[3]);
		string store_id = string(argv[4]);

		auto xx = trainBucketedCategoryStoreIO(10, cat_id, store_id);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		auto vv = *uvars(*uu);

		EVAL(hr->dimension);
		EVAL(hr->size);

		auto& vvi = ur->mapVarSize();
		auto vv0 = sorted(vv);
		SizeList vv1;
		for (auto& v : vv0)
			vv1.push_back(vvi[v]);

		size_t wmax = 18;
		size_t lmax = 20;
		size_t xmax = 128 * 8;
		size_t omax = 30;
		size_t bmax = 30 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 127;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vv1, *hr, *ur);
		std::ofstream out(model+".bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();
		EVAL(treesSize(*dr->slices));
		EVAL(frder(*dr->fud)->size());
		EVAL(frund(*dr->fud)->size());
		EVAL(frvars(*dr->fud)->size());
	}
	
	if (argc >= 5 && string(argv[1]) == "induce_category_store3")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		string model = string(argv[2]);
		string cat_id = string(argv[3]);
		string store_id = string(argv[4]);
		size_t scale = argc >= 6 ? atoi(argv[5]) : 1;

		auto xx = trainBucketedCategoryStoreIO(10, cat_id, store_id);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr0 = std::get<2>(xx);

		auto vv = *uvars(*uu);
		
		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t j = 0; j < scale; j++)
				for (size_t i = 0; i < hr0->size; i++)
					ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hr0);
		}

		EVAL(hr->dimension);
		EVAL(hr->size);

		auto& vvi = ur->mapVarSize();
		auto vv0 = sorted(vv);
		SizeList vv1;
		for (auto& v : vv0)
			vv1.push_back(vvi[v]);

		size_t wmax = 18;
		size_t lmax = 8;
		size_t xmax = 128;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 1914;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vv1, *hr, *ur);
		std::ofstream out(model+".bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();
		EVAL(treesSize(*dr->slices));
		EVAL(frder(*dr->fud)->size());
		EVAL(frund(*dr->fud)->size());
		EVAL(frvars(*dr->fud)->size());
	}

	if (argc >= 5 && string(argv[1]) == "induce_category_store4")
	{
		auto uvars = systemsSetVar;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		string model = string(argv[2]);
		string cat_id = string(argv[3]);
		string store_id = string(argv[4]);

		auto xx = trainBucketedCategoryStoreIO(20, cat_id, store_id);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		auto vv = *uvars(*uu);

		EVAL(hr->dimension);
		EVAL(hr->size);

		auto& vvi = ur->mapVarSize();
		auto vv0 = sorted(vv);
		SizeList vv1;
		for (auto& v : vv0)
			vv1.push_back(vvi[v]);

		size_t wmax = 18;
		size_t lmax = 20;
		size_t xmax = 128 * 8;
		size_t omax = 30;
		size_t bmax = 30 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 127;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vv1, *hr, *ur);
		std::ofstream out(model+".bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();
		EVAL(treesSize(*dr->slices));
		EVAL(frder(*dr->fud)->size());
		EVAL(frund(*dr->fud)->size());
		EVAL(frvars(*dr->fud)->size());
	}
	if (argc >= 5 && string(argv[1]) == "model_error_category_store")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		
		string model = string(argv[2]);
		string cat_id = string(argv[3]);
		string store_id = string(argv[4]);
		size_t scale = argc >= 6 ? atoi(argv[5]) : 1;

		auto xx = trainBucketedCategoryStoreIO(10, cat_id, store_id);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr0 = std::get<2>(xx);
		auto& records = std::get<3>(xx);

		auto vv = *uvars(*uu);
		
		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t j = 0; j < scale; j++)
				for (size_t i = 0; i < hr0->size; i++)
					ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hr0);
		}

		EVAL(hr->dimension);
		EVAL(hr->size);

		auto& vvi = ur->mapVarSize();
		auto vv0 = sorted(vv);
		SizeList vv1;
		for (auto& v : vv0)
			vv1.push_back(vvi[v]);
		
		StrVarPtrMap m;
		std::ifstream in(model+".bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		EVAL(treesSize(*dr->slices));
		EVAL(treesLeafElements(*dr->slices)->size());
		EVAL(frder(*dr->fud)->size());
		EVAL(frund(*dr->fud)->size());
		EVAL(frvars(*dr->fud)->size());

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesLeafElements(*dr->slices);
		std::map<std::size_t, SizeList> slevs;
		std::vector<std::size_t> evsl;
		evsl.reserve(z);
		for (auto s : *sl)
		{
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
				{
					slevs[s].push_back(j);
					evsl.push_back(s);
				}
			}
		}
//		EVAL(slevs);
//		EVAL(evsl);
		std::vector<double> daily_error;
		for (auto& record : *records)
		{
			double e = 0.0; 
			for (std::size_t j = 0; j < z/scale-1; j++)
				e += (record.d[j+1] - record.d[j])*(record.d[j+1] - record.d[j]);
			e /= z/scale-1;
			daily_error.push_back(std::sqrt(e));
		}
		std::vector<double> slice_error;
		for (auto& record : *records)
		{
			double e = 0.0; 
			for (std::size_t j = 0; j < z; j++)
			{
				double a = 0.0;
				auto ll = slevs[evsl[j]];
				for (auto k : ll)
					a += record.d[k % (z/scale)];
				a /= ll.size();
				e += (record.d[j % (z/scale)] - a)*(record.d[j % (z/scale)] - a);
			}
			e /= z;
			slice_error.push_back(std::sqrt(e));
		}
		auto err = 0.0;
		for (std::size_t i = 0; i < records->size(); i++)
		{
			std::cout << (*records)[i].id << ":\t" << slice_error[i] << "\t" << daily_error[i] << "\t" << slice_error[i]/daily_error[i] << std::endl;
			err += slice_error[i]/daily_error[i];
		}
		err /= records->size();
		EVAL(err);
	}

	return 0;
}

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
	
	if (argc >= 6 && string(argv[1]) == "condition_category_store")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrjoin = vectorHistoryRepasJoin_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialMultiLabelFmaxIORepa_u;
		
		string modelin = string(argv[2]);
		string model = string(argv[3]);
		string cat_id = string(argv[4]);
		string store_id = string(argv[5]);
		size_t nmul = argc >= 7 ? atoi(argv[6]) : 1;
		size_t fmax = argc >= 8 ? atoi(argv[7]) : 1;

		std::unique_ptr<HistoryRepa> hr;
		{
			auto xx = trainBucketedCategoryStoreIO(10, cat_id, store_id);
			hr = std::move(std::get<2>(xx));
		}

		std::unique_ptr<SystemRepa> ur;
		std::unique_ptr<ApplicationRepa> dr;
		{
			StrVarPtrMap m;
			std::ifstream in(modelin+".bin", std::ios::binary);
			ur = persistentsSystemRepa(in, m);
			dr = persistentsApplicationRepa(in);
			in.close();
		}
		auto& llu = ur->listVarSizePair;
		
		auto ur1 = std::make_unique<SystemRepa>();
		auto& llu1 = ur1->listVarSizePair;	
		std::unique_ptr<HistoryRepa> hr1;
		std::vector<std::shared_ptr<ApplicationRepa>> lld;
		{
			auto n = hr->dimension;
			auto vv = hr->vectorVar;
			auto z = hr->size;
			HistoryRepaPtrList llh;
			for (size_t k = 0; k < nmul; k++)
			{
				auto vk = std::make_shared<Variable>((int)k);
				SizeSizeUMap nn;
				nn.reserve(n);
				for (std::size_t i = 0; i < n; i++)
				{
					auto x = vv[i];
					auto& p = llu[x];
					auto v = std::make_shared<Variable>(vk, p.first);
					llu1.push_back(VarSizePair(v, p.second));
					nn[x] = llu1.size() - 1;
				}
				SizeList ll;
				for (size_t j = nmul-1-k; j < z-k; j++)
					ll.push_back(j);
				auto hr0 = hrsel(ll.size(), ll.data(), *hr);
				hr0->reframe_u(nn);
				llh.push_back(std::move(hr0));
				auto dr0 = drcopy(*dr);
				for (auto& ll : dr->fud->layers)
					for (auto& tr : ll)
					{
						auto& p = llu[tr->derived];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vk, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu1.push_back(VarSizePair(vdflb1, p.second));
						nn[tr->derived] = llu1.size() - 1;
					}
				dr0->reframe_u(nn);
				lld.push_back(std::move(dr0));
			}
			hr1 = hrjoin(llh);
		}
		
		EVAL(hr1->dimension);
		EVAL(hr1->size);
		
		ApplicationRepa dr1;
		{
			dr1.slices = std::make_shared<SizeTree>();
			dr1.slices->_list.reserve(dr->slices->_list.size() * nmul);
			dr1.fud = std::make_shared<FudRepa>();
			dr1.fud->layers.reserve(dr->fud->layers.size());
			dr1.substrate.reserve(dr->substrate.size() * nmul);
			for (auto& dr0 : lld)
			{
				dr1.slices->_list.insert(dr1.slices->_list.end(), dr0->slices->_list.begin(), dr0->slices->_list.end());
				dr1.fud->layers.insert(dr1.fud->layers.end(), dr0->fud->layers.begin(), dr0->fud->layers.end());
				dr1.substrate.insert(dr1.substrate.end(), dr0->substrate.begin(), dr0->substrate.end());
			}
		}
		EVAL(treesSize(*dr1.slices));
		EVAL(treesLeafElements(*dr1.slices)->size());
		EVAL(frder(*dr1.fud)->size());
		EVAL(frund(*dr1.fud)->size());
		EVAL(frvars(*dr1.fud)->size());	
		
		auto hr2 = frmul(*hr1, *dr1.fud);

		EVAL(hr2->dimension);
		EVAL(hr2->size);
		
		SizeList vvk;
		{
			for (std::size_t i = 1; i < lld.size(); i++)
			{
				auto sl = treesElements(*lld[i]->slices);
				vvk.insert(vvk.end(), sl->begin(), sl->end());
			}
		}
		SizeList vvl;
		{
			auto sl = treesLeafElements(*lld[0]->slices);
			auto m = sl->size();
			auto z = hr2->size;
			auto& mvv2 = hr2->mapVarInt();
			SizeList pvv2;
			for (auto v : *sl)
				pvv2.push_back(mvv2[v]);
			auto hr3 = std::make_unique<HistoryRepa>();
			std::size_t n3 = 2;
			std::size_t s0 = (m-1)/256 + 1;
			std::size_t s1 = m > 256 ? 256 : m;
			llu1.push_back(VarSizePair(std::make_shared<Variable>("slices00"), s0));
			llu1.push_back(VarSizePair(std::make_shared<Variable>("slices01"), s1));
			std::size_t v0 = llu1.size() - 2;
			std::size_t v1 = llu1.size() - 1;
			vvl.push_back(v0);
			vvl.push_back(v1);
			hr3->dimension = n3;
			hr3->vectorVar = new std::size_t[n3];
			auto vv3 = hr3->vectorVar;
			hr3->shape = new std::size_t[n3];
			auto sh3 = hr3->shape;
			vv3[0] = v0;
			sh3[0] = s0;
			vv3[1] = v1;
			sh3[1] = s1;
			hr3->size = z;
			hr3->evient = false;
			hr3->arr = new unsigned char[z*n3];
			auto rr2 = hr2->arr;
			auto rr3 = hr3->arr;
			for (std::size_t j = 0; j < z; j++)
				for (std::size_t i = 0; i < m; i++)
				{
					std::size_t u = rr2[pvv2[i]*z + j];
					if (u)
					{
						rr3[j] = (unsigned char)(i/256);
						rr3[z+j] = (unsigned char)(i%256);
						break;
					}
				}
			// EVAL(*hr3);
			HistoryRepaPtrList llh;
			llh.push_back(std::move(hr2));
			llh.push_back(std::move(hr3));
			hr2 = hrjoin(llh);
		}
	
		auto dr2 = applicationer(fmax, vvk, vvl, *hr2, nmul+1, *ur1);
		auto dr3 = drjoin(dr1, *dr2);
		std::ofstream out(model+".bin", std::ios::binary);
		systemRepasPersistent(*ur1, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		EVAL(treesSize(*dr3->slices));
		EVAL(treesLeafElements(*dr3->slices)->size());
		EVAL(frder(*dr3->fud)->size());
		EVAL(frund(*dr3->fud)->size());
		EVAL(frvars(*dr3->fud)->size());

	}
	
		if (argc >= 5 && string(argv[1]) == "entropy")
	{
		auto uvars = systemsSetVar;
		auto uruu = systemsRepasSystem;
		auto aall = histogramsList;
		auto add = pairHistogramsAdd_u;
		auto ent = histogramsEntropy;
		auto araa = systemsHistogramRepasHistogram_u;
		auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarList& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			SizeList kk1;
			for (std::size_t i = 0; i < m; i++)
				kk1.push_back(vvi[kk[i]]);
			return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
		};
		auto hrconcat = vectorHistoryRepasConcat_u;
		auto hrshuffle = historyRepasShuffle_u;
		auto hrpart = systemsHistoryRepasApplicationsHistoryHistoryPartitionedRepa_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		
		string model = string(argv[2]);
		string cat_id = string(argv[3]);
		string store_id = string(argv[4]);
		size_t mult = argc >= 6 ? atoi(argv[5]) : 1;
		
		EVAL(model);
		EVAL(mult);

		std::unique_ptr<System> uu;
		std::unique_ptr<SystemRepa> ur;
		std::unique_ptr<HistoryRepa> hr;
		{
			auto xx = trainBucketedCategoryStoreIO(10, cat_id, store_id);
			uu = std::move(std::get<0>(xx));
			ur = std::move(std::get<1>(xx));
			hr = std::move(std::get<2>(xx));
		}

		ECHO(double z = hr->size);
		EVAL(z);
		ECHO(double v = z * mult);
		EVAL(v);
		
		StrVarPtrMap m;
		std::ifstream in(model + ".bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		EVAL(fudRepasSize(*dr->fud));
		EVAL(frder(*dr->fud)->size());
		EVAL(frund(*dr->fud)->size());
		EVAL(treesSize(*dr->slices));
		ECHO(auto d = treesLeafElements(*dr->slices)->size());
		EVAL(d);

		auto hrp = hrpart(*hr, *dr, *ur);
		// EVAL(*hrp);
		uruu(*ur, *uu);
		// EVAL(*uu);
		auto aa = araa(*uu, *ur, *hrred(*hrp, *ur, VarList{ Variable("partition0"), Variable("partition1") }));
		// EVAL(*aa);
		EVAL(ent(*aa));
		EVAL(ent(*aa) * z);
		EVAL((1.0-exp(ent(*aa))/d)*100.0);
		
		HistoryRepaPtrList qq;
		qq.reserve(mult);
		for (std::size_t i = 1; i <= mult; i++)
			qq.push_back(hrshuffle(*hr, (unsigned int)(12345+i*z)));
		auto hrs = hrconcat(qq);
		
		auto hrsp = hrpart(*hrs, *dr, *ur);
		auto bb = araa(*uu, *ur, *hrred(*hrsp, *ur, VarList{ Variable("partition0"), Variable("partition1") }));
		EVAL(ent(*bb));
		EVAL(ent(*bb) * v);
		EVAL((1.0-exp(ent(*bb))/d)*100.0);
		
		auto cc = add(*aa,*bb);
		
		EVAL(ent(*cc));
		EVAL(ent(*cc) * (z+v));
		EVAL((1.0-exp(ent(*cc))/d)*100.0);
		
		EVAL((ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v)/z);
		EVAL(ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v);
		EVAL(exp((ent(*cc) * (z+v) - ent(*aa) * z - ent(*bb) * v)/z)/d*100.0);
	}

	return 0;
}

#include "dev.h"

using namespace Alignment;
using namespace M5FA;
using namespace std;

typedef std::chrono::duration<double> sec; 
typedef std::chrono::high_resolution_clock clk;

int main(int argc, char **argv)
{
	if (false)
	{
		const int a = 28;
		const int z = 60000;
		unsigned char* images = new unsigned char[z*a*a];
		unsigned char* labels = new unsigned char[z];
		try
		{
			ifstream fimages("train-images-idx3-ubyte", ios::binary);
			fimages.read((char*)images, 16);
			fimages.read((char*)images, z*a*a);
			fimages.close();
			ifstream flabels("train-labels-idx1-ubyte", ios::binary);
			flabels.read((char*)labels, 8);
			flabels.read((char*)labels, z);
			flabels.close();
		}
		catch (const std::exception& e)
		{
			cout << "trainBucketedIO : " << e.what() << endl << endl;
		}
		map<int, int> mm;
		for (int i = 0; i < z; i++)
			mm[labels[i]] += 1;
		cout << mm << endl;
		map<int, int> nn;
		for (int i = 0; i < z*a*a; i++)
			nn[images[i]] += 1;
		cout << nn << endl;
		delete[] images;
		delete[] labels;
	}

	if (false)
	{
		auto lluu = listsSystem_u;
		auto uuur = systemsSystemRepa;

		int d = 2;

		const int a = 28;
		const int z = 60000;
		ValSet digits;
		for (int i = 0; i < 10; i++)
			digits.insert(Value(i));
		ValSet buckets;
		for (int i = 0; i < d; i++)
			buckets.insert(Value(i));
		std::vector<VarValSetPair> ll;
		ll.push_back(VarValSetPair(Variable("digit"), digits));
		for (int i = 0; i < a; i++)
			for (int j = 0; j < a; j++)
				ll.push_back(VarValSetPair(Variable(Variable(i + 1), Variable(j + 1)), buckets));
		auto uu = lluu(ll);
		auto ur = uuur(*uu);
		cout << "uu" << endl
			<< *uu << endl << endl;
		cout << "ur" << endl
			<< *ur << endl << endl;
	}

	if (false)
	{
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};

		auto xx = trainBucketedIO(2);
		auto uu = std::move(std::get<0>(xx));
		auto ur = std::move(std::get<1>(xx));
		auto hr = std::move(std::get<2>(xx));
		cout << "uu" << endl
			<< *uu << endl << endl;
		cout << "ur" << endl
			<< *ur << endl << endl;
		cout << "hrsel(hr,SizeList{0})" << endl
			<< *hrsel(*hr, SizeList{ 0 }) << endl << endl;
	}

	if (false)
	{
		Bitmap bm(341,753);
		for (int i = 0; i <bm.height; i++) {
			for (int j = 0; j< bm.width; j++) {
				bm.image[i*bm.width * 3 + j * 3 + 2] = (unsigned char)((double)i / bm.height * 255); ///red
				bm.image[i*bm.width * 3 + j * 3 + 1] = (unsigned char)((double)j / bm.width * 255); ///green
				bm.image[i*bm.width * 3 + j * 3 + 0] = (unsigned char)(((double)i + j) / (bm.height + bm.width) * 255); ///blue
			}
		}
		bmwrite("M5FA.bmp", bm);
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
		};

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		set<size_t> ww;
		for (auto& w : vvk)
			ww.insert(vol(*uu, VarUSet{ w }));
		cout << "ww" << endl
			<< ww << endl << endl;

		cout << "vol(uu,vvl)" << endl
			<< vol(*uu, vvl) << endl << endl;

		cout << "rpln(aall(araa(uu,hrred(hr,vvl))))" << endl;
		rpln(cout, sorted(*aall(*araa(*uu, *ur, *hrred(*hr, *ur, vvl))))); cout << endl;

		cout << "hrsel(hr,SizeList{0})" << endl
			<< *hrsel(*hr, SizeList{ 0 }) << endl << endl;

		auto hr1 = hrhrred(*hr, *ur, vvk);
		auto bm = hrbm(28, 1, 2, *hrsel(*hr1, SizeList{ 0 }));
		cout << "bm.height" << endl
			<< bm.height << endl << endl;
		cout << "bm.width" << endl
			<< bm.width << endl << endl;
		cout << "bm.image.size()" << endl
			<< bm.image.size() << endl << endl;
		cout << "bm.image" << endl;
		for (std::size_t i = 0; i < bm.image.size(); i += 3)
		{
			if (i) cout << ",";
			cout << "[" << (int)bm.image[i] << "," << (int)bm.image[i+1] << "," << (int)bm.image[i+2] << "]";
		}
		bmwrite("M5FA.bmp", bm);
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
		};

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		set<size_t> ww;
		for (auto& w : vvk)
			ww.insert(vol(*uu, VarUSet{ w }));
		cout << "ww" << endl
			<< ww << endl << endl;

		cout << "vol(uu,vvl)" << endl
			<< vol(*uu, vvl) << endl << endl;

		cout << "rpln(aall(araa(uu,hrred(hr,vvl))))" << endl;
		rpln(cout, sorted(*aall(*araa(*uu, *ur, *hrred(*hr, *ur, vvl))))); cout << endl;

		auto hr1 = hrhrred(*hr, *ur, vvk);

		{
			std::vector<Bitmap> bms;
			for (size_t i = 0; i < 25; i++)
				bms.push_back(bmborder(1,hrbm(28, 1, 2, *hrsel(*hr1, SizeList{i}))));
			bmwrite("M5FA01.bmp", bmhstack(bms));
		}

		auto hrbmav = hrbm(28, 3, 2, *hr1);
		bmwrite("M5FA02.bmp", hrbmav);

		{
			std::vector<Bitmap> bms;
			for (auto ss : sorted(*cart(*uu, vvl)))
				bms.push_back(bmborder(1, hrbm(28, 2, 2, *hrhrred(*hrhrsel(*hr, *aahr(*uu, *ur, *single(ss, 1))), *ur, vvk))));
			bmwrite("M5FA03.bmp", bmhstack(bms));
		}

		auto hrr = historyRepasShuffle_u(*hr, 1);

		bmwrite("M5FA04.bmp", hrbm(28, 3, 2, *hrhrred(*hrr, *ur, vvk)));

		{
			auto hrr1 = hrhrred(*hrr, *ur, vvk);
			std::vector<Bitmap> bms;
			for (size_t i = 0; i < 25; i++)
				bms.push_back(bmborder(1, hrbm(28, 1, 2, *hrsel(*hrr1, SizeList{ i }))));
			bmwrite("M5FA05.bmp", bmhstack(bms));
		}

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
		};
		auto hrcross = [](std::size_t xmax, std::size_t omax, const HistoryRepa& hr, const HistoryRepa& hrs, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			auto pr = historyRepasRed(hr);
			auto prs = historyRepasRed(hrs);
			auto xx = parametersSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, kk1, hr, *pr, hrs, *prs);
			std::vector<std::pair<double, VarList>> ll;
			auto tt = sorted(*std::get<0>(xx));
			for (auto& mm : tt)
			{
				VarList ll1;
				for (auto& i : mm.second)
					ll1.push_back(*(ur.listVarSizePair[i]).first);
				ll.push_back(std::pair<double, VarList>(mm.first,ll1));
			}
			return ll;
		};

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		{
			auto start = chrono::system_clock::now();
			auto hrr = historyRepasShuffle_u(*hr, 1);
			auto end = chrono::system_clock::now();
			cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto ll = hrcross(100, 10, *hr, *hrr, *ur, vvk);
			end = chrono::system_clock::now();
			cout << "hrcross " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			cout << "ll" << endl;
			for (auto& mm : ll)
				cout << mm.first << "," << mm.second << endl;
			/*
			historyRepasShuffle_u 0.218406s
			hrcross 13.8532s
			ll
			2123.91,[<24,12>,<24,13>]
			2123.98,[<17,20>,<18,20>]
			2130.76,[<15,9>,<16,9>]
			2132.73,[<12,10>,<13,10>]
			2134.58,[<23,12>,<23,13>]
			2136.53,[<23,11>,<23,12>]
			2172.46,[<12,9>,<13,9>]
			2187.93,[<14,8>,<15,8>]
			2234.01,[<14,9>,<15,9>]
			2292.43,[<13,9>,<14,9>]
			*/
		}

		{
			auto start = chrono::system_clock::now();
			hr->transpose();
			auto end = chrono::system_clock::now();
			cout << "transpose " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto hrr = historyRepasShuffle_u(*hr, 1);
			end = chrono::system_clock::now();
			cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto ll = hrcross(100, 10, *hr, *hrr, *ur, vvk);
			end = chrono::system_clock::now();
			cout << "hrcross " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			cout << "ll" << endl;
			for (auto& mm : ll)
				cout << mm.first << "," << mm.second << endl;
			/*
			transpose 0.0312008s
			historyRepasShuffle_u 0.37441s
			hrcross 98.8129s
			ll
			2123.2,[<24,12>,<24,13>]
			2123.24,[<17,20>,<18,20>]
			2130.83,[<15,9>,<16,9>]
			2132.78,[<12,10>,<13,10>]
			2134.47,[<23,12>,<23,13>]
			2138.44,[<23,11>,<23,12>]
			2172.53,[<12,9>,<13,9>]
			2187.68,[<14,8>,<15,8>]
			2234.05,[<14,9>,<15,9>]
			2291.64,[<13,9>,<14,9>]
			*/
		}
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
		};

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t xmax = 4096;
		size_t omax = 10;
		{
			auto start = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			auto end = chrono::system_clock::now();
			cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto pr = historyRepasRed(*hr);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto prs = historyRepasRed(*hrs);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto xx = parametersSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, vvk1, *hr, *pr, *hrs, *prs);
			end = chrono::system_clock::now();
			cout << "hrcross " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			auto xc = std::move(std::get<0>(xx));
			auto sc = std::get<1>(xx);
			cout << "steps: " << sc << endl;
			auto tt = sorted(*xc);
			for (auto& mm : tt)
			{
				cout << mm.first << ", ";
				VarList ll1;
				for (auto& i : mm.second)
					ll1.push_back(*(ur->listVarSizePair[i]).first);
				cout << ll1 << endl;
			}

			SizeListList vdd;
			for (auto& mm : *xc)
				vdd.push_back(mm.second);

			start = chrono::system_clock::now();
			xx = parametersSetVarsSetSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, vvk1, vdd, *hr, *pr, *hrs, *prs);
			end = chrono::system_clock::now();
			cout << "hrappend " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			xc = std::move(std::get<0>(xx));
			sc = std::get<1>(xx);
			cout << "steps: " << sc << endl;
			tt = sorted(*xc);
			for (auto& mm : tt)
			{
				cout << mm.first << ", ";
				VarList ll1;
				for (auto& i : mm.second)
					ll1.push_back(*(ur->listVarSizePair[i]).first);
				cout << ll1 << endl;
			}
			/*
			historyRepasShuffle_u 0.234003s
			historyRepasRed(hr) 0.0156002s
			historyRepasRed(hrs) 0.0156002s
			hrcross 13.9778s
			steps: 306936
			2123.91, [<24,12>,<24,13>]
			2123.98, [<17,20>,<18,20>]
			2130.76, [<15,9>,<16,9>]
			2132.73, [<12,10>,<13,10>]
			2134.58, [<23,12>,<23,13>]
			2136.53, [<23,11>,<23,12>]
			2172.46, [<12,9>,<13,9>]
			2187.93, [<14,8>,<15,8>]
			2234.01, [<14,9>,<15,9>]
			2292.43, [<13,9>,<14,9>]
			hrappend 0.81121s
			steps: 7820
			4175.65, [<23,9>,<23,11>,<23,12>]
			4181.65, [<11,8>,<12,9>,<13,9>]
			4201.86, [<19,19>,<17,20>,<18,20>]
			4260.35, [<16,7>,<14,8>,<15,8>]
			4268.39, [<14,9>,<12,10>,<13,10>]
			4275.66, [<13,7>,<14,8>,<15,8>]
			4297.26, [<23,10>,<23,12>,<23,13>]
			4383.27, [<14,8>,<15,9>,<16,9>]
			4476.49, [<12,8>,<13,9>,<14,9>]
			4542.22, [<13,8>,<14,9>,<15,9>]
			*/
		}

		{
			auto start = chrono::system_clock::now();
			hr->transpose();
			auto end = chrono::system_clock::now();
			cout << "transpose " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			end = chrono::system_clock::now();
			cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto pr = historyRepasRed(*hr);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto prs = historyRepasRed(*hrs);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto xx = parametersSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, vvk1, *hr, *pr, *hrs, *prs);
			end = chrono::system_clock::now();
			cout << "hrcross " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			auto xc = std::move(std::get<0>(xx));
			auto sc = std::get<1>(xx);
			cout << "steps: " << sc << endl;
			auto tt = sorted(*xc);
			for (auto& mm : tt)
			{
				cout << mm.first << ", ";
				VarList ll1;
				for (auto& i : mm.second)
					ll1.push_back(*(ur->listVarSizePair[i]).first);
				cout << ll1 << endl;
			}

			SizeListList vdd;
			for (auto& mm : *xc)
				vdd.push_back(mm.second);

			start = chrono::system_clock::now();
			xx = parametersSetVarsSetSetVarsHistoryRepasSetSetVarsAlignedTop_u(xmax, omax, vvk1, vdd, *hr, *pr, *hrs, *prs);
			end = chrono::system_clock::now();
			cout << "hrappend " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			xc = std::move(std::get<0>(xx));
			sc = std::get<1>(xx);
			cout << "steps: " << sc << endl;
			tt = sorted(*xc);
			for (auto& mm : tt)
			{
				cout << mm.first << ", ";
				VarList ll1;
				for (auto& i : mm.second)
					ll1.push_back(*(ur->listVarSizePair[i]).first);
				cout << ll1 << endl;
			}
			/*
			transpose 0.0312004s
			historyRepasShuffle_u 0.390005s
			historyRepasRed(hr) 0s
			historyRepasRed(hrs) 0s
			hrcross 104.007s
			steps: 306936
			2123.2, [<24,12>,<24,13>]
			2123.24, [<17,20>,<18,20>]
			2130.83, [<15,9>,<16,9>]
			2132.78, [<12,10>,<13,10>]
			2134.47, [<23,12>,<23,13>]
			2138.44, [<23,11>,<23,12>]
			2172.53, [<12,9>,<13,9>]
			2187.68, [<14,8>,<15,8>]
			2234.05, [<14,9>,<15,9>]
			2291.64, [<13,9>,<14,9>]
			hrappend 6.06848s
			steps: 7820
			4178.08, [<23,9>,<23,11>,<23,12>]
			4181.29, [<11,8>,<12,9>,<13,9>]
			4202.66, [<19,19>,<17,20>,<18,20>]
			4260.41, [<16,7>,<14,8>,<15,8>]
			4269.11, [<14,9>,<12,10>,<13,10>]
			4275.52, [<13,7>,<14,8>,<15,8>]
			4298.27, [<23,10>,<23,12>,<23,13>]
			4383.27, [<14,8>,<15,9>,<16,9>]
			4475.37, [<12,8>,<13,9>,<14,9>]
			4543.04, [<13,8>,<14,9>,<15,9>]
			*/
		}
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto ind = histogramsIndependent;
		auto algn = histogramsAlignment;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto arpr = histogramRepasRed;
		auto prar = histogramRepaRedsIndependent;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
		{
			return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
		{
			return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
		};
		auto hrpr = historyRepasRed;
		auto aralgn = [](const HistogramRepa& ar)
		{
			auto ax = histogramRepaRedsIndependent(ar.size(),*histogramRepasRed(ar.size(),ar));
			return ar.facLn() - ax->facLn();
		};

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t xmax = 4096;
		size_t omax = 10;
		size_t bmax = 10;
		size_t mmax = 1;
		{
			auto start = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			auto end = chrono::system_clock::now();
			cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto pr = historyRepasRed(*hr);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto prs = historyRepasRed(*hrs);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto t = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
			end = chrono::system_clock::now();
			cout << "buildtup " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			auto xx = std::move(std::get<0>(t));
			auto s = std::get<1>(t);
			cout << "steps: " << s << endl;
			for (auto& kk : *xx)
			{
				cout << aralgn(*hrred(*hr, kk)) - aralgn(*hrred(*hrs, kk)) << ",";
				VarSet qq;
				for (std::size_t i = 0; i < kk.size(); i++)
					qq.insert(*(ur->listVarSizePair[kk[i]]).first);
				cout << qq << endl;
			}
		}

		{
			auto start = chrono::system_clock::now();
			hr->transpose();
			auto end = chrono::system_clock::now();
			cout << "transpose " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			end = chrono::system_clock::now();
			cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto pr = historyRepasRed(*hr);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto prs = historyRepasRed(*hrs);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto t = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
			end = chrono::system_clock::now();
			cout << "buildtup " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			auto xx = std::move(std::get<0>(t));
			auto s = std::get<1>(t);
			cout << "steps: " << s << endl;
			for (auto& kk : *xx)
			{
				cout << aralgn(*hrred(*hr, kk)) - aralgn(*hrred(*hrs, kk)) << ",";
				VarSet qq;
				for (std::size_t i = 0; i < kk.size(); i++)
					qq.insert(*(ur->listVarSizePair[kk[i]]).first);
				cout << qq << endl;
			}
		}
		/*
		hrtr->dimension
		785

		hrtr->size
		60000

		hr->dimension
		785

		hr->size
		7500

		historyRepasShuffle_u 0.234008s
		historyRepasRed(hr) 0.0156005s
		historyRepasRed(hrs) 0.031201s
		buildtup 32.169s
		steps: 256850
		23395.8,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<14,10>}
		23285.8,{<10,9>,<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>}
		23217.8,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>,<14,11>}
		23197.7,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>,<15,9>}
		23176.9,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>}
		23159,{<10,10>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>}
		23126.1,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<15,9>}
		23106.6,{<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>}
		23102.4,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<14,10>,<15,9>,<15,10>}
		23087,{<10,9>,<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<13,9>,<13,10>,<14,9>,<14,10>}
		transpose 0.0312006s
		historyRepasShuffle_u 0.49921s
		historyRepasRed(hr) 0.0156003s
		historyRepasRed(hrs) 0.0156003s
		buildtup 186.269s
		steps: 256850
		23400.4,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<14,10>}
		23255,{<10,9>,<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>}
		23190.9,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>,<14,11>}
		23180.6,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>}
		23143.9,{<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<15,9>}
		23140.3,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>,<15,9>}
		23105.7,{<10,10>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>}
		23082.1,{<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<13,11>,<14,9>,<14,10>}
		23052.5,{<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<12,11>,<13,9>,<13,10>,<14,9>,<14,10>,<15,9>,<15,10>}
		23050.2,{<10,9>,<10,10>,<10,11>,<11,9>,<11,10>,<11,11>,<12,9>,<12,10>,<13,9>,<13,10>,<14,9>,<14,10>}
		*/
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto ind = histogramsIndependent;
		auto algn = histogramsAlignment;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto arpr = histogramRepasRed;
		auto prar = histogramRepaRedsIndependent;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
		{
			return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
		{
			return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
		};
		auto hrpr = historyRepasRed;
		auto aralgn = [](const HistogramRepa& ar)
		{
			auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
			return ar.facLn() - ax->facLn();
		};

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		// model 3
		size_t xmax = 512;
		size_t omax = 40;
		size_t bmax = 40*4;
		size_t mmax = 4;
		size_t umax = 256;
		size_t pmax = 1;
		{
			auto start = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			auto end = chrono::system_clock::now();
			cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto pr = historyRepasRed(*hr);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto prs = historyRepasRed(*hrs);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto t = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
			end = chrono::system_clock::now();
			cout << "buildtup " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			auto xx = std::move(std::get<0>(t));
			auto s = std::get<1>(t);
			cout << "steps: " << s << endl;
			cout << "tuples: " << xx->size() << endl;

			s = 0;
			std::size_t p = 0;
			start = chrono::system_clock::now();
			for (auto& kk : *xx)
			{
				auto t2 = parametersSystemsPartitionerMaxRollByMRepa_ui(mmax, umax, pmax, kk, *hr, *hrs);
				p += std::get<0>(t2)->size();
				s += std::get<1>(t2);
			}
			end = chrono::system_clock::now();
			cout << "parter " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			cout << "steps: " << s << endl;
			cout << "partitions: " << p << endl;

			/*
			historyRepasShuffle_u 1.74723s
			historyRepasRed(hr) 0.156003s
			historyRepasRed(hrs) 0.156003s
			buildtup 392.581s
			steps: 416030
			tuples: 40
			parter 50.2028s
			steps: 442000
			partitions: 120
			*/
		}
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto ind = histogramsIndependent;
		auto algn = histogramsAlignment;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto arpr = histogramRepasRed;
		auto prar = histogramRepaRedsIndependent;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
		{
			return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
		{
			return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
		};
		auto hrpr = historyRepasRed;
		auto aralgn = [](const HistogramRepa& ar)
		{
			auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
			return ar.facLn() - ax->facLn();
		};
		auto tupler = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui;
		auto rrvqqy = parametersHistogramRepaVecsSetTuplePartitionTopByM_u;
		auto parter = parametersSystemsPartitionerMaxRollByMRepa_ui;
		auto roller = parametersRollerMaximumRollExcludedSelfRepa_i;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		// model 3
		size_t xmax = 512;
		size_t omax = 40;
		size_t bmax = 40 * 4;
		size_t mmax = 4;
		size_t umax = 256;
		size_t pmax = 1;
		{
			auto start = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			auto end = chrono::system_clock::now();
			cout << "historyRepasShuffle_u " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto pr = historyRepasRed(*hr);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hr) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto prs = historyRepasRed(*hrs);
			end = chrono::system_clock::now();
			cout << "historyRepasRed(hrs) " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;

			start = chrono::system_clock::now();
			auto t = tupler(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
			end = chrono::system_clock::now();
			cout << "tupler " << ((chrono::duration<double>)(end - start)).count() << "s" << endl;
			auto xx = std::move(std::get<0>(t));
			auto s = std::get<1>(t);
			cout << "steps: " << s << endl;
			cout << "tuples: " << xx->size() << endl;

			map<string, double> perf;
			map<string, size_t> steps;
			auto mark = chrono::system_clock::now();
			for (auto& kk : *xx)
			{
				auto z = (double)hr->size;

				mark = chrono::system_clock::now();
				auto ar = hrred(*hr, kk);
				auto ars = hrred(*hrs, kk);
				perf["hrred"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
				steps["hrred"] += 2;

				mark = chrono::system_clock::now();
				double y1 = ar->facLn() - ars->facLn();
				perf["facLn"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
				steps["facLn"] += 2;
				mark = chrono::system_clock::now();

				auto t = rrvqqy(mmax, umax, pmax, *ar, *ars, z, y1);
				perf["parter"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
				steps["parter"] += std::get<1>(t);

				auto xx = std::move(std::get<0>(t));
				for (auto& nn : *xx)
				{
					mark = chrono::system_clock::now();
					auto t2 = roller(nn, *ar, *ars, z);
					perf["roller"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
					steps["roller"] += std::get<1>(t2);
				}
			}
			cout << "perf: " << perf << endl;
			cout << "steps: " << steps << endl;

			/*
			historyRepasShuffle_u 1.77843s
			historyRepasRed(hr) 0.156003s
			historyRepasRed(hrs) 0.156003s
			tupler 395.88s
			steps: 416030
			tuples: 40
			perf: {(facLn,0),(hrred,0.0936018),(parter,51.9198),(roller,2.01244)}
			steps: {(facLn,80),(hrred,80),(parter,442000),(roller,523178)}
			*/
		}
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto ind = histogramsIndependent;
		auto algn = histogramsAlignment;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto arpr = histogramRepasRed;
		auto prar = histogramRepaRedsIndependent;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
		{
			return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
		{
			return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
		};
		auto hrpr = historyRepasRed;
		auto aralgn = [](const HistogramRepa& ar)
		{
			auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
			return ar.facLn() - ax->facLn();
		};
		auto tupler = parametersSystemsBuilderTupleNoSumlayerMultiEffectiveRepa_ui;
		auto rrvqqy = parametersHistogramRepaVecsSetTuplePartitionTopByM_u;
		auto parter = parametersSystemsPartitionerMaxRollByMRepa_ui;
		auto roller = parametersRollerMaximumRollExcludedSelfRepa_i;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		// model 35
		size_t xmax = 1024;
		size_t omax = 30;
		size_t bmax = 30 * 3;
		size_t mmax = 3;
		size_t umax = 256;
		size_t pmax = 1;
		{
			map<string, double> perf;
			map<string, size_t> steps;
			auto mark = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			perf["historyRepasShuffle_u"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
			steps["historyRepasShuffle_u"] += 1;

			mark = chrono::system_clock::now();
			auto pr = historyRepasRed(*hr);
			perf["historyRepasRed"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
			steps["historyRepasRed"] += 1;

			mark = chrono::system_clock::now();
			auto prs = historyRepasRed(*hrs);
			perf["historyRepasRed"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
			steps["historyRepasRed"] += 1;

			mark = chrono::system_clock::now();
			auto t = tupler(xmax, omax, bmax, mmax, vvk1, FudRepa(), *hr, *pr, *hrs, *prs);
			perf["tupler"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
			steps["tupler"] += std::get<1>(t);
			auto xx = std::move(std::get<0>(t));

			for (auto& kk : *xx)
			{
				auto z = (double)hr->size;

				mark = chrono::system_clock::now();
				auto ar = hrred(*hr, kk);
				auto ars = hrred(*hrs, kk);
				perf["hrred"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
				steps["hrred"] += 2;

				mark = chrono::system_clock::now();
				double y1 = ar->facLn() - ars->facLn();
				perf["facLn"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
				steps["facLn"] += 2;
				mark = chrono::system_clock::now();

				auto t = rrvqqy(mmax, umax, pmax, *ar, *ars, z, y1);
				perf["parter"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
				steps["parter"] += std::get<1>(t);

				auto xx = std::move(std::get<0>(t));
				for (auto& nn : *xx)
				{
					mark = chrono::system_clock::now();
					auto t2 = roller(nn, *ar, *ars, z);
					perf["roller"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
					steps["roller"] += std::get<1>(t2);
				}
			}
			cout << "historyRepasShuffle_u " << perf["historyRepasShuffle_u"] << "s" << endl;
			cout << "steps: " << steps["historyRepasShuffle_u"] << endl;
			cout << "historyRepasRed " << perf["historyRepasRed"] << "s" << endl;
			cout << "steps: " << steps["historyRepasRed"] << endl;
			cout << "tupler " << perf["tupler"] << "s" << endl;
			cout << "steps: " << steps["tupler"] << endl;
			cout << "hrred " << perf["hrred"] << "s" << endl;
			cout << "steps: " << steps["hrred"] << endl;
			cout << "facLn " << perf["facLn"] << "s" << endl;
			cout << "steps: " << steps["facLn"] << endl;
			cout << "parter " << perf["parter"] << "s" << endl;
			cout << "steps: " << steps["parter"] << endl;
			cout << "roller " << perf["roller"] << "s" << endl;
			cout << "steps: " << steps["roller"] << endl;
			/*
			historyRepasShuffle_u 1.87204s
			steps: 1
			historyRepasRed 0.296406s
			steps: 2
			tupler 370.247s
			steps: 389070
			hrred 0.156003s
			steps: 60
			facLn 0s
			steps: 60
			parter 61.3892s
			steps: 294930
			roller 4.82049s
			steps: 802096
			*/
		}
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto ind = histogramsIndependent;
		auto algn = histogramsAlignment;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto arpr = histogramRepasRed;
		auto prar = histogramRepaRedsIndependent;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
		{
			return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
		{
			return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
		};
		auto hrpr = historyRepasRed;
		auto aralgn = [](const HistogramRepa& ar)
		{
			auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
			return ar.facLn() - ax->facLn();
		};
		auto uuur = systemsSystemRepa;
		auto uruu = systemsRepasSystem;
		auto fffr = systemsFudsFudRepa_u;
		auto frff = systemsFudRepasFud_u;

		auto layerer = parametersSystemsLayererMaxRollByMExcludedSelfHighestIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		// model 3
		size_t wmax = 2048;
		size_t lmax = 8;
		size_t xmax = 512;
		size_t omax = 40;
		size_t bmax = 40 * 4;
		size_t mmax = 4;
		size_t umax = 256;
		size_t pmax = 1;
		{
			map<string, double> perf;

			auto mark = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			perf["historyRepasShuffle_u"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();

			mark = chrono::system_clock::now();
			auto t = layerer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, vvk1, *hr, *hrs, 1, *ur);
			perf["layerer"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
			auto& fr = std::get<0>(t);
			auto& mm = std::get<1>(t);
			if (mm->size())
			{
				auto& a = mm->back().first;
				auto& kk = mm->back().second;
				VarSet qq;
				for (std::size_t i = 0; i < kk.size(); i++)
					qq.insert(*(ur->listVarSizePair[kk[i]]).first);
				cout << "a = " << a << endl;
				cout << "kk = " << qq << endl;
			}
			cout << "fudRepasSize(fr) = " << fudRepasSize(*fr) << endl;
		}
		/*
		>>> layerer
		>>> layer	   fud: 1  layer: 1
		substrate cardinality: 784
		fud cardinality: 0
		tupler  searched: 416030		rate: 1066.88
		tupler 389.949s
		tuple cardinality: 40
		max tuple algn: 156208
		layer cardinality: 196
		parter  searched: 442000		rate: 8619.05
		parter 51.2818s
		roller  searched: 523178		rate: 251398
		roller 2.08108s
		der vars algn density: 141207
		dervarser	   searched: 105580		rate: 742.594
		dervarser 142.177s
		application 0.976372s
		<<< layer 586.473s
		>>> layer	   fud: 1  layer: 2
		substrate cardinality: 784
		fud cardinality: 196
		tupler  searched: 308712		rate: 1390.63
		tupler 221.995s
		tuple cardinality: 40
		max tuple algn: 99539.3
		layer cardinality: 100
		parter  searched: 7440  rate: 12394.3
		parter 0.600278s
		roller  searched: 744226		rate: 437419
		roller 1.7014s
		der vars algn density: 161478
		dervarser	   searched: 180631		rate: 824.022
		dervarser 219.206s
		application 0.798009s
		<<< layer 444.306s
		>>> layer	   fud: 1  layer: 3
		substrate cardinality: 784
		fud cardinality: 296
		tupler  searched: 436989		rate: 1450.31
		tupler 301.306s
		tuple cardinality: 40
		max tuple algn: 3244.27
		layer cardinality: 76
		parter  searched: 7440  rate: 14363.7
		parter 0.517973s
		roller  searched: 780016		rate: 561905
		roller 1.38816s
		der vars algn density: 107674
		dervarser	   searched: 184660		rate: 1395.98
		dervarser 132.28s
		application 0.862928s
		<<< layer 436.361s
		<<< layerer 1467.59s
		a = 161478
		kk = {<<1,2>,12>,<<1,2>,14>,<<1,2>,15>,<<1,2>,16>,<<1,2>,18>,<<1,2>,51>,<<1,2>,56>,<<1,2>,61>,<<1,2>,63>,<<1,2>,73>,<<1,2>,77>}
		fudRepasSize(fr) = 296
		*/
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto ind = histogramsIndependent;
		auto algn = histogramsAlignment;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto arpr = histogramRepasRed;
		auto prar = histogramRepaRedsIndependent;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
		{
			return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
		{
			return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
		};
		auto hrpr = historyRepasRed;
		auto aralgn = [](const HistogramRepa& ar)
		{
			auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
			return ar.facLn() - ax->facLn();
		};
		auto uuur = systemsSystemRepa;
		auto uruu = systemsRepasSystem;
		auto fffr = systemsFudsFudRepa_u;
		auto frff = systemsFudRepasFud_u;

		auto layerer = parametersSystemsLayererMaxRollByMExcludedSelfHighestIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		// model 35
		size_t wmax = 2048;
		size_t lmax = 8;
		size_t xmax = 1024;
		size_t omax = 30;
		size_t bmax = 30 * 3;
		size_t mmax = 3;
		size_t umax = 256;
		size_t pmax = 1;
		{
			map<string, double> perf;

			auto mark = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			perf["historyRepasShuffle_u"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();

			mark = chrono::system_clock::now();
			auto t = layerer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, vvk1, *hr, *hrs, 1, *ur);
			perf["layerer"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
			auto& fr = std::get<0>(t);
			auto& mm = std::get<1>(t);
			if (mm->size())
			{
				auto& a = mm->back().first;
				auto& kk = mm->back().second;
				VarSet qq;
				for (std::size_t i = 0; i < kk.size(); i++)
					qq.insert(*(ur->listVarSizePair[kk[i]]).first);
				cout << "a = " << a << endl;
				cout << "kk = " << qq << endl;
			}
			cout << "fudRepasSize(fr) = " << fudRepasSize(*fr) << endl;
		}
		/*
		>>> layerer
		>>> layer	   fud: 1  layer: 1
		substrate cardinality: 784
		fud cardinality: 0
		tupler  searched: 389070		rate: 1047.9
		tupler 371.285s
		tuple cardinality: 30
		max tuple algn: 178925
		layer cardinality: 101
		parter  searched: 294930		rate: 4846.68
		parter 60.852s
		roller  searched: 802096		rate: 154438
		roller 5.19363s
		der vars algn density: 140988
		dervarser	   searched: 34820 rate: 689.954
		dervarser 50.4671s
		application 0.848342s
		<<< layer 488.653s
		>>> layer	   fud: 1  layer: 2
		substrate cardinality: 784
		fud cardinality: 101
		tupler  searched: 176058		rate: 1169.92
		tupler 150.487s
		tuple cardinality: 30
		max tuple algn: 135438
		layer cardinality: 77
		parter  searched: 3630  rate: 8638.15
		parter 0.420229s
		roller  searched: 759555		rate: 309677
		roller 2.45273s
		der vars algn density: 120890
		dervarser	   searched: 56806 rate: 1064.27
		dervarser 53.3757s
		application 0.751577s
		<<< layer 207.494s
		<<< layerer 696.562s
		a = 140988
		kk = {<<1,1>,7>,<<1,1>,24>,<<1,1>,25>,<<1,1>,27>,<<1,1>,32>,<<1,1>,41>,<<1,1>,43>,<<1,1>,55>,<<1,1>,61>,<<1,1>,77>,<<1,1>,92>}
		fudRepasSize(fr) = 101
		*/
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto ind = histogramsIndependent;
		auto algn = histogramsAlignment;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto arpr = histogramRepasRed;
		auto prar = histogramRepaRedsIndependent;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
		{
			return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
		{
			return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
		};
		auto hrpr = historyRepasRed;
		auto aralgn = [](const HistogramRepa& ar)
		{
			auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
			return ar.facLn() - ax->facLn();
		};
		auto uuur = systemsSystemRepa;
		auto uruu = systemsRepasSystem;
		auto fffr = systemsFudsFudRepa_u;
		auto frff = systemsFudRepasFud_u;

		auto layerer = parametersSystemsLayererMaxRollByMExcludedSelfHighestIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		// model 1
//		size_t wmax = 1024;
		size_t wmax = 32;
		size_t lmax = 8;
		size_t xmax = 256;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 256;
		size_t pmax = 1;
//		size_t fmax = 15;
		size_t fmax = 2;
		size_t mult = 1;
		size_t seed = 5;
		{
			map<string, double> perf;

			auto mark = chrono::system_clock::now();
			auto hrs = historyRepasShuffle_u(*hr, 1);
			perf["historyRepasShuffle_u"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();

			mark = chrono::system_clock::now();
			auto t = layerer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, vvk1, *hr, *hrs, 1, *ur);
			perf["layerer"] += ((chrono::duration<double>)(chrono::system_clock::now() - mark)).count();
			auto& fr = std::get<0>(t);
			auto& mm = std::get<1>(t);
			if (mm->size())
			{
				auto& a = mm->back().first;
				auto& kk = mm->back().second;
				VarSet qq;
				for (std::size_t i = 0; i < kk.size(); i++)
					qq.insert(*(ur->listVarSizePair[kk[i]]).first);
				cout << "a = " << a << endl;
				cout << "kk = " << qq << endl;
			}
			cout << "fudRepasSize(fr) = " << fudRepasSize(*fr) << endl;
		}
		/*
		hr->dimension
		785

		hr->size
		60000

		>>> layerer
		>>> layer		fud: 1		layer: 1
		substrate cardinality: 784
		fud cardinality: 0
		tupler		searched: 268440		rate: 3059.04
		tupler 87.753s
		tuple cardinality: 10
		max tuple algn: 133995
		layer cardinality: 38
		parter		searched: 10930		rate: 38053.4
		parter 0.287228s
		roller		searched: 31245		rate: 427624
		roller 0.0730666s
		der vars algn density: 56977
		dervarser		searched: 2426		rate: 3122.04
		dervarser 0.777056s
		application 0.366584s
		<<< layer 89.257s
		>>> layer		fud: 1		layer: 2
		substrate cardinality: 784
		fud cardinality: 38
		tupler		searched: 56839		rate: 2869.46
		tupler 19.8083s
		tuple cardinality: 10
		max tuple algn: 63424.4
		layer cardinality: 25
		parter		searched: 1210		rate: 76612.7
		parter 0.0157937s
		roller		searched: 16853		rate: 786624
		roller 0.0214245s
		der vars algn density: 65722.6
		dervarser		searched: 4735		rate: 3428.19
		dervarser 1.38119s
		application 0.364668s
		<<< layer 21.5913s
		>>> layer		fud: 1		layer: 3
		substrate cardinality: 784
		fud cardinality: 63
		tupler		searched: 84320		rate: 2276.67
		tupler 37.0366s
		tuple cardinality: 10
		max tuple algn: 19838.5
		layer cardinality: 21
		parter		searched: 10930		rate: 60754.2
		parter 0.179905s
		roller		searched: 33163		rate: 850393
		roller 0.0389972s
		der vars algn density: 64125.9
		dervarser		searched: 6536		rate: 2939.56
		dervarser 2.22346s
		application 0.376406s
		<<< layer 39.8554s
		<<< layerer 151.03s
		a = 65722.6
		kk = {<<1,2>,1>,<<1,2>,2>,<<1,2>,5>,<<1,2>,23>,<<1,2>,25>}
		fudRepasSize(fr) = 63
		*/
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto ind = histogramsIndependent;
		auto algn = histogramsAlignment;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto arpr = histogramRepasRed;
		auto prar = histogramRepaRedsIndependent;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SizeList& kk)
		{
			return setVarsHistoryRepasReduce_u(1.0, kk.size(), kk.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const SizeList& kk)
		{
			return setVarsHistoryRepasHistoryRepaReduced_u(kk.size(), kk.data(), hr);
		};
		auto hrpr = historyRepasRed;
		auto aralgn = [](const HistogramRepa& ar)
		{
			auto ax = histogramRepaRedsIndependent(ar.size(), *histogramRepasRed(ar.size(), ar));
			return ar.facLn() - ax->facLn();
		};
		auto uuur = systemsSystemRepa;
		auto uruu = systemsRepasSystem;
		auto fffr = systemsFudsFudRepa_u;
		auto frff = systemsFudRepasFud_u;

		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		// model 1
		size_t wmax = 1024;
		size_t lmax = 8;
		size_t xmax = 256;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 256;
		size_t pmax = 1;
		size_t fmax = 15;
		size_t mult = 1;
		size_t seed = 5;
		{
			auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax,  mult, seed, vvk1, *hr, *ur);
			std::ofstream out("model1.bin", std::ios::binary);
			systemRepasPersistent(*ur, out); cout << endl;
			applicationRepasPersistent(*dr, out); cout << endl;
			out.close();
//			cout << "dr = " << *dr << endl;
			cout << "treesPaths(dr.slices)" << endl;
			rpln(cout, *treesPaths(*dr->slices)); cout << endl;
		}
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		// model 2
		size_t wmax = 1024;
		size_t lmax = 8;
		size_t xmax = 1024;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 256;
		size_t pmax = 1;
		size_t fmax = 15;
		size_t mult = 3;
		size_t seed = 5;
		{
			auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vvk1, *hr, *ur);
			std::ofstream out("model2.bin", std::ios::binary);
			systemRepasPersistent(*ur, out); cout << endl;
			applicationRepasPersistent(*dr, out); cout << endl;
			out.close();
			//			cout << "dr = " << *dr << endl;
			// cout << "treesPaths(dr.slices)" << endl;
			// rpln(cout, *treesPaths(*dr->slices)); cout << endl;
		}
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model35")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 2048;
		size_t lmax = 8;
		size_t xmax = 1024;
		size_t omax = 30;
		size_t bmax = 30 * 3;
		size_t mmax = 3;
		size_t umax = 256;
		size_t pmax = 1;
		size_t fmax = 127;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vvk1, *hr, *ur);
		std::ofstream out("model35.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model100")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

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
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vvk1, *hr, *ur);
		std::ofstream out("model100.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model2.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 500)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("M5FA01.bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "bitmap" && string(argv[2]) == "model35")
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model35.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 50)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model35.bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "bitmap")
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		string model = string(argv[2]);
		int zmin = argc >= 4 ? atoi(argv[3]) : 50;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in(model + ".bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= zmin)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite(model + ".bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model101")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedRegionRandomIO(2,10,13);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

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
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vvk1, *hr, *ur);
		std::ofstream out("model101.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedRegionRandomIO(2, 10, 13);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model101.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 50)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(10, 3, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model101.bmp", bmvstack(ll2));
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto mark = clk::now();

		auto xx = trainBucketedRegionRandomIO(2, 10, 13);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model101.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "treesSize(*dr->slices)" << endl
			<< treesSize(*dr->slices) << endl << endl;

		cout << "frder(*dr->fud)->size()" << endl
			<< frder(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		{
			auto& llu = ur1->listVarSizePair;
			VarSet qq;
			for (std::size_t i = 0; i < dr->substrate.size(); i++)
				qq.insert(*(llu[dr->substrate[i]]).first);
			cout << "substrate " << qq << endl;
		}

		{
			auto& llu = ur1->listVarSizePair;
			VarSet qq;
			auto ww = frder(*dr->fud);
			for (auto& w : *ww)
				qq.insert(*(llu[w]).first);
			cout << "derived " << qq << endl;
		}

		mark = clk::now();
		auto hr1 = frmul(*hr, *dr->fud);
		cout << "frmul " << ((sec)(clk::now() - mark)).count() << "s" << endl; // 84MB
		this_thread::sleep_for(60s);
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;
		auto drcopy = applicationRepasApplicationRepa_u;

		auto mark = clk::now();

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		mark = clk::now();
		StrVarPtrMap m;
		std::ifstream in("model101.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		cout << "model " << ((sec)(clk::now() - mark)).count() << "s" << endl;

		mark = clk::now();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,6,10,14,18 };
		SizeList ys{ 2,6,10,14,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}
		cout << "reframe_u " << ((sec)(clk::now() - mark)).count() << "s" << endl;

		cout << "treesSize(*dr.slices)" << endl
			<< treesSize(*dr.slices) << endl << endl;

		cout << "frder(*dr.fud)->size()" << endl
			<< frder(*dr.fud)->size() << endl << endl;

		cout << "frund(*dr.fud)->size()" << endl
			<< frund(*dr.fud)->size() << endl << endl;

		cout << "frvars(*dr.fud)->size()" << endl
			<< frvars(*dr.fud)->size() << endl << endl;

		//{
		//	VarSet qq;
		//	for (std::size_t i = 0; i < dr.substrate.size(); i++)
		//		qq.insert(*(llu[dr.substrate[i]]).first);
		//	cout << "substrate " << qq << endl;
		//}

		//{
		//	VarSet qq;
		//	auto ww = frder(*dr.fud);
		//	for (auto& w : *ww)
		//		qq.insert(*(llu[w]).first);
		//	cout << "derived " << qq << endl;
		//}

		mark = clk::now();
		auto hr1 = frmul(*hr, *dr.fud);
		cout << "frmul " << ((sec)(clk::now() - mark)).count() << "s" << endl; 
		this_thread::sleep_for(60s);
		/*
		model 0.0309985s
		reframe_u 0.634182s
		treesSize(*dr.slices)
		17500

		frder(*dr.fud)->size()
		14350

		frund(*dr.fud)->size()
		676

		frvars(*dr.fud)->size()
		71476

		frmul 6.23653s
		
		566MB
		*/
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;
		auto drcopy = applicationRepasApplicationRepa_u;

		auto mark = clk::now();

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		mark = clk::now();
		StrVarPtrMap m;
		std::ifstream in("model101.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		cout << "model " << ((sec)(clk::now() - mark)).count() << "s" << endl;

		mark = clk::now();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,6,8,10,12,14,18 };
		SizeList ys{ 2,6,8,10,12,14,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}
		cout << "reframe_u " << ((sec)(clk::now() - mark)).count() << "s" << endl;

		cout << "treesSize(*dr.slices)" << endl
			<< treesSize(*dr.slices) << endl << endl;

		cout << "frder(*dr.fud)->size()" << endl
			<< frder(*dr.fud)->size() << endl << endl;

		cout << "frund(*dr.fud)->size()" << endl
			<< frund(*dr.fud)->size() << endl << endl;

		cout << "frvars(*dr.fud)->size()" << endl
			<< frvars(*dr.fud)->size() << endl << endl;

		//{
		//	VarSet qq;
		//	for (std::size_t i = 0; i < dr.substrate.size(); i++)
		//		qq.insert(*(llu[dr.substrate[i]]).first);
		//	cout << "substrate " << qq << endl;
		//}

		//{
		//	VarSet qq;
		//	auto ww = frder(*dr.fud);
		//	for (auto& w : *ww)
		//		qq.insert(*(llu[w]).first);
		//	cout << "derived " << qq << endl;
		//}

//		hr->transpose();
		mark = clk::now();
		auto hr1 = frmul(*hr, *dr.fud);
		cout << "frmul " << ((sec)(clk::now() - mark)).count() << "s" << endl;
		this_thread::sleep_for(60s);
		/*
		model 0.0307217s
		reframe_u 1.26809s
		treesSize(*dr.slices)
		34300

		frder(*dr.fud)->size()
		28126

		frund(*dr.fud)->size()
		676

		frvars(*dr.fud)->size()
		139444

		frmul 12.6613s = 12.1 ns/z/var = 32 cycles

		1,092MB => 7831/var = (7500 + 331)/var
		*/
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto hrpr = setVarsHistoryRepasRed_u;
		auto prents = histogramRepaRedsListEntropy;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;
		auto drcopy = applicationRepasApplicationRepa_u;

		auto mark = clk::now();

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		mark = clk::now();
		StrVarPtrMap m;
		std::ifstream in("model101.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		cout << "model " << ((sec)(clk::now() - mark)).count() << "s" << endl;

		mark = clk::now();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,6,8,10,12,14,18 };
		SizeList ys{ 2,6,8,10,12,14,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}
		cout << "reframe_u " << ((sec)(clk::now() - mark)).count() << "s" << endl;

		cout << "treesSize(*dr.slices)" << endl
			<< treesSize(*dr.slices) << endl << endl;

		cout << "frder(*dr.fud)->size()" << endl
			<< frder(*dr.fud)->size() << endl << endl;

		cout << "frund(*dr.fud)->size()" << endl
			<< frund(*dr.fud)->size() << endl << endl;

		cout << "frvars(*dr.fud)->size()" << endl
			<< frvars(*dr.fud)->size() << endl << endl;

		//{
		//	VarSet qq;
		//	for (std::size_t i = 0; i < dr.substrate.size(); i++)
		//		qq.insert(*(llu[dr.substrate[i]]).first);
		//	cout << "substrate " << qq << endl;
		//}

		//{
		//	VarSet qq;
		//	auto ww = frder(*dr.fud);
		//	for (auto& w : *ww)
		//		qq.insert(*(llu[w]).first);
		//	cout << "derived " << qq << endl;
		//}

		mark = clk::now();
		auto hr1 = frmul(*hr, *dr.fud);
		cout << "frmul " << ((sec)(clk::now() - mark)).count() << "s" << endl;
		mark = clk::now();
		auto sl = treesElements(*dr.slices);
		auto pr1 = hrpr(sl->size(),sl->data(),*hr1);
		cout << "hrpr " << ((sec)(clk::now() - mark)).count() << "s" << endl;
		mark = clk::now();
		auto ee1 = prents(*pr1);
		cout << "prents " << ((sec)(clk::now() - mark)).count() << "s" << endl;
		cout << "prents size" << endl
			<< ee1->size() << endl << endl;
		mark = clk::now();
		std::sort(ee1->begin(), ee1->end());
		cout << "sort " << ((sec)(clk::now() - mark)).count() << "s" << endl;
		cout << "prents front" << endl
			<< ee1->front() << endl << endl;
		cout << "prents back" << endl
			<< ee1->back() << endl << endl;
		std::sort(ee1->begin(), ee1->end());
		DoubleSizePairList ee2;
		for (std::size_t i = ee1->size() - 1000; i < ee1->size(); i++)
			ee2.push_back((*ee1)[i]);
		cout << "prents 1000" << endl;
		for (auto& p : ee2)
			cout << "(" << *(llu[p.second]).first << "," << p.first << "),";
		cout << endl << endl;

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
		};
		auto hrred = setVarsHistoryRepasReduce_u;
		auto hrpr = historyRepasRed;
		auto prents = histogramRepaRedsListEntropy;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;
		auto drcopy = applicationRepasApplicationRepa_u;

		auto mark = clk::now();

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		auto hr1 = hrhrred(*hr, *ur, vvk);
		auto pr1 = hrpr(*hr1);
		auto ee1 = prents(*pr1);
		std::map<std::size_t, double> mm1;
		for (auto& p : *ee1)
			mm1[p.second] = p.first;
		int b = 28;
		int c = 3;
		Bitmap bm(b*c, b*c);
		for (int i = 0; i < bm.height; i++) {
			for (int j = 0; j< bm.width; j++) {
				unsigned char x = (unsigned char)(mm1[(b - 1 - (i / c))*b + (j / c)]*255/log(2));
				int k = i*bm.width * 3 + j * 3;
				for (int l = 0; l<3; l++)
					bm.image[k + l] = x;
			}
		}
		bmwrite("ents.bmp", bm);
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model100_1")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 18;
		size_t lmax = 8;
		size_t xmax = 128;
		double znnmax = 7500.0 * 2.0 * 100.0 * 100.0;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 127;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, znnmax, omax, bmax, mmax, umax, pmax, fmax, mult, 0, seed, vvk1, FudRepa(), *hr, 0, *ur);
		std::ofstream out("model100_1.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model100_1.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 50)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model100_1.bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model102")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		StrVarPtrMap m;
		std::ifstream in("model101.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,6,8,10,12,14,18 };
		SizeList ys{ 2,6,8,10,12,14,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		size_t wmax = 18;
		size_t lmax = 8;
		size_t xmax = 128;
		double znnmax = 7500.0 * 2.0 * 100.0 * 100.0;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 127;
		size_t mult = 1;
		size_t seed = 5;
		auto sl = treesElements(*dr.slices);
		auto dr2 = applicationer(wmax, lmax, xmax, znnmax, omax, bmax, mmax, umax, pmax, fmax, mult, 0, seed, *sl, *dr.fud, *hr, 0, *ur);
		auto dr3 = drjoin(dr,*dr2);
		std::ofstream out("model102.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model102.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "treesSize(*dr->slices)" << endl
			<< treesSize(*dr->slices) << endl << endl;

		cout << "treesPaths(dr.slices)" << endl;
		rpln(cout, *treesPaths(*dr->slices)); cout << endl;

		cout << "frder(*dr->fud)->size()" << endl
			<< frder(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)" << endl
			<< *frund(*dr->fud) << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model102.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "treesSize(*dr->slices)" << endl
			<< treesSize(*dr->slices) << endl << endl;

		cout << "frder(*dr->fud)->size()" << endl
			<< frder(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)" << endl
			<< *frund(*dr->fud) << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 50)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model102.bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model103")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedRegionRandomIO(2, 10, 13);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 4;
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
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vvk1, *hr, *ur);
		std::ofstream out("model103.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedRegionRandomIO(2, 10, 13);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model103.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 50)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(10, 3, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model103.bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model104")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		StrVarPtrMap m;
		std::ifstream in("model103.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,6,10,14,18 };
		SizeList ys{ 2,6,10,14,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		size_t wmax = 18;
		size_t lmax = 8;
		size_t xmax = 128;
		double znnmax = 7500.0 * 2.0 * 800.0 * 800.0;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 127;
		size_t mult = 1;
		size_t seed = 5;
		auto sl = treesElements(*dr.slices);
		auto dr2 = applicationer(wmax, lmax, xmax, znnmax, omax, bmax, mmax, umax, pmax, fmax, mult, 0, seed, *sl, *dr.fud, *hr, 0, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model104.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model104.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "treesSize(*dr->slices)" << endl
			<< treesSize(*dr->slices) << endl << endl;

		cout << "frder(*dr->fud)->size()" << endl
			<< frder(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)" << endl
			<< *frund(*dr->fud) << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 50)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model104.bmp", bmvstack(ll2));
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		std::unique_ptr<System> uu;
		std::unique_ptr<SystemRepa> ur;
		std::unique_ptr<HistoryRepa> hr;
		{
			auto xx = trainBucketedIO(2);
			uu = std::move(std::get<0>(xx));
			ur = std::move(std::get<1>(xx));
			hr = std::move(std::get<2>(xx));
		}

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		SizeList vvl1{ vvi[digit] };

		cout << "train size" << endl
			<< hr->size << endl << endl;

		StrVarPtrMap m;
		std::ifstream in("model100.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		std::map<std::size_t, std::size_t> sp;
		{
			auto hr1 = frmul(*hr, *dr->fud);
			if (hr1->evient)
				hr1->transpose();
			auto z = hr1->size;
			auto& mvv = hr1->mapVarInt();
			auto sh = hr1->shape;
			auto rr = hr1->arr;
			auto pl = mvv[vvi[digit]];
			auto sl = sh[pl];
			auto nn = treesLeafNodes(*dr->slices);
			SizeList al(sl);
			for (auto& s : *nn)
			{
				for (std::size_t k = 0; k < sl; k++)
					al[k] = 0;
				auto pk = mvv[s.first];
				for (std::size_t j = 0; j < z; j++)
				{
					std::size_t u = rr[pk*z + j];
					if (u)
					{
						std::size_t w = rr[pl*z + j];
						al[w]++;
					}
				}
				std::size_t c = 0;
				std::size_t cl = sl;
				for (std::size_t k = 0; k < sl; k++)
				{
					auto u = al[k];
					if (u > c)
					{
						c = u;
						cl = k;
					}
				}
				sp[s.first] = cl;
			}

		}
		//cout << "sp" << endl
		//	<< sp << endl << endl;

		{
			auto xx = testBucketedIO(2);
			hr = std::move(std::get<2>(xx));
		}

		cout << "test size" << endl
			<< hr->size << endl << endl;


		std::size_t a = 0;
		std::size_t x = 0;
		{
			SizeList ww{ vvi[digit] };
			auto nn = treesLeafNodes(*dr->slices);
			for (auto& s : *nn)
				ww.push_back(s.first);
			auto hr1 = hrhrred(ww.size(), ww.data(), *frmul(*hr, *dr->fud));
			if (!hr1->evient)
				hr1->transpose();
			auto n = hr1->dimension;
			auto vv = hr1->vectorVar;
			auto sh = hr1->shape;
			auto z = hr1->size;
			auto rr = hr1->arr;
			auto sl = sh[0];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t cl = rr[j*n];
				for (std::size_t i = 1; i < n; i++)
				{
					std::size_t u = rr[j*n + i];
					if (u)
					{
						std::size_t l = sp[vv[i]];
						if (l == cl)
							a++;
						else if (l == sl)
							x++;
						break;
					}
				}
			}

		}
		cout << "accuracy = " << (double)a / (double)hr->size *100.0 << "%" << endl;
		cout << "ineffective = " << (double)x / (double)hr->size *100.0 << "%" << endl;
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model105")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 4;
		size_t lmax = 8;
		size_t xmax = 128;
		double znnmax = 60000.0 * 2.0 * 100.0 * 100.0;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 127;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, znnmax, omax, bmax, mmax, umax, pmax, fmax, mult, 0, seed, vvk1, FudRepa(), *hr, 0, *ur);
		std::ofstream out("model105.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model106")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 4;
		size_t lmax = 8;
		size_t xmax = 128;
		double znnmax = 60000.0 * 2.0 * 100.0 * 100.0;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 1023;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, znnmax, omax, bmax, mmax, umax, pmax, fmax, mult, 0, seed, vvk1, FudRepa(), *hr, 0, *ur);
		std::ofstream out("model106.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model106.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "treesSize(*dr->slices)" << endl
			<< treesSize(*dr->slices) << endl << endl;

		cout << "frder(*dr->fud)->size()" << endl
			<< frder(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)" << endl
			<< *frund(*dr->fud) << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 10)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model106.bmp", bmvstack(ll2));
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		std::unique_ptr<System> uu;
		std::unique_ptr<SystemRepa> ur;
		std::unique_ptr<HistoryRepa> hr;
		{
			auto xx = trainBucketedIO(2);
			uu = std::move(std::get<0>(xx));
			ur = std::move(std::get<1>(xx));
			hr = std::move(std::get<2>(xx));
		}

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		SizeList vvl1{ vvi[digit] };

		cout << "train size" << endl
			<< hr->size << endl << endl;

		DoubleSizePairList ee;
		auto z = hr->size;
		auto& mvv = hr->mapVarInt();
		auto sh = hr->shape;
		auto rr = hr->arr;
		auto l = vvi[digit];
		auto pl = mvv[l];
		auto sl = sh[pl];
		double f = 1.0 / (double)z;
		for (auto v : vvk1)
		{
			auto p = mvv[v];
			auto s = sh[p];
			SizeList ee1(s*sl);
			SizeList ee2(s);
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = rr[p*z + j];
				std::size_t w = rr[pl*z + j];
				ee1[w*s + u]++;
				ee2[u]++;
			}
			double e1 = 0.0;
			double e2 = 0.0;
			for (std::size_t k = 0; k < s*sl; k++)
			{
				double a = (double)ee1[k] * f;
				if (a > 0.0)
					e1 += a * log(a);
			}
			for (std::size_t k = 0; k < s; k++)
			{
				double a = (double)ee2[k] * f;
				if (a > 0.0)
					e2 += a * log(a);
			}
			ee.push_back(DoubleSizePair(e2-e1,v));
		}
		std::sort(ee.begin(), ee.end());
		auto& llu = ur->listVarSizePair;
		VarSet qq;
		for (auto p : ee)
			cout << "(" << p.first << "," << *(llu[p.second]).first << ")" << endl;
		cout << endl;

		/*
		(2.08693,<14,15>)
		(2.1026,<13,15>)
		(2.10739,<15,15>)
		(2.11737,<16,15>)
		(2.11856,<17,14>)
		(2.12503,<15,18>)
		(2.12819,<16,14>)
		(2.13386,<21,9>)
		(2.13499,<17,15>)
		(2.1351,<18,14>)
		(2.13666,<20,11>)
		(2.13843,<22,9>)
		...
		(2.30116,<28,3>)
		(2.30116,<28,4>)
		(2.30116,<28,5>)
		(2.30116,<28,24>)
		(2.30116,<28,25>)
		(2.30116,<28,26>)
		(2.30116,<28,27>)
		(2.30116,<28,28>)
		*/
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model107")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(10);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

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
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vvk1, *hr, *ur);
		std::ofstream out("model107.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto uruu = systemsRepasSystem;

		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;
		auto frff = systemsFudRepasFud_u;

		auto xx = trainBucketedIO(10);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model107.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		uruu(*ur1, *uu);
		auto ff = frff(*uu, *ur1, *dr->fud);
		std::ofstream out("model107.json");
		fudsPersistentPretty(1, *ff, out); cout << endl;
		out.close();

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 50)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 10, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model107.bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model108")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerConditionalFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		size_t fmax = 127;
		auto dr = applicationer(fmax, vvk1, vvi[digit], *hr, 1, *ur);
		std::ofstream out("model108.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model108.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "treesSize(*dr->slices)" << endl
			<< treesSize(*dr->slices) << endl << endl;

		cout << "frder(*dr->fud)->size()" << endl
			<< frder(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)" << endl
			<< *frund(*dr->fud) << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 10)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model108.bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model100_2")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerConditionalFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		StrVarPtrMap m;
		std::ifstream in("model100.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		auto hr1 = frmul(*hr, *dr->fud);

		SizeList vvk2;
		for (std::size_t i = 0; i < hr1->dimension; i++)
			vvk2.push_back(hr1->vectorVar[i]);

		size_t fmax = 127;
		auto dr2 = applicationer(fmax, vvk2, vvi[digit], *hr1, 1, *ur1);
		auto dr3 = drjoin(*dr, *dr2);
		std::ofstream out("model100_2.bin", std::ios::binary);
		systemRepasPersistent(*ur1, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in("model100_2.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "treesSize(*dr->slices)" << endl
			<< treesSize(*dr->slices) << endl << endl;

		cout << "frder(*dr->fud)->size()" << endl
			<< frder(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frund(*dr->fud)" << endl
			<< *frund(*dr->fud) << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= 50)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(28, 1, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite("model100_2.bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model106_1")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerConditionalFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 2)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		StrVarPtrMap m;
		std::ifstream in("model106.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		auto hr1 = frmul(*hr, *dr->fud);

		SizeList vvk2;
		for (std::size_t i = 0; i < hr1->dimension; i++)
			vvk2.push_back(hr1->vectorVar[i]);

		size_t fmax = 1023;
		auto dr2 = applicationer(fmax, vvk2, vvi[digit], *hr1, 1, *ur1);
		auto dr3 = drjoin(*dr, *dr2);
		std::ofstream out("model106_1.bin", std::ios::binary);
		systemRepasPersistent(*ur1, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model106_2")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 2)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		StrVarPtrMap m;
		std::ifstream in("model106.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		auto hr1 = frmul(*hr, *dr->fud);

		SizeList vvk2;
		for (std::size_t i = 0; i < hr1->dimension; i++)
			vvk2.push_back(hr1->vectorVar[i]);

		size_t fmax = 1023;
		auto dr2 = applicationer(fmax, vvk2, vvi[digit], *hr1, 1, *ur1);
		auto dr3 = drjoin(*dr, *dr2);
		std::ofstream out("model106_2.bin", std::ios::binary);
		systemRepasPersistent(*ur1, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model106_3")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 64)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		StrVarPtrMap m;
		std::ifstream in("model106.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		auto hr1 = frmul(*hr, *dr->fud);

		SizeList vvk2;
		for (std::size_t i = 0; i < hr1->dimension; i++)
			vvk2.push_back(hr1->vectorVar[i]);

		size_t fmax = 1023;
		auto dr2 = applicationer(fmax, vvk2, vvi[digit], *hr1, 1, *ur1);
		auto dr3 = drjoin(*dr, *dr2);
		std::ofstream out("model106_3.bin", std::ios::binary);
		systemRepasPersistent(*ur1, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model109")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerConditionalFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		StrVarPtrMap m;
		std::ifstream in("model103.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,6,10,14,18 };
		SizeList ys{ 2,6,10,14,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		SizeList vvk2;
		for (std::size_t i = 0; i < hr1->dimension; i++)
			vvk2.push_back(hr1->vectorVar[i]);

		size_t fmax = 127;
		auto dr2 = applicationer(fmax, vvk2, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model109.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model110")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerConditionalFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model103.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,6,8,10,12,14,18 };
		SizeList ys{ 2,6,8,10,12,14,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		SizeList vvk2;
		for (std::size_t i = 0; i < hr1->dimension; i++)
			vvk2.push_back(hr1->vectorVar[i]);

		size_t fmax = 1023;
		auto dr2 = applicationer(fmax, vvk2, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model110.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model111")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerConditionalFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model103.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,6,8,10,12,14,18 };
		SizeList ys{ 2,6,8,10,12,14,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		auto sl = treesElements(*dr.slices);

		size_t fmax = 1023;
		auto dr2 = applicationer(fmax, *sl, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model111.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model112")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedRegionRandomIO(2, 10, 13);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 2)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 4;
		size_t lmax = 12;
		size_t xmax = 128;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 63;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vvk1, *hr, *ur);
		std::ofstream out("model112.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model113")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerConditionalFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model112.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,4,6,8,10,12,14,12,18 };
		SizeList ys{ 2,4,6,8,10,12,14,12,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		auto sl = treesElements(*dr.slices);

		size_t fmax = 2047;
		auto dr2 = applicationer(fmax, *sl, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model113.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model114")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model112.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,4,6,8,10,12,14,12,18 };
		SizeList ys{ 2,4,6,8,10,12,14,12,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		auto sl = treesElements(*dr.slices);

		size_t fmax = 2047;
		auto dr2 = applicationer(fmax, *sl, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model114.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model115")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model112.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,4,6,8,10,12,14,12,18 };
		SizeList ys{ 2,4,6,8,10,12,14,12,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		auto sl = treesElements(*dr.slices);

		size_t fmax = 2048*16-1;
		auto dr2 = applicationer(fmax, *sl, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model115.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model115_1")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model112.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,4,6,8,10,12,14,12,18 };
		SizeList ys{ 2,4,6,8,10,12,14,12,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		auto sl = treesLeafElements(*dr.slices);

		size_t fmax = 2048 * 16 - 1;
		auto dr2 = applicationer(fmax, *sl, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model115_1.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "test")
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		string model = string(argv[2]);

		cout << "model: " << model << endl;

		std::unique_ptr<System> uu;
		std::unique_ptr<SystemRepa> ur;
		std::unique_ptr<HistoryRepa> hr;
		{
			auto xx = trainBucketedIO(2);
			uu = std::move(std::get<0>(xx));
			ur = std::move(std::get<1>(xx));
			hr = std::move(std::get<2>(xx));
		}

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		SizeList vvl1{ vvi[digit] };

		cout << "train size: " << hr->size << endl;

		StrVarPtrMap m;
		std::ifstream in(model + ".bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "model cardinality: " << fudRepasSize(*dr->fud) << endl;
		cout << "derived  cardinality: " << frder(*dr->fud)->size() << endl;
		cout << "underlying cardinality: " << frund(*dr->fud)->size() << endl;

		std::map<std::size_t, std::size_t> sp;
		{
			auto hr1 = frmul(*hr, *dr->fud);
			if (hr1->evient)
				hr1->transpose();
			auto z = hr1->size;
			auto& mvv = hr1->mapVarInt();
			auto sh = hr1->shape;
			auto rr = hr1->arr;
			auto pl = mvv[vvi[digit]];
			auto sl = sh[pl];
			auto nn = treesLeafNodes(*dr->slices);
			SizeList al(sl);
			for (auto& s : *nn)
			{
				for (std::size_t k = 0; k < sl; k++)
					al[k] = 0;
				auto pk = mvv[s.first];
				for (std::size_t j = 0; j < z; j++)
				{
					std::size_t u = rr[pk*z + j];
					if (u)
					{
						std::size_t w = rr[pl*z + j];
						al[w]++;
					}
				}
				std::size_t c = 0;
				std::size_t cl = sl;
				for (std::size_t k = 0; k < sl; k++)
				{
					auto u = al[k];
					if (u > c)
					{
						c = u;
						cl = k;
					}
				}
				sp[s.first] = cl;
			}

		}
		//cout << "sp" << endl
		//	<< sp << endl << endl;

		{
			auto xx = testBucketedIO(2);
			hr = std::move(std::get<2>(xx));
		}

		cout << "test size: " << hr->size << endl;

		std::size_t a = 0;
		std::size_t x = 0;
		{
			SizeList ww{ vvi[digit] };
			auto nn = treesLeafNodes(*dr->slices);
			for (auto& s : *nn)
				ww.push_back(s.first);
			auto hr1 = hrhrred(ww.size(), ww.data(), *frmul(*hr, *dr->fud));
			if (!hr1->evient)
				hr1->transpose();
			auto n = hr1->dimension;
			auto vv = hr1->vectorVar;
			auto sh = hr1->shape;
			auto z = hr1->size;
			auto rr = hr1->arr;
			auto sl = sh[0];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t cl = rr[j*n];
				for (std::size_t i = 1; i < n; i++)
				{
					std::size_t u = rr[j*n + i];
					if (u)
					{
						std::size_t l = sp[vv[i]];
						if (l == cl)
							a++;
						else if (l == sl)
							x++;
						break;
					}
				}
			}

		}
		cout << "effective size: " << hr->size - x << endl;
		cout << "matches: " << a << endl;

	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model116")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 128)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 18;
		size_t lmax = 8;
		size_t xmax = 128;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 1023;
		size_t mult = 1;
		size_t smin = 0;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, 0, omax, bmax, mmax, umax, pmax, fmax, mult, smin, seed, vvk1, FudRepa(), *hr, 0, *ur);
		std::ofstream out("model116.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model117")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 128)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 18;
		size_t lmax = 8;
		size_t xmax = 128;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 1023;
		size_t mult = 1;
		size_t smin = 100;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, 0, omax, bmax, mmax, umax, pmax, fmax, mult, smin, seed, vvk1, FudRepa(), *hr, 0, *ur);
		std::ofstream out("model117.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (argc >= 3 && string(argv[1]) == "bitmap_10x10")
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		string model = string(argv[2]);
		int zmin = argc >= 4 ? atoi(argv[3]) : 50;

		auto xx = trainBucketedRegionRandomIO(2, 10, 13);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 8)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
		}

		StrVarPtrMap m;
		std::ifstream in(model+".bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "frund(*dr->fud)->size()" << endl
			<< frund(*dr->fud)->size() << endl << endl;

		cout << "frvars(*dr->fud)->size()" << endl
			<< frvars(*dr->fud)->size() << endl << endl;

		auto hr1 = frmul(*hr, *dr->fud);
		if (hr1->evient)
			hr1->transpose();
		auto z = hr1->size;
		auto& mvv = hr1->mapVarInt();
		auto sl = treesElements(*dr->slices);
		std::map<std::size_t, std::shared_ptr<HistoryRepa>> shr;
		for (auto s : *sl)
		{
			SizeList ev;
			auto pk = mvv[s];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t u = hr1->arr[pk*z + j];
				if (u)
					ev.push_back(j);
			}
			shr[s] = move(hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1)));
		}
		auto ll = treesPaths(*dr->slices);
		vector<vector<pair<double, size_t>>> ll1;
		for (auto pp : *ll)
		{
			vector<pair<double, size_t>> pp1;
			for (auto s : pp)
				if (shr[s]->size >= zmin)
					pp1.push_back(pair<double, size_t>((double)shr[s]->size, s));
			if (pp1.size())
				ll1.push_back(pp1);
		}
		auto ll0 = *treesPaths(*pathsTree(ll1));
		sort(ll0.begin(), ll0.end());
		reverse(ll0.begin(), ll0.end());
		std::vector<Bitmap> ll2;
		for (auto pp : ll0)
		{
			std::vector<Bitmap> pp1;
			for (auto p : pp)
				if (p.first > 0)
					pp1.push_back(hrbm(10, 3, 2, *shr[p.second]));
			if (pp1.size())
				ll2.push_back(bmhstack(pp1));
		}
		bmwrite(model + ".bmp", bmvstack(ll2));
	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model118")

	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsHistoryRepasApplicationerMaxRollByMExcludedSelfHighestFmaxIORepa;

		auto xx = trainBucketedRegionRandomIO(2, 10, 13);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 4;
		size_t lmax = 8;
		size_t xmax = 128;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 1023;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, omax, bmax, mmax, umax, pmax, fmax, mult, seed, vvk1, *hr, *ur);
		std::ofstream out("model118.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 3000)
			ll.push_back(i);
		auto hr = hrsel(ll.size(), ll.data(), *hrtr);
		hrtr.reset();
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model118.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,4,6,8,10,12,14,12,18 };
		SizeList ys{ 2,4,6,8,10,12,14,12,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		SizeSizeUMap vvx;
		SizeSizeUMap vvy;
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						auto i = llu.size() - 1;
						nn[x1] = i;
						vvx[i] = x;
						vvy[i] = y;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		//auto sl = treesLeafElements(*dr.slices);
		//cout << "sl->size()" << endl
		//	<< sl->size() << endl << endl;

		auto ll2 = treesPaths(*dr.slices);

		std::vector<Bitmap> ll1;
		for (size_t i = 0; i < hr->size; i++)
		{
			std::vector<Bitmap> pp;
			SizeList ev{ i };
			pp.push_back(hrbm(28, 1, 2, *hrhrred(vvk1.size(), vvk1.data(), *hrsel(ev.size(), ev.data(), *hr1))));
			ll1.push_back(bmhstack(pp));
		}
		bmwrite("M5FA.bmp", bmvstack(ll1));
	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto vol = systemsSetVarsVolume_u;
		auto aall = histogramsList;
		auto cart = systemsSetVarsSetStateCartesian_u;
		auto single = histogramSingleton_u;
		auto aaar = systemsHistogramsHistogramRepa_u;
		auto araa = systemsHistogramRepasHistogram_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto hrhrsel = [](const HistoryRepa& hr, const HistoryRepa& ss)
		{
			return historyRepasHistoryRepasHistoryRepaSelection_u(ss, hr);
		};
		auto hrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasReduce_u(1.0, m, kk1.data(), hr);
		};
		auto hrhrred = [](const HistoryRepa& hr, const SystemRepa& ur, const VarUSet& kk)
		{
			auto& vvi = ur.mapVarSize();
			std::size_t m = kk.size();
			auto kk0 = sorted(kk);
			SizeList kk1;
			for (auto& v : kk0)
				kk1.push_back(vvi[v]);
			return setVarsHistoryRepasHistoryRepaReduced_u(m, kk1.data(), hr);
		};

		auto xx = trainBucketedAffineIO(2,3,0.2,17);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < 50; i++)
			for (size_t j = 0; j < 3; j++)
				ll.push_back(i + 60000*j);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto hr1 = hrhrred(*hr, *ur, vvk);

		std::vector<Bitmap> bmv;
		for (size_t i = 0; i < 50; i++)
		{
			std::vector<Bitmap> bmh;
			for (size_t j = 0; j < 3; j++)
				bmh.push_back(bmborder(1, hrbm(28, 2, 2, *hrsel(*hr1, SizeList{ i*3+j }))));
			bmv.push_back(bmhstack(bmh));
		}
		bmwrite("affine.bmp", bmvstack(bmv));
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model119")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_up;

		size_t tint = argc >= 4 ? atoi(argv[3]) : 1;

		auto xx = trainBucketedAffineIO(2, 10, 0.2, 17);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model112.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,4,6,8,10,12,14,12,18 };
		SizeList ys{ 2,4,6,8,10,12,14,12,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		auto sl = treesElements(*dr.slices);

		size_t fmax = 2048*8-1;
		auto dr2 = applicationer(fmax, tint, *sl, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model119.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model120")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_up;

		size_t tint = argc >= 4 ? atoi(argv[3]) : 1;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model112.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr1 = persistentsApplicationRepa(in);
		in.close();
		auto& llu1 = ur1->listVarSizePair;
		VarSizeUMap ur0 = ur->mapVarSize();
		auto n = fudRepasSize(*dr1->fud);
		size_t a = 28;
		size_t b = 10;
		SizeList xs{ 2,4,6,8,10,12,14,12,18 };
		SizeList ys{ 2,4,6,8,10,12,14,12,18 };
		auto& llu = ur->listVarSizePair;
		ApplicationRepa dr;
		{
			llu.reserve(n * xs.size() * ys.size() + a*a);
			dr.slices = std::make_shared<SizeTree>();
			dr.slices->_list.reserve(dr1->slices->_list.size() * xs.size() * ys.size());
			dr.fud = std::make_shared<FudRepa>();
			dr.fud->layers.reserve(dr1->fud->layers.size() * xs.size() * ys.size());
			dr.substrate.reserve(dr1->substrate.size() * xs.size() * ys.size());
		}
		for (auto x : xs)
			for (auto y : ys)
			{
				auto dr2 = drcopy(*dr1);
				SizeSizeUMap nn;
				nn.reserve(n + b*b);
				for (auto x1 : dr1->substrate)
				{
					auto& p = llu1[x1];
					auto vx = std::make_shared<Variable>((int)(p.first->_var0->_int + x - 1));
					auto vy = std::make_shared<Variable>((int)(p.first->_var1->_int + y - 1));
					auto v = std::make_shared<Variable>(vx, vy);
					nn[x1] = ur0[*v];
				}
				auto vx1 = std::make_shared<Variable>((int)x);
				auto vy1 = std::make_shared<Variable>((int)y);
				auto vd1 = std::make_shared<Variable>(vx1, vy1);
				for (auto& ll : dr1->fud->layers)
					for (auto& tr : ll)
					{
						auto x1 = tr->derived;
						auto& p = llu1[x1];
						auto vdfl = p.first->_var0;
						auto vb = p.first->_var1;
						auto vdf = vdfl->_var0;
						auto vl = vdfl->_var1;
						auto vf = vdf->_var1;
						auto vdf1 = std::make_shared<Variable>(vd1, vf);
						auto vdfl1 = std::make_shared<Variable>(vdf1, vl);
						auto vdflb1 = std::make_shared<Variable>(vdfl1, vb);
						llu.push_back(VarSizePair(vdflb1, p.second));
						nn[x1] = llu.size() - 1;
					}
				dr2->reframe_u(nn);
				dr.slices->_list.insert(dr.slices->_list.end(), dr2->slices->_list.begin(), dr2->slices->_list.end());
				dr.fud->layers.insert(dr.fud->layers.end(), dr2->fud->layers.begin(), dr2->fud->layers.end());
				dr.substrate.insert(dr.substrate.end(), dr2->substrate.begin(), dr2->substrate.end());
			}

		auto hr1 = frmul(*hr, *dr.fud);

		auto sl = treesElements(*dr.slices);

		size_t fmax = 2047;
		auto dr2 = applicationer(fmax, tint, *sl, vvi[digit], *hr1, 1, *ur);
		auto dr3 = drjoin(dr, *dr2);
		std::ofstream out("model120.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "condition" && string(argv[2]) == "model106_2_p")
	{
		auto uvars = systemsSetVar;
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto drcopy = applicationRepasApplicationRepa_u;
		auto drjoin = applicationRepaPairsJoin_u;
		auto applicationer = parametersSystemsHistoryRepasApplicationerCondMultinomialFmaxIORepa_up;

		size_t tint = argc >= 4 ? atoi(argv[3]) : 1;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		std::unique_ptr<HistoryRepa> hr;
		{
			SizeList ll;
			for (size_t i = 0; i < hrtr->size; i += 2)
				ll.push_back(i);
			hr = hrsel(ll.size(), ll.data(), *hrtr);
			cout << "hr->size" << endl
				<< hr->size << endl << endl;
			hrtr.reset();
		}

		StrVarPtrMap m;
		std::ifstream in("model106.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		auto hr1 = frmul(*hr, *dr->fud);

		SizeList vvk2;
		for (std::size_t i = 0; i < hr1->dimension; i++)
			vvk2.push_back(hr1->vectorVar[i]);

		size_t fmax = 1023;
		auto dr2 = applicationer(fmax, tint, vvk2, vvi[digit], *hr1, 1, *ur1);
		auto dr3 = drjoin(*dr, *dr2);
		std::ofstream out("model106_2_p.bin", std::ios::binary);
		systemRepasPersistent(*ur1, out); cout << endl;
		applicationRepasPersistent(*dr3, out); cout << endl;
		out.close();
	}

	if (argc >= 3 && string(argv[1]) == "affine_test")
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;

		string model = string(argv[2]);

		cout << "model: " << model << endl;

		std::unique_ptr<System> uu;
		std::unique_ptr<SystemRepa> ur;
		std::unique_ptr<HistoryRepa> hr;
		{
			auto xx = trainBucketedAffineIO(2, 10, 0.2, 17);
			uu = std::move(std::get<0>(xx));
			ur = std::move(std::get<1>(xx));
			hr = std::move(std::get<2>(xx));
		}

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		SizeList vvk1;
		for (auto& v : sorted(vvk))
			vvk1.push_back(vvi[v]);

		SizeList vvl1{ vvi[digit] };

		cout << "train size: " << hr->size << endl;

		StrVarPtrMap m;
		std::ifstream in(model + ".bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		cout << "model cardinality: " << fudRepasSize(*dr->fud) << endl;
		cout << "derived  cardinality: " << frder(*dr->fud)->size() << endl;
		cout << "underlying cardinality: " << frund(*dr->fud)->size() << endl;

		std::map<std::size_t, std::size_t> sp;
		{
			auto hr1 = frmul(*hr, *dr->fud);
			if (hr1->evient)
				hr1->transpose();
			auto z = hr1->size;
			auto& mvv = hr1->mapVarInt();
			auto sh = hr1->shape;
			auto rr = hr1->arr;
			auto pl = mvv[vvi[digit]];
			auto sl = sh[pl];
			auto nn = treesLeafNodes(*dr->slices);
			SizeList al(sl);
			for (auto& s : *nn)
			{
				for (std::size_t k = 0; k < sl; k++)
					al[k] = 0;
				auto pk = mvv[s.first];
				for (std::size_t j = 0; j < z; j++)
				{
					std::size_t u = rr[pk*z + j];
					if (u)
					{
						std::size_t w = rr[pl*z + j];
						al[w]++;
					}
				}
				std::size_t c = 0;
				std::size_t cl = sl;
				for (std::size_t k = 0; k < sl; k++)
				{
					auto u = al[k];
					if (u > c)
					{
						c = u;
						cl = k;
					}
				}
				sp[s.first] = cl;
			}

		}
		//cout << "sp" << endl
		//	<< sp << endl << endl;

		{
			auto xx = testBucketedIO(2);
			hr = std::move(std::get<2>(xx));
		}

		cout << "test size: " << hr->size << endl;

		std::size_t a = 0;
		std::size_t x = 0;
		{
			SizeList ww{ vvi[digit] };
			auto nn = treesLeafNodes(*dr->slices);
			for (auto& s : *nn)
				ww.push_back(s.first);
			auto hr1 = hrhrred(ww.size(), ww.data(), *frmul(*hr, *dr->fud));
			if (!hr1->evient)
				hr1->transpose();
			auto n = hr1->dimension;
			auto vv = hr1->vectorVar;
			auto sh = hr1->shape;
			auto z = hr1->size;
			auto rr = hr1->arr;
			auto sl = sh[0];
			for (std::size_t j = 0; j < z; j++)
			{
				std::size_t cl = rr[j*n];
				for (std::size_t i = 1; i < n; i++)
				{
					std::size_t u = rr[j*n + i];
					if (u)
					{
						std::size_t l = sp[vv[i]];
						if (l == cl)
							a++;
						else if (l == sl)
							x++;
						break;
					}
				}
			}

		}
		cout << "effective size: " << hr->size - x << endl;
		cout << "matches: " << a << endl;

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frmul_p = historyRepasFudRepasMultiply_up;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;
		auto llfr = setVariablesListTransformRepasFudRepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);
		SizeUSet vvk2;
		for (auto& v : vvk0)
			vvk2.insert(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model106.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		{
			SizeList ss;
			for (auto& ll : dr->fud->layers)
				ss.push_back(ll.size());

			cout << "fudRepasSize(*dr->fud)" << endl
				<< fudRepasSize(*dr->fud) << endl << endl;

			cout << "dr->fud->layers.size()" << endl
				<< dr->fud->layers.size() << endl << endl;

			cout << "dr->fud->layers" << endl
				<< sorted(ss) << endl << endl;
		}

		{
			auto mark = clk::now();
			auto hr1 = frmul(*hr, *dr->fud);
			cout << "frmul " << ((sec)(clk::now() - mark)).count() << "s" << endl; 
			std::size_t h = 0;
			std::size_t s = 0;
			auto n = hr1->dimension;
			auto z = hr1->size;
			for (std::size_t j = 0; j < z; j++)
				for (std::size_t i = 0; i < n; i++)
				{
					h = 23*h + hr1->arr[j*n + i];
					s += hr1->arr[j*n + i];
				}
			cout << "hash: " << h << endl;
			cout << "sum: " << s << endl << endl;
		}

		{
			auto mark = clk::now();
			auto hr1 = frmul_p(4, *hr, *dr->fud);
			cout << "frmul_p " << ((sec)(clk::now() - mark)).count() << "s" << endl;
			std::size_t h = 0;
			std::size_t s = 0;
			auto n = hr1->dimension;
			auto z = hr1->size;
			for (std::size_t j = 0; j < z; j++)
				for (std::size_t i = 0; i < n; i++)
				{
					h = 23 * h + hr1->arr[j*n + i];
					s += hr1->arr[j*n + i];
				}
			cout << "hash: " << h << endl;
			cout << "sum: " << s << endl << endl;
		}

		{
			auto mark = clk::now();
			TransformRepaPtrList tt;
			tt.reserve(fudRepasSize(*dr->fud));
			for (auto& ll : dr->fud->layers)
				for (auto& tr : ll)
					tt.push_back(tr);
			auto fr = llfr(vvk2, tt);
			cout << "llfr " << ((sec)(clk::now() - mark)).count() << "s" << endl;
			SizeList ss;
			for (auto& ll : fr->layers)
				ss.push_back(ll.size());
			cout << "fudRepasSize(*fr)" << endl
				<< fudRepasSize(*fr) << endl << endl;
			cout << "fr->layers.size()" << endl
				<< fr->layers.size() << endl << endl;
			cout << "fr->layers" << endl
				<< ss << endl << endl;
			mark = clk::now();
			auto hr1 = frmul_p(4, *hr, *fr);
			cout << "frmul_p " << ((sec)(clk::now() - mark)).count() << "s" << endl;
			std::size_t h = 0;
			std::size_t s = 0;
			auto n = hr1->dimension;
			auto z = hr1->size;
			for (std::size_t j = 0; j < z; j++)
				for (std::size_t i = 0; i < n; i++)
				{
					h = 23 * h + hr1->arr[j*n + i];
					s += hr1->arr[j*n + i];
				}
			cout << "hash: " << h << endl;
			cout << "sum: " << s << endl << endl;
		}
		/*
		fudRepasSize(*dr->fud)
		15421

		dr->fud->layers.size()
		3735

		dr->fud->layers
		[1,1,1,1
		...
		,17,17]

		frmul 5.98771s
		hash: 14485459118646729375
		sum: 348224699

		frmul_p 5.18827s
		hash: 14485459118646729375
		sum: 348224699

		llfr 0.0257498s
		fudRepasSize(*fr)
		15421

		fr->layers.size()
		18

		fr->layers
		[6910,3463,1163,337,92,37,44,84,151,249,434,669,833,595,266,78,13,3]

		frmul_p 1.80618s
		hash: 9834352411011248031
		sum: 348224699
		*/

	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model100_p")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa_p;

		size_t tint = argc >= 4 ? atoi(argv[3]) : 1;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

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
		auto dr = applicationer(wmax, lmax, xmax, 0, omax, bmax, mmax, umax, pmax, fmax, mult, 0, seed, tint, vvk1, FudRepa(), *hr, 0, *ur);
		std::ofstream out("model100_p.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model121")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa_p;

		size_t tint = argc >= 4 ? atoi(argv[3]) : 1;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hrtr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		cout << "hrtr->dimension" << endl
			<< hrtr->dimension << endl << endl;
		cout << "hrtr->size" << endl
			<< hrtr->size << endl << endl;

		SizeList ll;
		for (size_t i = 0; i < hrtr->size; i += 8)
			ll.push_back(i);
		auto hr = hrsel(*hrtr, ll);
		cout << "hr->dimension" << endl
			<< hr->dimension << endl << endl;
		cout << "hr->size" << endl
			<< hr->size << endl << endl;

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 2048;
		size_t lmax = 8;
		size_t xmax = 1024;
		size_t omax = 30;
		size_t bmax = 30 * 3;
		size_t mmax = 3;
		size_t umax = 256;
		size_t pmax = 1;
		size_t fmax = 3;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, 0, omax, bmax, mmax, umax, pmax, fmax, mult, 0, seed, tint, vvk1, FudRepa(), *hr, 0, *ur);
		std::ofstream out("model121.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (argc >= 3 && string(argv[1]) == "induce" && string(argv[2]) == "model106_p")
	{
		auto uvars = systemsSetVar;
		auto hrsel = [](const HistoryRepa& hr, const SizeList& ll)
		{
			return eventsHistoryRepasHistoryRepaSelection_u(ll.size(), (std::size_t*)ll.data(), hr);
		};
		auto applicationer = parametersSystemsFudRepasHistoryRepasApplicationerSubstrateEntropyMaxRollByMExcludedSelfHighestFmaxIORepa_p;

		size_t tint = argc >= 4 ? atoi(argv[3]) : 1;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);

		size_t wmax = 4;
		size_t lmax = 8;
		size_t xmax = 128;
		double znnmax = 60000.0 * 2.0 * 100.0 * 100.0;
		size_t omax = 10;
		size_t bmax = 10 * 3;
		size_t mmax = 3;
		size_t umax = 128;
		size_t pmax = 1;
		size_t fmax = 1023;
		size_t mult = 1;
		size_t seed = 5;
		auto dr = applicationer(wmax, lmax, xmax, znnmax, omax, bmax, mmax, umax, pmax, fmax, mult, 0, seed, tint, vvk1, FudRepa(), *hr, 0, *ur);
		std::ofstream out("model106_p.bin", std::ios::binary);
		systemRepasPersistent(*ur, out); cout << endl;
		applicationRepasPersistent(*dr, out); cout << endl;
		out.close();

	}

	if (false)
	{
		auto uvars = systemsSetVar;
		auto single = histogramSingleton_u;
		auto aahr = [](const System& uu, const SystemRepa& ur, const Histogram& aa)
		{
			return systemsHistoriesHistoryRepa_u(uu, ur, *histogramsHistory_u(aa));
		};
		auto hrsel = eventsHistoryRepasHistoryRepaSelection_u;
		auto hrhrred = setVarsHistoryRepasHistoryRepaReduced_u;
		auto hrred = setVarsHistoryRepasReduce_u;
		auto frmul = historyRepasFudRepasMultiply_u;
		auto frmul_p = historyRepasFudRepasMultiply_up;
		auto frvars = fudRepasSetVar;
		auto frder = fudRepasDerived;
		auto frund = fudRepasUnderlying;
		auto frdep = fudRepasSetVarsDepends;
		auto llfr = setVariablesListTransformRepasFudRepa_u;

		auto xx = trainBucketedIO(2);
		auto& uu = std::get<0>(xx);
		auto& ur = std::get<1>(xx);
		auto& hr = std::get<2>(xx);

		Variable digit("digit");
		auto vv = *uvars(*uu);
		auto vvl = VarUSet();
		vvl.insert(digit);
		auto vvk = VarUSet(vv);
		vvk.erase(digit);

		auto& vvi = ur->mapVarSize();
		auto vvk0 = sorted(vvk);
		SizeList vvk1;
		for (auto& v : vvk0)
			vvk1.push_back(vvi[v]);
		SizeUSet vvk2;
		for (auto& v : vvk0)
			vvk2.insert(vvi[v]);

		StrVarPtrMap m;
		std::ifstream in("model106_p.bin", std::ios::binary);
		auto ur1 = persistentsSystemRepa(in, m);
		auto dr = persistentsApplicationRepa(in);
		in.close();

		{
			SizeList ss;
			for (auto& ll : dr->fud->layers)
				ss.push_back(ll.size());

			cout << "fudRepasSize(*dr->fud)" << endl
				<< fudRepasSize(*dr->fud) << endl << endl;

			cout << "dr->fud->layers.size()" << endl
				<< dr->fud->layers.size() << endl << endl;

			cout << "dr->fud->layers" << endl
				<< ss << endl << endl;
		}

		{
			auto mark = clk::now();
			auto hr1 = frmul(*hr, *dr->fud);
			cout << "frmul " << ((sec)(clk::now() - mark)).count() << "s" << endl;
			std::size_t h = 0;
			std::size_t s = 0;
			auto n = hr1->dimension;
			auto z = hr1->size;
			for (std::size_t j = 0; j < z; j++)
				for (std::size_t i = 0; i < n; i++)
				{
					h = 23 * h + hr1->arr[j*n + i];
					s += hr1->arr[j*n + i];
				}
			cout << "hash: " << h << endl;
			cout << "sum: " << s << endl << endl;
		}

		{
			auto mark = clk::now();
			auto hr1 = frmul_p(4, *hr, *dr->fud);
			cout << "frmul_p " << ((sec)(clk::now() - mark)).count() << "s" << endl;
			std::size_t h = 0;
			std::size_t s = 0;
			auto n = hr1->dimension;
			auto z = hr1->size;
			for (std::size_t j = 0; j < z; j++)
				for (std::size_t i = 0; i < n; i++)
				{
					h = 23 * h + hr1->arr[j*n + i];
					s += hr1->arr[j*n + i];
				}
			cout << "hash: " << h << endl;
			cout << "sum: " << s << endl << endl;
		}

		{
			auto mark = clk::now();
			TransformRepaPtrList tt;
			tt.reserve(fudRepasSize(*dr->fud));
			for (auto& ll : dr->fud->layers)
				for (auto& tr : ll)
					tt.push_back(tr);
			auto fr = llfr(vvk2, tt);
			cout << "llfr " << ((sec)(clk::now() - mark)).count() << "s" << endl;
			SizeList ss;
			for (auto& ll : fr->layers)
				ss.push_back(ll.size());
			cout << "fudRepasSize(*fr)" << endl
				<< fudRepasSize(*fr) << endl << endl;
			cout << "fr->layers.size()" << endl
				<< fr->layers.size() << endl << endl;
			cout << "fr->layers" << endl
				<< ss << endl << endl;
			mark = clk::now();
			auto hr1 = frmul_p(4, *hr, *fr);
			cout << "frmul_p " << ((sec)(clk::now() - mark)).count() << "s" << endl;
			std::size_t h = 0;
			std::size_t s = 0;
			auto n = hr1->dimension;
			auto z = hr1->size;
			for (std::size_t j = 0; j < z; j++)
				for (std::size_t i = 0; i < n; i++)
				{
					h = 23 * h + hr1->arr[j*n + i];
					s += hr1->arr[j*n + i];
				}
			cout << "hash: " << h << endl;
			cout << "sum: " << s << endl << endl;
		}
		/*
		fudRepasSize(*dr->fud)
		15423

		dr->fud->layers.size()
		29

		dr->fud->layers
		[6922,3473,1161,326,83,28,8,23,8,45,22,80,44,120,70,238,116,413,221,575,339,459,279,186,117,37,20,3,7]

		frmul 6.17454s
		hash: 7553982042899864222
		sum: 348265622

		frmul_p 1.76259s
		hash: 7553982042899864222
		sum: 348265622

		llfr 0.0189569s
		fudRepasSize(*fr)
		15423

		fr->layers.size()
		18

		fr->layers
		[6922,3473,1161,326,90,32,43,85,151,249,434,672,833,592,266,78,13,3]

		frmul_p 1.90916s
		hash: 5649481198801195934
		sum: 348265622
		*/

	}


	return 0;
}

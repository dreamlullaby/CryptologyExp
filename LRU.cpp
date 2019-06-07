#include<iostream>
#include<queue>
#include<string>
#include<fstream>
#include<bitset>
#include<iomanip>
using namespace std;
class cache_counter //counter
{
	string *pframes;
	int* pcounter;
	int cache_size;
	int frame_index;
public:
	cache_counter(int nframe = 4) 
	{ 
		pframes = new string[nframe]; 
		pcounter = new int[nframe]; 
		cache_size = nframe; 
		
		frame_index = 0; 
		for (int i = 0; i < nframe; i++) { pframes[i] =" ";pcounter[i] =  0 ; }
	}
	bool visit_cache(string frameid) 
	{

		if (frame_index < cache_size)
		{
			pframes[frame_index] = frameid;
			for (int i = 0; i < frame_index; i++) pcounter[i]++;
			frame_index++;
			//cout <<pframes[frame_index-1]<< "miss" << endl;
			return false;
		}
		else 
		{
			if (incache(frameid)>=0) 
			{
				//cout << "hit " << pframes[incache(frameid)] << endl; 
				pcounter[incache(frameid)] = 0;
				for (int i = 0; i < frame_index; i++) { if (i == incache(frameid)) continue; pcounter[i]++; }
				return true;
			}
			else 
			{
				int key = 0;
				int tmp = -1;
				for (int i = 0; i < cache_size; i++)
				{
					if (pcounter[i] > tmp) { key = i; tmp = pcounter[i]; }
				}
				//cout << "miss, remove page " << pframes[key] << endl;
				pframes[key] = frameid;
				pcounter[key] = 0;
				for (int i = 0; i < frame_index; i++) { if (i ==key) continue; pcounter[i]++; }
				return false;
			}
		}
	}
	int incache(string frameid)
	{
		for (int i = 0; i < cache_size; i++) { if (frameid == pframes[i]) return i; }
		return -1;
	}
};
class cache_stack
{
	queue<string>* pframes,*tmp;
	int cache_size;
	int frame_index;
public:
	cache_stack(int nframe)
	{
		pframes = new queue<string>;
		tmp=new queue<string>;
		cache_size = nframe;
		frame_index = 0;
	}
	bool visit_cache(string frameid)
	{
		if (frame_index < cache_size)
		{
			pframes->push(frameid);
			frame_index++;
			//cout << frameid << "  miss" << endl;
			return false;
		}
		else
		{
			if (incache(frameid))
			{
				for(int i=0;i<cache_size;i++)
				{
					string id = pframes->front();
					pframes->pop();
					if (id == frameid) continue;
					tmp->push(id);
				}
				while (tmp->size() != 0)
				{
					string id = tmp->front();
					tmp->pop();
					pframes->push(id);
				}
				pframes->push(frameid);
				//cout << "hit " << frameid << endl;
				return true;
			}

			else
			{
				pframes->pop();
				pframes->push(frameid);
				//cout << "miss, remove page " << frameid << endl;
				return false;
			}
		}
	}
	bool incache(string frameid)//
	{
		int loop = cache_size;
		bool flag = false;
		for(int i=0;i<loop;i++)
		{
			string tmp = pframes->front();
			if (tmp == frameid)	 flag=true;
			pframes->pop();
			pframes->push(tmp);
		}
		return flag;
	}
};
class cache_ARB //additonal reference bits
{
	string *pframes;
	bitset<8>* parb;
	int cache_size;
	int frame_index;
	bitset<8> c;
public:
	cache_ARB(int nframe)
	{
		pframes = new string[nframe];
		parb = new bitset<8>[nframe];
		cache_size = nframe;
		frame_index = 0;
		for (int i = 0; i < nframe; i++) { pframes[i] = " ";}
		c = bitset<8>(string("10000000"));
	}
	bool visit_cache(string frameid)
	{

		if (frame_index < cache_size)
		{
			pframes[frame_index] = frameid;
			for (int i = 0; i < frame_index; i++) {
				parb[i]=parb[i]>>1; 
			}
			parb[frame_index] = c;
			frame_index++;
			//cout <<pframes[frame_index-1]<< "miss" << endl;
			return false;
		}
		else
		{
			if (incache(frameid) >= 0)
			{
				//cout << "hit " << pframes[incache(frameid)] << endl; 
				int pos = incache(frameid);
				for (int i = 0; i < cache_size; i++) { parb[i]>>=1;}
				parb[pos] |= c;
				return true;
			}
			else
			{
				int key = 0;
				unsigned long tmp = 256;
				for (int i = 0; i < cache_size; i++)
				{
					if (parb[i].to_ulong()<tmp) { key = i; tmp = parb[i].to_ulong(); }
				}
				//cout << "miss, remove page " << pframes[key] << endl;
				pframes[key] = frameid;
				for (int i = 0; i < cache_size; i++) { parb[i] >>=1; }
				parb[key] = c;
				return false;
			}
		}
	}
	int incache(string frameid)
	{
		for (int i = 0; i < cache_size; i++) { if (frameid == pframes[i]) return i; }
		return -1;
	}
};
class cache_2ndchance
{
	string *pframes;
	int* pcounter;
	int* status;
	int cache_size;
	int frame_index;
public:
	cache_2ndchance(int nframe)
	{
		pframes = new string[nframe];
		pcounter = new int[nframe];
		status = new int[nframe];
		cache_size = nframe;

		frame_index = 0;
		for (int i = 0; i < nframe; i++) { pframes[i] = " "; pcounter[i] = 0; status[i] = 0; }
	}
	bool visit_cache(string frameid)
	{

		if (frame_index < cache_size)
		{
			pframes[frame_index] = frameid;
			status[frame_index] = 1;
			for (int i = 0; i < frame_index; i++) pcounter[i]++;
			frame_index++;
			//cout <<pframes[frame_index-1]<< "miss" << endl;
			return false;
		}
		else
		{
			if (incache(frameid) >= 0)
			{
				//cout << "hit " << pframes[incache(frameid)] << endl; 
				int pos = incache(frameid);
				pcounter[pos] = 0;
				status[pos]= 1;
				for (int i = 0; i < frame_index; i++) { if (i == incache(frameid)) continue; pcounter[i]++; }
				return true;
			}
			else
			{
				int key = 0,tmp = -1,st = -1,i=0;
				int loop = cache_size;
				while (loop>0) 
				{
					for ( i = 0; i < cache_size; i++)
					{
						if (pcounter[i] > tmp) { key = i; tmp = pcounter[i]; st = status[i]; }
					}
					if (st == 0) break;
					else { pcounter[i] = 0; status[i] = 0; }
					loop--;
				}
				//cout << "miss, remove page " << pframes[key] << endl;
				pframes[key] = frameid;
				pcounter[key] = 0;
				for (int i = 0; i < frame_index; i++) { if (i == key) continue; pcounter[i]++; }
				return false;
			}
		}
	}
	int incache(string frameid)
	{
		for (int i = 0; i < cache_size; i++) { if (frameid == pframes[i]) return i; }
		return -1;
	}

};

int main()
{
	int args[4] = { 8,16,32,64 };
	fstream trace,output;
	string tracefile[3] = { "E:\\gpp","E:\\top.out","E:\\emacs.small" };
	output.open("E:\\OS exp4 result.txt");
	for (int j = 0; j < 3; j++)
	{
		cout << "current tracing file: " << tracefile[j] << endl;
		for (int i = 0; i < 4; i++)		//counter位实现的lru
		{
			if (i == 0) cout << "  current algorithm: LRU" << endl;
			trace.open(tracefile[j]);
			int npages = 0, nhit = 0, nmiss = 0;
			cache_counter c1(args[i]);
			string paddr, mode, page, space = " ";
			while (trace >> paddr >> mode) { page = paddr + space + mode; bool res = c1.visit_cache(page); npages++; if (res) nhit++; if (!res) nmiss++; }
			cout << "    nframes=" << args[i] << " ,hits: " << nhit << " ,miss: " << nmiss << " ,fault ratio:  " << float(nmiss) / float(npages) << " ,hit ratio:  " << float(nhit) / float(npages) << endl;
			output << "    nframes=" << args[i] << " ,hits: " << nhit << " ,miss: " << nmiss << " ,fault ratio:  " << float(nmiss) / float(npages) << " ,hit ratio:  " << float(nhit) / float(npages) << endl;
			trace.close();
		}

		/*
		for (int i = 0; i < 4; i++) //stack 实现的lru
		{
			trace.open("E:\\gpp");
			int npages = 0, nhit = 0, nmiss = 0;
			cache_stack c2(args[i]);
			string paddr, mode, page, space = " ";
			while (trace >> paddr >> mode) { page = paddr + space + mode; bool res = c2.visit_cache(page); npages++; if (res) nhit++; if (!res) nmiss++; }
			cout << "nframes=" << args[i] << " ,hits: " << nhit << " ,miss: " << nmiss << " ,fault ratio:  " << float(nmiss) / float(npages) << endl;
			trace.close();
		}
		*/
		for (int i = 0; i < 4; i++)	//additional reference bits 近似lru算法
		{
			if (i == 0) cout << "  current algorithm: Additional Reference Bits" << endl;
			trace.open(tracefile[j]);
			int npages = 0, nhit = 0, nmiss = 0;
			cache_ARB c3(args[i]);
			string paddr, mode, page, space = " ";
			while (trace >> paddr >> mode) { page = paddr + space + mode; bool res = c3.visit_cache(page); npages++; if (res) nhit++; if (!res) nmiss++; }
			cout << "    nframes=" << args[i] << " ,hits: " << nhit << " ,miss: " << nmiss << " ,fault ratio:  " << float(nmiss) / float(npages) << " ,hit ratio:  " << float(nhit) / float(npages) << endl;
			output << "    nframes=" << args[i] << " ,hits: " << nhit << " ,miss: " << nmiss << " ,fault ratio:  " << float(nmiss) / float(npages) << " ,hit ratio:  " << float(nhit) / float(npages) << endl;
			trace.close();
		}

		for (int i = 0; i < 4; i++)	//second chance 近似lru算法
		{
			if (i == 0) cout << "  current algorithm: second chance" << endl;
			trace.open(tracefile[j]);
			int npages = 0, nhit = 0, nmiss = 0;
			cache_2ndchance c4(args[i]);
			string paddr, mode, page, space = " ";
			while (trace >> paddr >> mode) { page = paddr + space + mode; bool res = c4.visit_cache(page); npages++; if (res) nhit++; if (!res) nmiss++; }
			cout << "    nframes=" << args[i] << " ,hits: " << nhit << " ,miss: " << nmiss << " ,fault ratio:  " << float(nmiss) / float(npages) << " ,hit ratio:  " << float(nhit) / float(npages) << endl;
			output << "    nframes=" << args[i] << " ,hits: " << nhit << " ,miss: " << nmiss << " ,fault ratio:  " << float(nmiss) / float(npages) << " ,hit ratio:  " << float(nhit) / float(npages) << endl;
			trace.close();
		}
	}
	output.close();
	return 0;
}
//
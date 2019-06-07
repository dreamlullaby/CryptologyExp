#include<iostream>
using namespace std;
#define buffersize 20
class buffer
{
	int buff[buffersize];
	int in_ptr;
	int out_ptr;
public:
	buffer() { for (int i = 0; i < buffersize; i++) buff[i] = 0; in_ptr = 0; out_ptr = 0; }
	void item_insert(int item) {
		buff[in_ptr] = item;
		in_ptr = (in_ptr + 1) % buffersize;
		cout << "put " << item << " into buffer" << endl;
	}
	void item_remove() {
		cout << "remove " <<buff[out_ptr]<< " from buffer" << endl;
		out_ptr = (out_ptr + 1) % buffersize;
	}

};

buffer buf;
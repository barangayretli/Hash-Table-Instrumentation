#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <ostream>
#include "LinearProbing.h"

using namespace std;

const int sizeHash=10007;

struct table
{
	double loadfactor;
	int probe;
    int visit_count;
	table (double x=0.0, int p=0)
		: loadfactor(x), probe (p), visit_count (p)
	{}
};

table insert_suc[sizeHash+1];table insert_fail[sizeHash+1];table delete_suc[sizeHash+1];table delete_fail[sizeHash+1];table find_suc[sizeHash+1];table find_fail[sizeHash+1];

int main()
{
	ofstream output1, output2, output3, output4, output5, output6;
	output1.open("file1.csv");output2.open("file2.csv");output3.open("file3.csv");output4.open("file4.csv");output5.open("file5.csv");output6.open("file6.csv"); //open csv files to store the data 
	
	srand(5);//random number sequence

	HashTable hashx;//hashtable initialazation

	int probe=0;

	for(int i=0; i<1000000 && !hashx.isFull();i++)// do this until either the hash table is full or 1.000.000 iteration is done
	{
		int k=hashx.getCurrentSize();//k is the currentSize of hashtable
		int temp = rand()%8;//temp is btw 0-7
		int alfa = rand()%(sizeHash/20);// the number to insert, delete or find
		if(temp<2)//insert
		{
			
			if(hashx.insert(alfa,probe))
			{
				insert_suc[k].loadfactor=hashx.getLoadFactor();
				insert_suc[k].probe+=probe;
				insert_suc[k].visit_count++;
			}
			else
			{
				insert_fail[k].loadfactor=hashx.getLoadFactor();
				insert_fail[k].probe+=probe;
				insert_fail[k].visit_count++;
			}
		}
		else if(temp==2)//delete
		{
			
			if(hashx.remove(alfa,probe))
			{
				delete_suc[k].loadfactor=hashx.getLoadFactor();
				delete_suc[k].probe+=probe;
				delete_suc[k].visit_count++;
			}
			else
			{
				delete_fail[k].loadfactor=hashx.getLoadFactor();
				delete_fail[k].probe+=probe;
				delete_fail[k].visit_count++;
			}
		}
		else//find
		{
			if(hashx.find(alfa,probe))
			{
				find_suc[k].loadfactor=hashx.getLoadFactor();
				find_suc[k].probe+=probe;
				find_suc[k].visit_count++;
			}
			else
			{
				find_fail[k].loadfactor=hashx.getLoadFactor();
				find_fail[k].probe+=probe;
				find_fail[k].visit_count++;
			}
		}
	}


	for (int x=0; x<10007+1; x++)// the loop to wirte the data to csv files
	{
		if (insert_suc[x].visit_count!=0 )
			output1 << x / (float) sizeHash << ";" << insert_suc[x].probe / (float)(insert_suc[x].visit_count) << endl;
		if (insert_fail[x].visit_count!=0)
			output2 << insert_fail[x].loadfactor << ";" << insert_fail[x].probe / (float)(insert_fail[x].visit_count) << endl;
		if (delete_suc[x].visit_count!=0)
			output3 << delete_suc[x].loadfactor << ";" << delete_suc[x].probe / (float)(delete_suc[x].visit_count) << endl;
		if (delete_fail[x].visit_count!=0)
			output4 << x / (float) sizeHash << ";" << delete_fail[x].probe / (float)(delete_fail[x].visit_count) << endl;
		if(find_suc[x].visit_count!=0)
			output5 << find_suc[x].loadfactor << ";" << find_suc[x].probe / (float)(find_suc[x].visit_count) << endl;
		if( find_fail[x].visit_count!=0)
			output6 << find_fail[x].loadfactor << ";" << find_fail[x].probe / (float)(find_fail[x].visit_count) << endl;
	}
	output1.close();
	output2.close();
	output3.close();
	output4.close();
	output5.close();
	output6.close();

	return 0;
}
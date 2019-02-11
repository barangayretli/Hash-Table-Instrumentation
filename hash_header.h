#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <string>
using namespace std;

// LinearProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 10007
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hash( string str ) --> Global method to hash strings
enum EntryType { ACTIVE, EMPTY, DELETED };

struct HashEntry
{
	int element;
	EntryType info;
	

	HashEntry( const int & e = int( ), EntryType i = EMPTY )
		: element( e ), info( i ) { }
};

class HashTable
{
public:


	explicit HashTable( int size = 10007 ) : array ( 10007 )
	{ makeEmpty( ); }

	/*bool contains( const int & x ) const
	{
		int temp=0;
		return isActive( findPos( x,temp, probe ) );
	}*/

	void makeEmpty( )
	{
		currentSize = 0;
		for( unsigned int i = 0; i < array.size( ); i++ )
			array[ i ].info = EMPTY;
	}

	bool insert( const int & x , int & probing)
	{
		int temp=0;
		int currentPos=0;
		if(findPos(x,temp,probing)||isFull())
			return false;
		else
		{
		// Insert x as active
			 int probe=0;
			int currentPos= findPos_int(x);//find the position of x
			while (isActive(currentPos) && probe <array.size())// if it is active and we did not visit the whole table, then keep going
			{
				probe++;
				currentPos++;
				if(currentPos == array.capacity())
					currentPos=0;
			}
			
		array[ currentPos ] = HashEntry( x, ACTIVE );//insert it and make it active
		currentSize++;//increase the current size
		probing = probe;// send probe to main by reference

		return true;
		}
	}
	int findPos_int(const int & x)
	{
		int currentPos=x % array.size();
		int range=0;
		while (array[currentPos].element!=x && array[currentPos].info!= EMPTY && range< array.capacity()) 
		{//while element is not found, info is not empty and we did not visit the whole table
			if ( array[currentPos].info== DELETED)
				return currentPos;
			currentPos++; // increase the currentposition if the info is deleted
			if (currentPos==array.capacity())//if we reached to the end, go back to the beginning
				currentPos=0;
			range++;//increase the range
		}
		return currentPos;
	}
	
	bool isFull()
	{
		return currentSize==array.size();//function to check if the table is full
	}

	bool remove( const int & x, int & probing ) // remove if it can be found 
	{
		int currentPos=0;
		probing=0;
		
		if (findPos(x,currentPos,probing))// if you find
		{
			currentSize--;
			array[currentPos].info = DELETED;// remove it

			return true;
		}
		else // else you can not remove it
			return false;
	}

	bool findPos( const int & x, int & currentPos , int & probe ) const
	{
		int offset = 1; // probing 
		currentPos = myhash( x ); // get the current position by hash function
		if(array[currentPos].info==EMPTY)// if the info is empty, return false
			return false;
		

		while( array[ currentPos ].info != EMPTY &&
			array[ currentPos ].element != x && probe < array.capacity()) 
		{
			probe++; // increase the probe
			currentPos += offset;  // add 1 to currentPos

			if(currentPos==array.capacity())// if we reached to the end
				currentPos=0;// make it 0 again
		}
		if (array[currentPos].element == x && array[currentPos].element== ACTIVE)// if it is found return true
			return true;
		else
			return false;
	}
	bool find (const int & x,int & probing) // if it can be found return true;
	{
		probing=0;
		int currentPos=0;
		if (findPos(x,currentPos,probing))
			return true;
		return false;
	
	}

	int getCurrentSize()
	{
		return currentSize;
	}
	double getLoadFactor()
	{
		return (double)currentSize/array.capacity();
	}
	
private:
	vector<HashEntry> array;
	int currentSize;

	bool isActive( int currentPos ) const
	{ return array[ currentPos ].info == ACTIVE; }


	
	int myhash( const int & key ) const
	{
		int hashVal = key % array.size();

		return hashVal;
	}
};




#endif
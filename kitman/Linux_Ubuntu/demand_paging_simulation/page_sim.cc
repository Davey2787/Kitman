#include <sys/types.h>
#include <sys/ipc.h>
#include <iostream>
#include <unistd.h>
#include <stdlib.h> 
using namespace std; 

struct PageEntry
{
	int pBit;
	int rBit;
	int mBit;
	int frameNo;
};

PageEntry table [] = {{1,0,0,11},{0,0,0,0},{1,1,1,10},{1,0,0,5},{1,1,0,7}};

main()
{
	int addr;
	int pageNo;
	int stored;
	int frame_num;
	int physical_addr;
	int offset;

	cout<<"\nPlease enter logical address\n";
	cin>>addr;	
	if(addr > 12287)
	{
		cout<<"\nAddress out of bounds\n\n";
		exit (EXIT_SUCCESS);
	}

	pageNo = addr/2048;
	offset = addr%2048;

	stored = table[pageNo].pBit;

	if(stored == 0)
	{
		cout<<"\nPage fault\n\n";
		exit (EXIT_SUCCESS);
	}
	else
	{
		frame_num = table[pageNo].frameNo;
		
		physical_addr = frame_num*2048+offset;

		cout<<"\nPhysical address is "<<physical_addr<<"\n\n";
	}

}
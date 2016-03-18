#include "class_cache_multinivel.cpp"
#include <sstream>
#include <fstream>
#include <limits>

int main(int argc, char const *argv[])
{
	using namespace std;

	int cache_size_L1 = atoi(argv[1]);
	int cache_size_L2 = atoi(argv[2]);
	int block_size = 16;
	int associative_level = 1; //1: direct mapped, 0: full associative
	/*
	if (argv[4])
	{
		associative_level = atoi(argv[4]);
	}
	if (argv[3])
	{
		block_size = atoi(argv[3]);
	}
	*/
	cout << "associative_level: " <<associative_level<< " Cache_Size_L1: " <<cache_size_L1 << " Cache_Size_L2: " <<cache_size_L2<<"\n";
	
	//Declaring new cache object
	cCache MiCache(cache_size_L1,cache_size_L2,block_size,associative_level);

	//Reading the instructions
	//ifstream inFile("./Instrucciones/aligned.trace");
	//ifstream inFile("my_file");
	ifstream inFile("./../../Tarea1/Codigo/Instrucciones/aligned.trace");
	string firstWord;
	int count = 10000;
	while (inFile >> firstWord && count > 0)
	{
	    //cout << firstWord << endl;
    	inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    	MiCache.read_adress(firstWord);
    	count = count - 1;
	}


	//Printing the results
	unsigned int miss_amount = MiCache.miss_amount();
	unsigned int hit_amount_L1 = MiCache.hit_amount_L1();
	unsigned int hit_amount_L2 = MiCache.hit_amount_L2();
	unsigned int read_amount = MiCache.read_amount();
	unsigned int hit_latency_L1 = MiCache.hit_latency_time_L1();
	unsigned int hit_latency_L2 = MiCache.hit_latency_time_L2();

	float miss_rate = ((float)miss_amount/(float)read_amount)*100;

	printf("Miss %u\n", miss_amount);
	printf("Hits L1 %u\n", hit_amount_L1);
	printf("Hits L2 %u\n", hit_amount_L2);
	printf("Read %u\n", read_amount);
	printf("Miss_Rate %f % \n", miss_rate);
	printf("Hit latency L1 %u\n",hit_latency_L1 );
	printf("Hit latency L2 %u\n",hit_latency_L2 );

	return 0;
}

#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<ctime>

using namespace std;

int main(int argc, char* argv[])
{
   if(argc != 3)
      cout<<"Usage: ./ga1 <algorithm(1-3)> <max_array_size>\n";
   else
   {
      int max_size = atoi(argv[2]);
      int a[max_size];
      int max_sum = 0;
      int r;
      int N = 1;
      int M = 200;
      srand(time(NULL));

      //generate a random array
      for(int i=0;i<max_size;i++){
         r = M + rand() / (RAND_MAX / (N - M + 1) + 1) - 100;
         a[i] = r;
      }

      //timer
      clock_t start;
      double duration;
      for(int i = 0; i < 10; i++)
      {
         start = clock();

      if(strcmp(argv[1], "1") == 0)
      {
	 int sum;
	 for(int i = 0; i < (sizeof(a)/sizeof(int)); i++)
	 {
            for(int j = 0; j < (sizeof(a)/sizeof(int)); j++)
	    {
               if(j > i)
	       {
                  sum = 0;
		  for(int k = i; k < j; k++)
		  {
                     sum += a[k];
		  }
		  max_sum = max(max_sum, sum);
	       }
	    }
	 }
      }
      else if(strcmp(argv[1], "2") == 0)
      {
	 int sum;
         for(int i = 0; i < (sizeof(a)/sizeof(int)); i++)
	 {
            sum = 0;
	    for(int j = i; j < (sizeof(a)/sizeof(int)); j++)
	    {
               sum += a[j];
	       max_sum = max(max_sum, sum);
	    }
	 }
      }
      else if(strcmp(argv[1], "3") == 0)
      {
         int cumul_max = 0;
	 for(int i = 0; i < (sizeof(a)/sizeof(int)); i++)
	 {
            cumul_max = max(0,(cumul_max + a[i]));
	    max_sum = max(max_sum, cumul_max);
	 }
      }
         duration = (clock() - start) / ((double) CLOCKS_PER_SEC);
      }
      cout<<"Max sum: "<<max_sum<<endl;
      cout<<"Duration: "<<duration<<endl;
   }
   return 0;
}


#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define N 100000
int main()
{
clock_t start, finish;
start = clock();
int Total_prime=0;
for (int i=0; i<N ; i++)
{	int num =0;
	for (int j = 2; j< i; j++)
	{
		if (i%j == 0 )
		num++;	
	}
	if (num==0)
	Total_prime++;
}
printf("The prime number is : %d\n",Total_prime);
finish = clock();
double time = (double)(finish - start)/CLOCKS_PER_SEC;
printf("Time: %f s\n", time);	

}

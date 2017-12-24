#include "mpi.h"
#include <sys/time.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define N 100000

int Sum(int start, int finish)
{
	int total=0;
	for(start; start<finish; start++)
	{
		total+=start;
		
	}
	return total;
}
int main(int argc, char *argv[])
{
	int coreid, pro_num;
	int num = 0;
	int ave = 0;
	clock_t start,finish;
	long int Total_sum;
	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD, &coreid);
	MPI_Comm_size(MPI_COMM_WORLD, &pro_num);
	//srand(time(0));
	//printf ("%s",status);
	int last_id,residue;
	last_id = pro_num-1;
	residue = N%last_id+1;
	ave = N/last_id;
	start=clock();
	//printf ("the size:%d\n",pro_num );
	
	if (coreid!=0)
	{	if (coreid == last_id)
		{
			Total_sum = Sum((coreid-1)*ave, coreid*ave+residue);
			MPI_Send(&Total_sum,1,MPI_INT,0,99,MPI_COMM_WORLD);
			//printf ("the coreid %d the sum %d the start %d the finish %d\n", coreid, Total_sum,(coreid-1)*ave,coreid*ave+residue-1);
		}
		else 
		{
			Total_sum = Sum((coreid-1)*ave,coreid*ave);
			MPI_Send(&Total_sum,1,MPI_INT,0,99,MPI_COMM_WORLD);
			//printf ("the coreid %d the sum %d the start %d the finish %d\n", coreid, Total_sum,(coreid-1)*ave,coreid*ave);
		}
	}
	
	
	else 
	{	long int id_sum;
		long int last_sum=0;
		int NUM = 0;
		for(int core =1; core< pro_num; core++)
		{
			MPI_Recv(&id_sum,10,MPI_INT,core,99,MPI_COMM_WORLD, &status);
			last_sum += id_sum;
			 	
 		}
		//printf ("the total is %ld\n", last_sum);
	}
	
    finish = clock();
	if (coreid == 0)
     {
         double  time  =  (double)(finish-start)/CLOCKS_PER_SEC;
         printf("Time: %f s\n", time);
     }
	//printf("the total is %d\n",num);
	MPI_Finalize();
	return 0;
}

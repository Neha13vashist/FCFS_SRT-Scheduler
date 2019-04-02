#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
int main()
{
	int process[15], arrival_time[15], burst_time[15], waiting_time[15], turnaround_time[15];
	float avg_wt, avg_tt;
	int no_process;
	int i;
	printf("Enter the number of processes(max 15) : ");
	scanf(%d,no_process);
	if(no_process>15)
	{
		printf("Number of processes exceeded the max. limit");
	}
	else
	{
		printf("Enter the arrival time and the burst time for the processes");
		for(i=0; i<no_process; i++)
		{
			printf("Process P%d",i+1);
			printf("Arrival time : ");
			scanf(%d, arrival_time[i]);
			printf("Burst time : ");
			scanf(%d, burst_time[i]);
		}
	}
	return 0;
}

#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>


int itr=1;
int time_track=0;
//int count=0;

typedef struct Process
{
	int Process_Id;
	int Arrival_Time;
	int Burst_Time;
	int Burst_Time_Copy;
	int Waiting_Time;
	int Turnaround_Time;
	int Completion_time;
}pr;

int n;
pr P[10];
void Process_info(int);
void FCFS();
void FCFS_Algo(struct Process *, int);
void Display();
void SRT_Algo();
void Round_Robin(int);
void scheduling();
void wt_tt();






int main()
{
	printf("Enter the number of processes : ");
	scanf("%d",&n);
	if(n>10)
	{
		printf("You have exceeded the max. limit of processes to be executed");
	}
	else
	{
		Process_info(n);
	}
	return 0;
}



//schedule when to use which algorithm
void scheduling()
{
	int count = 0;
	for(int i=0;i<n;i++)
	{
		if(P[i].Burst_Time==0)
		{
			count = count+1;
		}
	}
	if(count==n)
	{
		Display();
	}
	else
	{
		if(itr==1)
		{
			FCFS_Algo(&P,n);
		}
		else
		{
			SRT_Algo();
		}
	}
}








// Getting details for the process
void Process_info(int a)
{
	int i;
	printf("Enter the arrival time and Burst time for the processes\n"); //Taking input for burst time and arrival time
	for(i=0;i<a;i++)
	{
		printf("\tEnter for Process %d :",i);
		scanf("%d%d",&P[i].Arrival_Time,&P[i].Burst_Time);
		P[i].Burst_Time_Copy = P[i].Burst_Time;
		P[i].Process_Id=i;
	}
	for(i=0;i<n;i++)
	{
		if(P[i].Burst_Time==0)
		{
			P[i].Completion_time = P[i].Arrival_Time;
		}
	}
	scheduling();
}


//Scheduling using First come first serve
void FCFS_Algo(struct Process *P,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(P[j].Arrival_Time>P[i].Arrival_Time)
			{
				struct Process t = P[i];
				P[i] = P[j];
				P[j] = t;
			}
		}
	}
	if(itr==1)
	{
		time_track = P[0].Arrival_Time;
	}
	for(int i=0;i<n;i++)
	{
		Round_Robin(i);
	}
	itr+=1;
	scheduling();
}



//scheduling using round robin
void Round_Robin(int p_no)
{
	if(itr==1)
	{
		if(P[p_no].Burst_Time>=9 && P[p_no].Arrival_Time<=time_track)
		{
			time_track+=9;
			P[p_no].Burst_Time = P[p_no].Burst_Time-9;
			
			if(P[p_no].Burst_Time==0)
			{
				P[p_no].Completion_time = time_track;
			}
		}
		else
		{
			if(P[p_no].Arrival_Time<=time_track)
			{
				time_track = P[p_no].Burst_Time+time_track;
				P[p_no].Burst_Time = 0;
				P[p_no].Completion_time = time_track;
			}
		}
	}
	else
	{
		if(P[p_no].Burst_Time>=6 && P[p_no].Arrival_Time<=time_track)
		{
			time_track+=6;
			P[p_no].Burst_Time = P[p_no].Burst_Time-6;
			
			if(P[p_no].Burst_Time==0)
			{
				P[p_no].Completion_time = time_track;
			}
		}
		else
		{
			if(P[p_no].Arrival_Time<=time_track)
			{
				time_track = P[p_no].Burst_Time+time_track;
				P[p_no].Burst_Time = 0;
				P[p_no].Completion_time = time_track;
			}
		}
	}	
}


//Shortest remaining job first algorithm
void SRT_Algo()
{
	
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(P[j].Burst_Time>P[i].Burst_Time)
			{
				struct Process t = P[i];
				P[i] = P[j];
				P[j] = t;
			}
		}
	}
	for(int i=0;i<n;i++)
	{
		if(P[i].Burst_Time!=0)
		{Round_Robin(i);}
		
	}
	scheduling();
}

//Calculating waiting time and turnaround time
void wt_tt()
{
	for(int i=0;i<n;i++)
	{
		P[i].Turnaround_Time = P[i].Completion_time - P[i].Arrival_Time;
		P[i].Waiting_Time = P[i].Turnaround_Time - P[i].Burst_Time_Copy;
	}
}


//Display the final scheduling
void Display()
{
	wt_tt();
	int avg_wt=0, avg_tat=0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(P[j].Process_Id>P[i].Process_Id)
			{
				struct Process t = P[i];
				P[i] = P[j];
				P[j] = t;
			}
		}
	}
	printf("P_Id\tArrival_Time\tBurst_Time\tWaiting_Time\tTurn_Around_Time\tCompletion_Time\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n",P[i].Process_Id,P[i].Arrival_Time,P[i].Burst_Time_Copy,P[i].Waiting_Time,P[i].Turnaround_Time,P[i].Completion_time);
		avg_wt += P[i].Waiting_Time;
		avg_tat += P[i].Turnaround_Time;
	}
	printf("\n\n Average Waiting Time : %d\n Average Turn Around Time : %d",avg_wt/n,avg_tat/n);
}

























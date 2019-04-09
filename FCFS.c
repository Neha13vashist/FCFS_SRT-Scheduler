#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>


int itr=1;
int time_track=0;
int flag=0;

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




void scheduling()
{
	for(int i=0;i<n;i++)
	{
		if(P[i].Burst_Time==0)
		{
			flag+=1;
		}
	}
	if(flag==n)
	{
		Display();
	}
	else
	{
		if(itr==1 || itr==2)
		{
			FCFS();
		}
		else
		{
			SRT_Algo();
		}
	}
}









void Process_info(int a)
{
	int i;
	printf("Enter the arrival time and Burst time for the processes\n");
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

void FCFS()
{
	FCFS_Algo(&P,n);
}

void Round_Robin(int p_no)
{
	if(itr==1)
	{
		if(P[p_no].Burst_Time>3)
		{
			time_track+=3;
			P[p_no].Burst_Time = P[p_no].Burst_Time-3;
			if(P[p_no].Burst_Time==0)
			{
				P[p_no].Completion_time = time_track;
			}
		}
		else
		{
			time_track += P[p_no].Burst_Time;
			P[p_no].Burst_Time = 0;
			P[p_no].Completion_time = time_track;
		}
	}
	else
	{
		if(P[p_no].Burst_Time>6)
		{
			time_track+=6;
			P[p_no].Burst_Time = P[p_no].Burst_Time-6;
		}
		else
		{
			time_track += P[p_no].Burst_Time;
			P[p_no].Burst_Time = 0;
			P[p_no].Completion_time = time_track;
		}
	}
	scheduling();	
}


void SRT_Algo()
{
	int p_no = 0;
	int s_rt = 1;
 	for (int i = 0; i < n; i++)
	{
      		if (P[i].Burst_Time <= s_rt && P[i].Burst_Time>0) 
		{
			p_no = i;
        		s_rt = P[i].Burst_Time;
      		}
   	}
	Round_Robin(p_no);
}


void wt_tt()
{
	for(int i=0;i<n;i++)
	{
		P[i].Turnaround_Time = P[i].Completion_time - P[i].Arrival_Time;
		P[i].Waiting_Time = P[i].Turnaround_Time - P[i].Burst_Time_Copy;
	}
}


void Display()
{
	wt_tt();
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n",P[i].Process_Id,P[i].Arrival_Time,P[i].Burst_Time_Copy,P[i].Waiting_Time,P[i].Turnaround_Time,P[i].Completion_time);
	}
}

























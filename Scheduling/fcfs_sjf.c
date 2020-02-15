#include<stdio.h>
#include <stdlib.h>
#include<string.h>

//Struture representing each process
struct Job{
	char *PID;
	double arrivalTime;
	double burstTime;
	double waitTime;
	double turnTime;
	double responseTime;
};

typedef struct Job Process;

//Initialising the data members of each process
void initialise(Process *p){
	p->PID=(char*)malloc(100*sizeof(char));
	p->arrivalTime=0.0;
	p->burstTime=0.0;
	p->waitTime=0.0;
	p->turnTime=0.0;
	p->responseTime=0.0;
}

//Accepting data of each process
void acceptProcess(Process *p){
	printf("\n Enter Process ID: ");scanf(" %s",p->PID);
	printf("\n Enter arrival time: ");scanf("%lf",&p->arrivalTime);
	printf("\n Enter burst time: ");scanf("%lf",&p->burstTime);
}

//Display Processes
void displayProcesses(Process p[],int number_of_processes){
	for(int i=0;i<number_of_processes;i++)
		printf("\t%s",p[i].PID);
	printf("\n");
}

//Sorting using Insertion sort
void sortOnArrivalTime(Process p[],int start_index,int end_index){
	for(int i=start_index;i<end_index;i++){
		Process key=p[i];
		int j=i-1;
		for(;j>=start_index&&key.arrivalTime<p[j].arrivalTime;j--)
			p[j+1]=p[j];
		p[j+1]=key;
	}
}

//Display Gantt Chart
void displayGanttChart(char *Gantt_Chart[],int number_of_interval,double start_times[],double end_times[]){
	
	//Display top line
	printf("\n Gantt_Chart:\n");
	for(int i=0;i<number_of_interval;i++){
		printf("_______________");
	}
	
	//Display order of processes
	printf("\n|");
	for(int i=0;i<number_of_interval;i++)
		printf("_____%4s_____|",Gantt_Chart[i]);
	printf("\n");

	//Display time line
	int i=0;
	for(i=0;i<number_of_interval;i++)
		printf("%-15.0lf",start_times[i]);
	printf("%-15.0lf",end_times[i-1]);
	printf("\n\n");
}

//FCFS Scheduling
void FCFS(Process P[],int number_of_processes){
	char *Gantt_Chart[100];
	for(int i=0;i<100;i++)
		Gantt_Chart[i]=(char*)malloc(10*sizeof(char));

	int interval=0;
	double start_times[100];
	double end_times[100];

	sortOnArrivalTime(P,0,number_of_processes);
	for(int i=0;i<number_of_processes;i++){
		strcpy(Gantt_Chart[interval],P[i].PID);
		if(interval==0){
			start_times[interval]=0;
		}
		else{
			start_times[interval]=end_times[interval-1];
		}
		end_times[interval]=start_times[interval]+P[i].burstTime;
		interval++;
	}

	displayGanttChart(Gantt_Chart,interval,start_times,end_times);

}

//Sorting on Burst time
void sortOnBurstTime(Process p[],int number_of_processes){

	for(int i=0;i<number_of_processes;i++){
		Process key=p[i];
		int j=i-1;
		for(;j>=0&&key.burstTime<p[j].burstTime;j--)
			p[j+1]=p[j];
		p[j+1]=key;
	}
	
}

//SJF Non-preemptive Scheduling
void Non_PreSJF(Process P[],int number_of_processes){
	//Total time of execution
	double sum=0;
	for(int i=0;i<number_of_processes;i++)
		sum+=P[i].burstTime;

	//Gantt chart
	char *Gantt_Chart[100];
	for(int i=0;i<100;i++)
		Gantt_Chart[i]=(char*)malloc(10*sizeof(char));

	//Start and end times of processes
	int interval=0;
	double start_times[100];
	double end_times[100];

	for(int time=0;time<sum;){
		
		Process tmp[100];
		for(int i=0;i<100;i++)
			initialise(&tmp[i]);

		int tctr=0;
		for(int i=0;i<number_of_processes;i++)
			if(P[i].arrivalTime<=time&&P[i].burstTime){
				tmp[tctr++]=P[i];
				P[i].burstTime=0;
			}

		sortOnBurstTime(tmp,tctr);
		
		for(int i=0;i<tctr;i++){
			strcpy(Gantt_Chart[interval],tmp[i].PID);
			if(interval==0){
				start_times[interval]=0;
			}
			else{
				start_times[interval]=end_times[interval-1];
			}
			end_times[interval]=start_times[interval]+tmp[i].burstTime;
			interval++;
		}
		time=end_times[interval-1];
	}
	displayGanttChart(Gantt_Chart,interval,start_times,end_times);
}

//SJF Preemptive Scheduling
void PreSJF(Process P[],int number_of_processes){
	//Total time of execution
	double sum=0;
	for(int i=0;i<number_of_processes;i++)
		sum+=P[i].burstTime;

	//Gantt chart
	char *Gantt_Chart[100];
	for(int i=0;i<100;i++)
		Gantt_Chart[i]=(char*)malloc(10*sizeof(char));

	//Start and end times of processes
	int interval=0;
	double start_times[100];
	double end_times[100];

	for(int time=0;time<sum;time++){
		
		Process tmp[100];
		for(int i=0;i<100;i++)
			initialise(&tmp[i]);

		int tctr=0;
		for(int i=0;i<number_of_processes;i++)
			if(P[i].arrivalTime<=time&&P[i].burstTime){
				tmp[tctr++]=P[i];
			}

		sortOnBurstTime(tmp,tctr);

		for(int i=0;i<number_of_processes;i++){
			if(strcmp(tmp[0].PID,P[i].PID)==0)
				P[i].burstTime--;
		}

		if(interval==0){
			strcpy(Gantt_Chart[interval],tmp[0].PID);
			start_times[interval]=0;
			interval++;
		}
		else{
			if(strcmp(Gantt_Chart[interval-1],tmp[0].PID)!=0){
				end_times[interval-1]=time;
				strcpy(Gantt_Chart[interval],tmp[0].PID);
				start_times[interval]=end_times[interval-1];
				interval++;
			}
		}
	}
	end_times[interval-1]=sum;
	displayGanttChart(Gantt_Chart,interval,start_times,end_times);
}



int main(){
	printf("\n\t\tCPU SCHEDULING ALGORITHMS\n");
	Process p[100];
	int number_of_processes;

	printf("\nEnter the number_of_processes:");scanf("%d",&number_of_processes);
	printf("\nEnter the details of the processes:");
	
	for(int i=0;i<number_of_processes;i++){
		initialise(&p[i]);
		acceptProcess(&p[i]);
	}

	Process FCFSp[100];
	for(int i=0;i<number_of_processes;i++){
		initialise(&FCFSp[i]);
		FCFSp[i]=p[i];
	}
	FCFS(FCFSp,number_of_processes);
	
	Process NSJFp[100];
	for(int i=0;i<number_of_processes;i++){
		initialise(&NSJFp[i]);
		NSJFp[i]=p[i];
	}
	Non_PreSJF(NSJFp,number_of_processes);
	
	Process SJFp[100];
	for(int i=0;i<number_of_processes;i++){
		initialise(&SJFp[i]);
		SJFp[i]=p[i];
	}
	PreSJF(SJFp,number_of_processes);
}
#include <stdio.h>
#define MAX_PROCESSES 10
typedef struct{
    int pid;
    int burst_time;
    int remaining;
    int base_priority;
    int dyn_priority;
    int cpu_usage;
    int completed;
    int completion_time;
    int waiting_time;
    int turnaround_time;
}Process;
void update_priority(Process p[],int n){
    for(int i=0;i<n;i++){
        if(!p[i].completed) p[i].dyn_priority=p[i].base_priority+p[i].cpu_usage/2;
    }
}
int select_process(Process p[],int n,int last_index){
    int min_remaining=9999, index=-1;
    int start=(last_index + 1)%n;
    for(int offset=0; offset<n;offset++){
        int i=(start+offset)%n;
        if(!p[i].completed && p[i].remaining<min_remaining){
            min_remaining=p[i].remaining;
            index=i;
        }
    }
    return index;
}
int main(){
    Process p[MAX_PROCESSES];
    int n;
    int time_quantum=3;
    printf("Enter number of processes: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter burst time and base priority (nice value) for P%d: ",p[i].pid);
        scanf("%d %d",&p[i].burst_time, &p[i].base_priority);
        p[i].remaining=p[i].burst_time;
        p[i].cpu_usage=0;
        p[i].completed=0;
    }
    int time=0,completed=0,last_index=-1;
    int gantt_pids[100],gantt_times[100],gcount = 0;
    printf("\n--- CPU Scheduling Simulation (RR + SJF Hybrid) ---\n");
    while(completed<n){
        update_priority(p,n);
        int i=select_process(p,n,last_index);
        if (i==-1) break;
        int exec=(p[i].remaining<=time_quantum)?p[i].remaining:time_quantum;
        printf("Time %2d - %2d: Process P%d (priority=%d)\n",time,time + exec,p[i].pid,p[i].dyn_priority);
        if(gcount == 0||gantt_pids[gcount - 1]!=p[i].pid){
            gantt_pids[gcount]=p[i].pid;
            gantt_times[gcount]=time;
            gcount++;
        }
        p[i].remaining-=exec;
        p[i].cpu_usage+=exec;
        time+=exec;
        if(p[i].remaining==0){
            p[i].completed=1;
            p[i].completion_time=time;
            completed++;
            printf(" -> P%d finished execution.\n",p[i].pid);
        }
        last_index=i;
    }
    gantt_times[gcount]=time;
    for(int i=0;i<n;i++){
        p[i].turnaround_time=p[i].completion_time;
        p[i].waiting_time=p[i].turnaround_time-p[i].burst_time;
    }
    printf("\nProcess\tBT\tPri\tCT\tTAT\tWT\n");
    for(int i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid, p[i].burst_time,p[i].base_priority,p[i].completion_time,p[i].turnaround_time,p[i].waiting_time);
    }
    printf("\nGantt Chart:\n");
    for(int i=0; i<gcount;i++) printf("<--P%d-->",gantt_pids[i]);
    printf("\n");
    for(int i=0;i<=gcount;i++) printf("%3d ",gantt_times[i]);
    printf("\n");
    return 0;
}

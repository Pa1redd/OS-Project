#include <stdio.h>
#include<limits.h>
#include <stdbool.h>
struct Process {
    int psid;
    int bat;
    int art;
};
void findWaitingTime(struct Process proc[], int n,int wt[])
{
    int rt[n],i,j;
    for (i = 0; i < n; i++)
        rt[i] = proc[i].bat;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = 0, finish_time;
    bool check = false;
    while (complete != n) {
        for (j = 0; j < n; j++) {
            if ((proc[j].art <= t) &&(rt[j] < minm) && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (check == false) {
            t++;
            continue;
        }
        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;
        if (rt[shortest] == 0) {
            complete++;
            finish_time = t + 1;
            wt[shortest] = finish_time -proc[shortest].bt -proc[shortest].art;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }
        t++;
    }
}
void findTurnAroundTime(struct Process proc[], int n,int wt[], int tat[])
{
    int i;
    for (i = 0; i < n; i++)
        tat[i] = proc[i].bat + wt[i];
}
void findavgTime(struct Process proc[], int n)
{
    int wt[n], tat[n], total_wt = 0,total_tat = 0;
    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);
    int i;
    printf( "Processes   Burst time   Waiting time   Turn around time\n");
    for (i = 0; i < n; i++) {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
            printf("%d\t\t%d\t\t%d\t\t%d\t\t\n",proc[i].psid,proc[i].bat,wt[i],tat[i]);
			    }

    printf("\nAverage waiting time =%f",(float)total_wt / (float)n);

    printf("\nAverage turn around time = %f",(float)total_tat / (float)n);
}
int main()
{
    int f,i;
    printf("Enter number of process\n");
    scanf("%d",&f);
    struct Process proc[f];
    for(i=0;i<f;i++)
    {
    	printf("Enter id of process \n");
    	scanf("%d",&proc[i].psid);
    	printf("Enter arraival time of process \n");
    	scanf("%d",&proc[i].art);
    	printf("Enter burst time of process \n");
    	scanf("%d",&proc[i].bat);
}
    int n = sizeof(proc) / sizeof(proc[0]);
    findavgTime(proc, n);
    return 0;
}

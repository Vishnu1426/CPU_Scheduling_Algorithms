#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int n;

int FCFS(int p_id[n], int p_at[n], int p_bt[n]); 
int SJF(int p_id[n], int p_at[n], int p_bt[n]);
int RR(int p_id[n], int p_at[n], int p_bt[n], int tq); 

struct node
    {
        int idx;
        struct node *next;
    };

int print(int p_id[n], int  p_at[n], int p_bt[n], int p_ct[n], int p_tat[n], int p_wt[n], float wt_avg, float tat_avg, int p_order[n])
    {
        printf("\n--------------------------------------------------------------------------------------------------------------------------------");
        printf("\nExecution Table is: \n");
        printf("Process ID\t\tArrival Time\t\tBurst Time\t\tCompletion Time\t\tTAT\t\tWait Time\n");
        for(int i = 0; i < n; i++)
            {
                printf("  %d\t\t\t  %d\t\t\t  %d\t\t\t\t%d\t\t %d\t\t  %d\n", p_id[i], p_at[i], p_bt[i], p_ct[i], p_tat[i], p_wt[i]);
            }
        printf("\nThe order of execution is: P%d", p_order[0]);
        for(int i = 1; i < n; i++)
            {
                printf(" -> P%d", p_order[i]);
            }
        printf("\nAverage Turn Around Time (TAT) = %f\n", tat_avg/n);
        printf("Average Wait Time (WT) = %f\n", wt_avg/n);
        printf("\n--------------------------------------------------------------------------------------------------------------------------------\n");
    }

int FCFS(int p_id[n], int p_at[n], int p_bt[n])   
    {
        int p_order[n], p_ct[n], p_tat[n], p_wt[n], time = 0;
        float wt_avg = 0, tat_avg = 0;

        for(int i = 0; i < n; i++)
            {
                p_order[i] = p_id[i];
                time = time + p_bt[i];
                p_ct[i] = time;
                if(i != n-1 && time < p_at[i+1])
                    {   
                        time  = p_at[i+1];
                    }
                p_tat[i] = p_ct[i] - p_at[i];
                p_wt[i] = p_tat[i] - p_bt[i];
                wt_avg = wt_avg + p_wt[i];
                tat_avg = tat_avg + p_tat[i];
            }
        print(p_id, p_at, p_bt, p_ct, p_tat, p_wt, wt_avg, tat_avg, p_order);
        return 0;
    }

int minimum(int p_remainingtime[n], int p_arrived[n], int time, int idx)
    {
        for(int i = 0; i < n; i++)
            {
                if(p_arrived[i] == 1)
                    {
                        if(p_remainingtime[i] < p_remainingtime[idx])
                            {
                                idx = i;
                            }
                    }
            }
        return idx;
    }

int SJF(int p_id[n], int p_at[n], int p_bt[n])   
    {
        int p_remainingtime[n], p_order[n], p_ct[n], p_tat[n], p_wt[n], time = p_at[0], p_arrived[n], idx = 0;
        float wt_avg = 0, tat_avg = 0;

        for(int i = 0; i < n; i++)
            {
                p_remainingtime[i] = p_bt[i];
            }
        p_arrived[0] = 1;

        for(int i = 0; i < n; i++)
            {
                if(i != n-1 && time < p_at[i])
                    {   
                        time  = p_at[i];
                    }
                // Checking for arrived processes
                for(int i = 0; i < n; i++)
                    {
                        if(p_at[i] <= time)
                            {
                                p_arrived[i] = 1;
                            }
                        else
                            {
                                p_arrived[i] = 0;
                            }
                     }

                idx = minimum(p_remainingtime, p_arrived, time, idx);

                p_order[i] = p_id[idx];
                time = time + p_bt[idx];;
                p_ct[idx] = time;
                p_tat[idx] = p_ct[idx] - p_at[idx];
                p_wt[idx] = p_tat[idx] - p_bt[idx];
                wt_avg = wt_avg + p_wt[idx];
                tat_avg = tat_avg + p_tat[idx];
                p_remainingtime[idx] = INT_MAX;
            }
        
        print(p_id, p_at, p_bt, p_ct, p_tat, p_wt, wt_avg, tat_avg, p_order);
        return 0;
    }

int RR(int p_id[n], int p_at[n], int p_bt[n], int tq)   
    {
        int idx, p_order[n], p_ct[n], p_tat[n], p_wt[n], time = 0,p_arrived[n], t = 0, completed = tq, p_remainingtime[n];
        float wt_avg = 0, tat_avg = 0;
        struct node *head, *tail; 
        struct node *temp;
        
        head = NULL;
        tail = NULL;

        for(int i = 0; i < n; i++)
            {
                p_remainingtime[i] = p_bt[i];
            }

        p_arrived[0] = 1;

        temp = (struct node*)(malloc(sizeof(struct node)));
        temp -> idx = 0;
        temp -> next = NULL;
        head = temp;
        tail = temp;

        while(t != n)
            {
                time = time + 1;
                // Checking for arrived processes
                for(int i = 1; i < n; i++)
                    {
                        if(p_at[i] <= time)
                            {
                                if(p_arrived[i] != 1)
                                    {
                                        p_arrived[i] = 1;
                                        struct node *temp;
                                        temp = (struct node*)(malloc(sizeof(struct node)));
                                        temp -> idx = i;
                                        temp -> next = NULL;
                                        if(head == NULL)
                                            {
                                                head = temp;
                                                tail = temp;
                                            }
                                        else
                                            {
                                                tail -> next = temp;
                                                tail = temp;
                                            }
                                    }
                            }
                        else
                            {
                                p_arrived[i] = 0;
                            }
                     }
                if(head != NULL)
                    {
                        p_remainingtime[head -> idx] = p_remainingtime[head -> idx] - 1;
                        completed = completed - 1;
                        if(completed == 0 && p_remainingtime[head -> idx] != 0)
                            {
                                struct node *temp;
                                temp = (struct node*)(malloc(sizeof(struct node)));
                                temp -> idx = head -> idx;
                                temp -> next = NULL;
                                tail -> next = temp;
                                tail = temp;
                                head = head -> next;
                                completed = tq;
                            }
                        else if(p_remainingtime[head -> idx] == 0)
                            {
                                p_order[t] = p_id[head -> idx];
                                p_ct[head -> idx] = time;
                                p_tat[head -> idx] = p_ct[head -> idx] - p_at[head -> idx];
                                p_wt[head -> idx] = p_tat[head -> idx] - p_bt[head -> idx];
                                wt_avg = wt_avg + p_wt[head -> idx];
                                tat_avg = tat_avg + p_tat[head -> idx];
                                head = head -> next;
                                t = t + 1;
                                completed = tq;
                            }
                    }
            }

        print(p_id, p_at, p_bt, p_ct, p_tat, p_wt, wt_avg, tat_avg, p_order);
        return 0;
    }

int main()
    {
        printf("\n--------------------------------------------------------------------------------------------------------------------------------");
        printf("\t\t\t\t\t\t\tCPU Scheduling Algorithms Simulation");
        printf("\n--------------------------------------------------------------------------------------------------------------------------------");
        printf("\nEnter the number of processes: ");
        scanf("%d", &n);
        fflush(stdin);

        int p_id[n], p_at[n], p_bt[n], ch, temp;

        for(int i = 0; i < n; i++)
            {
                printf("\nProcess %d\n", i);

                printf("Process ID:");
                scanf("%d", &p_id[i]);
                fflush(stdout);
                
                printf("Arrival Time: ");
                scanf("%d", &p_at[i]);
                fflush(stdout);
                
                printf("Burst Time: ");
                scanf("%d", &p_bt[i]);
                fflush(stdout);
            }

        // Sorting the list of peocesses according to their arrival time    
        for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < n-1; j++)
                    {
                        if(p_at[j] > p_at[j+1])
                            {
                                temp = p_at[j+1];
                                p_at[j+1] = p_at[j];
                                p_at[j] = temp;

                                temp = p_bt[j+1];
                                p_bt[j+1] = p_bt[j];
                                p_bt[j] = temp;
                                
                                temp = p_id[j+1];
                                p_id[j+1] = p_id[j];
                                p_id[j] = temp;
                            }
                    }
            }
        while(1)
            {
                printf("\nChoose the Scheduling Algorithm:\n");
                printf("1. First Come First Serve\n2. Shortest Job First\n3. Round Robin\n4. Exit\n");
                printf("\nChoice: ");
                scanf("%d", &ch);
                if(ch == 1)
                    {
                        FCFS(p_id, p_at, p_bt);
                    }
                else if(ch == 2)
                    {
                        SJF(p_id, p_at, p_bt);
                    }
                else if(ch == 3)
                    {
                        int tq;
                        printf("Enter the Time Quanta for Round Robin Scheduling:");
                        scanf("%d", &tq);
                        RR(p_id, p_at, p_bt, tq);
                    }
                else if(ch == 4)
                    {
                        exit(1);
                    }
                else
                    {
                        printf("Invalid Choice!!");
                    }
            }
            
        return 0;
    }
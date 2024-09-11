#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class process
{
    public:
        string pid;
        int burst_tme;
        int arrival_tme = 0;
        int wait_tme = 0;
        int turnaround_tme = 0;
        int priority_num = 0; 
        int remaining_tme = 0;

	//get normal info
    void get_info()
	{
		cout << endl;
        cout << "Enter PID: ";
        cin >> pid;

        cout << "\tEnter Burst time: ";
        cin >> burst_tme;
        
        remaining_tme = burst_tme;
    }
	
	//get normal + priority info
    void get_priority_info()
	{
        process::get_info();
        
        cout << "\tEnter Priority number: ";
        cin >> priority_num;
        cout << endl;
    }
    
    //FCFS
    static void fcfs(int num1, process p[])
	{
        p[0].turnaround_tme = p[0].burst_tme;
        p[0].wait_tme = 0;

        for (int i = 1; i < num1; i++)
		{
            p[i].wait_tme = p[i - 1].turnaround_tme;
            p[i].turnaround_tme = p[i].wait_tme + p[i].burst_tme;
        }
    }

    //SJF
    static void sjf(int num1, process p[])
	{
        sort(p, p + num1, [](process a, process b)
		{
            return a.burst_tme < b.burst_tme;
        });
        
        fcfs(num1, p);
    }

    //Priority
    static void priority_queue(int num1, process p[])
	{
        sort(p, p + num1, [](process a, process b)
		{
            return a.priority_num < b.priority_num;
        });
        
        fcfs(num1, p);
    }

    //Round robin
    static void round_robin(int num1, process p[], int quantum)
	{
        int time = 0;
        int remaining = num1;
        
        vector<int> wait(num1, 0);
        while (remaining > 0)
		{
            for (int i = 0; i < num1; i++)
			{
                if (p[i].remaining_tme > 0)
				{
                    if (p[i].remaining_tme <= quantum)
					{
                        time += p[i].remaining_tme;
                        
                        p[i].remaining_tme = 0;
                        p[i].turnaround_tme = time;
                        p[i].wait_tme = p[i].turnaround_tme - p[i].burst_tme;
                        
                        remaining--;
                    }
					else
					{
                        p[i].remaining_tme -= quantum;
                        time += quantum;
                    }
                }
            }
        }
    }
	
	//show normal info
    void show_info()
	{
        cout << pid << "\t\t" << burst_tme << "\t\t" << turnaround_tme << "\t\t\t" << wait_tme << endl;
    }
	
    //show normal + priority info
    void show_priority_info()
    {
		cout << pid << "\t\t" << priority_num << "\t\t\t" << burst_tme << "\t\t" << turnaround_tme << "\t\t\t" << wait_tme << endl;
	}
};

//calc avg times
void avg_times(int num1, process p[], float &turnaround_avg, float &wait_avg)
{
    float turnaround_ttl = 0;
    float wait_ttl = 0;

    for (int i = 0; i < num1; i++)
	{
        turnaround_ttl += p[i].turnaround_tme;
        wait_ttl += p[i].wait_tme;
    }
    
    if (num1 > 0)
	{
        turnaround_avg = turnaround_ttl / num1;
        wait_avg = wait_ttl / num1;
    }
}

//show normal info + titles
void show_info(int num1, process p[])
{
	cout << endl;
    cout << "Process:\tBurst time:\tTurn Around Time:\tWait Time:" << endl;
    
    for (int i = 0; i < num1; i++)
	{
        p[i].process::show_info();
    }
}

//show normal + priority info + titles
void show_priority_info(int num1, process p[])
{
	cout << endl;
	cout << "Process:\tPriority Number:\tBurst time:\tTurn Around Time:\tWait Time:" << endl;
	
	for (int i = 0; i < num1; i++)
	{
	    p[i].process::show_priority_info();
    }
}

//gantt charter
void gantt_chart(int num1, process p[])
{
    cout << "\nGantt Chart:\n";
    
    for (int i = 0; i < num1; i++)
	{
        cout << "| " << p[i].pid << " ";
    }
    
    cout << "|\n";

    int time = 0;
    
    for (int i = 0; i < num1; i++)
	{
        cout << time << "    ";
        time += p[i].burst_tme;
    }
    cout << time << endl;
}

int main() 
{
    process P[20];
    int num1;
    int choice;
    int quantum;
    
    cout << "[Process Scheduler 1.6]" << endl << endl;
    cout << "[1 = FCFS]\n[2 = SJF]\n[3 = Priority Queue]\n[4 = Round Robin]\n" << endl;
    
    cout << "Choose scheduling algorithm: ";
    cin >> choice;
    
    cout << endl;
    
	cout << "Enter number of processes: ";
	cin >> num1;
	cout << endl;
	
    if (choice == 3)
	{
        cout << "INPUT DATA: " << endl;
        
        for (int i = 0; i < num1; i++)
		{
            P[i].get_priority_info();
        }
    }
    
    else if (choice == 4)
    {
    	cout << "INPUT DATA: " << endl;
				
		for (int i = 0; i < num1; i++)
		{
		    P[i].get_info();
		}
		
		cout << endl;
		cout << "Enter time quantum: ";
		cin >> quantum;
	}
    
	else
	{
		cout << "INPUT DATA: " << endl;
		
        for (int i = 0; i < num1; i++)
		{
            P[i].get_info();
        }
    }

	cout << "________________________________" << endl;
	cout << "OUTPUT DATA: " << endl;
	
    float turnaround_avg = 0, wait_avg = 0;
    if (choice == 1)
	{
        process::fcfs(num1, P);
        cout << "[FCFS Scheduling]" << endl;
        show_info(num1, P);
    }
    
	else if (choice == 2)
	{
        process::sjf(num1, P);
        cout << "[SJF Scheduling]" << endl;
        show_info(num1, P);
    }
    
	else if (choice == 3)
	{
        process::priority_queue(num1, P);
        cout << "[Priority Scheduling]" << endl;
        show_priority_info(num1, P);
    }
    
	else if (choice == 4)
    {    
        process::round_robin(num1, P, quantum);
        cout << "[Round Robin Scheduling]" << endl;
        show_info(num1, P);
    }
    
    gantt_chart(num1, P);
	
	cout << endl;
	
	avg_times(num1, P, turnaround_avg, wait_avg);
    cout << "Average Turn Around Time = " << turnaround_avg << endl;
    cout << "Average Wait Time = " << wait_avg << endl;

    return 0;
}

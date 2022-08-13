# CPU_Scheduling_Algorithms
 FCFS, SJF and RR Algorithms using C
 
 # FCFS Algorithm
 It stands for First Come First Serve. Whichever process arrives first, it is executed first completely and then the next in queue is executed.
 
 # SJF Algorithm
 It stands for Shortest Job First. Whichever job has the shortest execution time out of all the processes arrived, that processs is executed completely first. 
 
 # RR Algorithm
 It stands for Round Robin. This has a time quanta (say q units) for execution. No process can remain in execution beyond the time quanta. Whichever process arrives first, it is executed for q units of time and if it still has some execution remaining, it is sent to the queue. The next process in queue is taken up for execution after that.
 
 # Program
 Input: Process ID, Arrival Time and Burst Time (Execution time).
        All inputs to be assumed as integers

Output: The execution table with the inputs and completion time, turn around time, and wait time.
        The order of execution, average turn around time and average wait time when all the processes are considered.

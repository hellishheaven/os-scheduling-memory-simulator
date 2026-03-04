Operating System Scheduling and Memory Management Simulator (C++)

Abstract

This project implements classical CPU scheduling and page replacement algorithms to analyze their performance trade-offs under different workloads. The simulator computes quantitative metrics and provides execution visualization to enable systematic comparison between theoretical and practical operating system strategies.

Implemented CPU Scheduling Algorithms

First Come First Serve (FCFS)
Shortest Job First (Non-Preemptive)
Round Robin (Time Quantum Based)

Metrics Computed

Completion Time (CT)
Turnaround Time (TAT)
Waiting Time (WT)
Average Waiting Time
Average Turnaround Time
Text-based Gantt Chart Visualization

Implemented Page Replacement Algorithms

FIFO (First In First Out)
LRU (Least Recently Used)
Optimal Page Replacement (Theoretical Benchmark)

Metrics Computed

Total Page Faults
Comparative Fault Analysis

Design Assumptions

Burst times are assumed to be known in advance.
Context switching overhead is not modeled.
All processes are CPU-bound.
Fixed frame allocation is used for paging.
Optimal algorithm assumes perfect future knowledge and is used only as a benchmark.

Analytical Observations

SJF minimizes average waiting time when arrival times are equal.
Round Robin improves response time but may increase overhead if quantum is too small.
FIFO may suffer from Belady’s anomaly because it does not satisfy the stack property.
LRU approximates Optimal under strong temporal locality.
Thrashing occurs when total working set exceeds available memory.

Sample Execution (Illustrative)

CPU Scheduling Output Example:
FCFS → Avg WT: X, Avg TAT: X
SJF → Avg WT: X, Avg TAT: X
Round Robin (q=2) → Avg WT: X, Avg TAT: X

Page Replacement Example (Frames = 3):

FIFO → X Page Faults
LRU → X Page Faults
Optimal → X Page Faults

How to Compile and Run

g++ os_simulator.cpp -o simulator
./simulator

Project Structure

os_simulator.cpp
README.md

Limitations

Preemptive SRTF not implemented.
No modeling of real context switching cost.
No dynamic frame allocation (Working Set / PFF not implemented).

Future Improvements

Add Preemptive SRTF scheduling
Implement Priority Scheduling with Aging
Add Working Set and PFF-based memory control
Add graphical Gantt chart visualization
Extend to multilevel queue scheduling

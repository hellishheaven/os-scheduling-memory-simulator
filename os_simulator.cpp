#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include <unordered_map>

using namespace std;

/* ====================== CPU SCHEDULING ====================== */

struct Process {
    int id;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int turnaround;
    int waiting;
};

/* ---------- FCFS ---------- */
void fcfs(vector<Process> processes) {
    cout << "\n=== FCFS Scheduling ===\n";

    sort(processes.begin(), processes.end(), [](Process a, Process b) {
        return a.arrival < b.arrival;
    });

    int time = 0;
    vector<int> gantt;

    for (auto &p : processes) {
        if (time < p.arrival)
            time = p.arrival;

        for (int i = 0; i < p.burst; i++)
            gantt.push_back(p.id);

        time += p.burst;
        p.completion = time;
        p.turnaround = p.completion - p.arrival;
        p.waiting = p.turnaround - p.burst;
    }

    double avgWT = 0, avgTAT = 0;

    cout << "ID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t" << p.turnaround << "\t" << p.waiting << "\n";
        avgWT += p.waiting;
        avgTAT += p.turnaround;
    }

    cout << "Average WT: " << avgWT / processes.size() << "\n";
    cout << "Average TAT: " << avgTAT / processes.size() << "\n";

    cout << "Gantt Chart:\n| ";
    for (int id : gantt)
        cout << "P" << id << " | ";
    cout << "\n";
}

/* ---------- SJF (Non-Preemptive) ---------- */
void sjf(vector<Process> processes) {
    cout << "\n=== SJF Scheduling ===\n";

    int n = processes.size();
    int completed = 0, time = 0;
    vector<bool> done(n, false);
    vector<int> gantt;

    while (completed < n) {
        int idx = -1;
        int minBurst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrival <= time &&
                processes[i].burst < minBurst) {
                minBurst = processes[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        for (int i = 0; i < processes[idx].burst; i++)
            gantt.push_back(processes[idx].id);

        time += processes[idx].burst;
        processes[idx].completion = time;
        processes[idx].turnaround = time - processes[idx].arrival;
        processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;

        done[idx] = true;
        completed++;
    }

    double avgWT = 0, avgTAT = 0;

    cout << "ID\tAT\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.id << "\t" << p.arrival << "\t" << p.burst << "\t"
             << p.completion << "\t" << p.turnaround << "\t" << p.waiting << "\n";
        avgWT += p.waiting;
        avgTAT += p.turnaround;
    }

    cout << "Average WT: " << avgWT / n << "\n";
    cout << "Average TAT: " << avgTAT / n << "\n";

    cout << "Gantt Chart:\n| ";
    for (int id : gantt)
        cout << "P" << id << " | ";
    cout << "\n";
}

/* ---------- Round Robin ---------- */
void roundRobin(vector<Process> processes, int quantum) {
    cout << "\n=== Round Robin Scheduling ===\n";

    int n = processes.size();
    queue<int> q;
    vector<int> gantt;

    for (int i = 0; i < n; i++)
        processes[i].remaining = processes[i].burst;

    int time = 0;
    for (int i = 0; i < n; i++)
        q.push(i);

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        int execTime = min(quantum, processes[i].remaining);

        for (int t = 0; t < execTime; t++)
            gantt.push_back(processes[i].id);

        time += execTime;
        processes[i].remaining -= execTime;

        if (processes[i].remaining > 0)
            q.push(i);
        else {
            processes[i].completion = time;
            processes[i].turnaround = time - processes[i].arrival;
            processes[i].waiting =
                processes[i].turnaround - processes[i].burst;
        }
    }

    double avgWT = 0, avgTAT = 0;

    cout << "ID\tBT\tCT\tTAT\tWT\n";
    for (auto &p : processes) {
        cout << p.id << "\t" << p.burst << "\t"
             << p.completion << "\t" << p.turnaround << "\t"
             << p.waiting << "\n";
        avgWT += p.waiting;
        avgTAT += p.turnaround;
    }

    cout << "Average WT: " << avgWT / n << "\n";
    cout << "Average TAT: " << avgTAT / n << "\n";

    cout << "Gantt Chart:\n| ";
    for (int id : gantt)
        cout << "P" << id << " | ";
    cout << "\n";
}

/* ====================== PAGE REPLACEMENT ====================== */

/* ---------- FIFO ---------- */
int fifoPageFaults(vector<int> pages, int frames) {
    unordered_map<int, bool> inMemory;
    queue<int> q;
    int faults = 0;

    for (int page : pages) {
        if (!inMemory[page]) {
            faults++;
            if (q.size() == frames) {
                int old = q.front();
                q.pop();
                inMemory[old] = false;
            }
            q.push(page);
            inMemory[page] = true;
        }
    }
    return faults;
}

/* ---------- LRU ---------- */
int lruPageFaults(vector<int> pages, int frames) {
    vector<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        auto it = find(memory.begin(), memory.end(), page);

        if (it == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int lruIndex = -1, farthest = i;
                for (int j = 0; j < memory.size(); j++) {
                    int k;
                    for (k = i - 1; k >= 0; k--)
                        if (pages[k] == memory[j])
                            break;
                    if (k < farthest) {
                        farthest = k;
                        lruIndex = j;
                    }
                }
                memory.erase(memory.begin() + lruIndex);
            }
            memory.push_back(page);
        }
    }
    return faults;
}

/* ---------- Optimal ---------- */
int optimalPageFaults(vector<int> pages, int frames) {
    vector<int> memory;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int page = pages[i];
        if (find(memory.begin(), memory.end(), page) == memory.end()) {
            faults++;
            if (memory.size() == frames) {
                int idx = -1, farthest = i;
                for (int j = 0; j < memory.size(); j++) {
                    int k;
                    for (k = i + 1; k < pages.size(); k++)
                        if (pages[k] == memory[j])
                            break;
                    if (k > farthest) {
                        farthest = k;
                        idx = j;
                    }
                }
                memory.erase(memory.begin() + idx);
            }
            memory.push_back(page);
        }
    }
    return faults;
}

/* ====================== MAIN ====================== */

int main() {

    vector<Process> processes = {
        {1, 0, 5},
        {2, 1, 3},
        {3, 2, 8}
    };

    fcfs(processes);
    sjf(processes);
    roundRobin(processes, 2);

    vector<int> pages = {1,2,3,4,1,2,5,1,2,3,4,5};
    int frames = 3;

    cout << "\n=== Page Replacement Comparison ===\n";
    cout << "FIFO Faults: " << fifoPageFaults(pages, frames) << "\n";
    cout << "LRU Faults: " << lruPageFaults(pages, frames) << "\n";
    cout << "Optimal Faults: " << optimalPageFaults(pages, frames) << "\n";

    return 0;
}
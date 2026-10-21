#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Structure to store process information
struct Process {
    int pid;                 // Process number (1, 2, 3...)
    int at, bt, priority;    // Arrival Time, Burst Time, Priority
    int ct = 0, tat = 0, wt = 0, rt = -1; // CT, TAT, WT, RT
    int remaining;          // Remaining burst time
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);

    // Input process details
    for (int i = 0; i < n; i++) {

        // Auto assign process number (P1, P2, ...)
        p[i].pid = i + 1;

        cout << "\nProcess P" << p[i].pid << ":\n";

        cout << "Arrival Time: ";
        cin >> p[i].at;

        cout << "Burst Time: ";
        cin >> p[i].bt;

        cout << "Priority: ";
        cin >> p[i].priority;

        p[i].remaining = p[i].bt;
    }

    int time = 0, completed = 0;

    // Run until all processes are completed
    while (completed < n) {
        int idx = -1;
        int highestPriority = INT_MIN;

        // Find highest priority process available
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].remaining > 0) {
                if (p[i].priority > highestPriority) {          //**
                    highestPriority = p[i].priority;
                    idx = i;
                }
            }
        }

        // If no process available → CPU idle
        if (idx == -1) {
            time++;
            continue;
        }

        // First response time
        if (p[idx].rt == -1) {
            p[idx].rt = time - p[idx].at;
        }

        // Execute for 1 unit
        p[idx].remaining--;
        time++;

        // If process finished
        if (p[idx].remaining == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }

    // Output
    double avgCT = 0, avgTAT = 0, avgWT = 0, avgRT = 0;

    cout << "\n\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++) {

        cout << "P" << p[i].pid << "\t"
             << p[i].at << "\t"
             << p[i].bt << "\t"
             << p[i].priority << "\t"
             << p[i].ct << "\t"
             << p[i].tat << "\t"
             << p[i].wt << "\t"
             << p[i].rt << "\n";

        avgCT += p[i].ct;
        avgTAT += p[i].tat;
        avgWT += p[i].wt;
        avgRT += p[i].rt;
    }

    cout << "\nAverage CT = " << avgCT / n;
    cout << "\nAverage TAT = " << avgTAT / n;
    cout << "\nAverage WT = " << avgWT / n;
    cout << "\nAverage RT = " << avgRT / n;

    return 0;
}

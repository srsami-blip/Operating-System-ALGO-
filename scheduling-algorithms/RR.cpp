#include <iostream>
#include <queue>
using namespace std;

struct Process {
    int id;                 // Process ID
    int arrivalTime;        // Arrival Time
    int burstTime;          // Burst Time
    int remainingTime;      // Remaining Burst Time
    int completionTime;     // Completion Time
    int turnaroundTime;     // Turnaround Time
    int waitingTime;        // Waiting Time
    int responseTime;       // Response Time
    bool started;           // First time execution check
};

int main() {
    int n, quantum;

    cout << "Enter number of processes: ";
    cin >> n;

    Process p[n];
    queue<int> q;           // Ready queue (FIFO)
    bool inQueue[n] = {false}; // Track if process is already in queue

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;

        cout << "Enter Arrival Time and Burst Time for P" << i + 1 << ": ";
        cin >> p[i].arrivalTime >> p[i].burstTime;

        p[i].remainingTime = p[i].burstTime; // Initially full burst time
        p[i].started = false; // Not started yet
    }

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    int currentTime = 0;   // CPU current time
    int completed = 0;     // Count of completed processes

    // Add processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].arrivalTime == 0) {
            q.push(i);
            inQueue[i] = true;
        }
    }

    // Main RR scheduling loop
    while (completed < n) {

        // If queue is empty, CPU is idle
        if (q.empty()) {
            currentTime++;

            // Check new arrivals
            for (int i = 0; i < n; i++) {
                if (p[i].arrivalTime <= currentTime && !inQueue[i] && p[i].remainingTime > 0) {
                    q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int i = q.front();  // Get front process
        q.pop();

        // Calculate Response Time (first execution only)
        if (!p[i].started) {
            p[i].responseTime = currentTime - p[i].arrivalTime;
            p[i].started = true;
        }

        // Execute process for time quantum or remaining time
        int execTime = min(quantum, p[i].remainingTime);
        p[i].remainingTime -= execTime;
        currentTime += execTime;

        // Check new arrivals during execution
        for (int j = 0; j < n; j++) {
            if (p[j].arrivalTime <= currentTime && !inQueue[j] && p[j].remainingTime > 0) {
                q.push(j);
                inQueue[j] = true;
            }
        }

        // If process not finished, add back to queue
        if (p[i].remainingTime > 0) {
            q.push(i);
        }
        else {
            // Process finished
            p[i].completionTime = currentTime;
            p[i].turnaroundTime = p[i].completionTime - p[i].arrivalTime;
            p[i].waitingTime = p[i].turnaroundTime - p[i].burstTime;
            completed++;
        }
    }

    // Variables for average calculation
    float avgTAT = 0, avgWT = 0, avgRT = 0;

    // Print results
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n";

    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t"
             << p[i].arrivalTime << "\t"
             << p[i].burstTime << "\t"
             << p[i].completionTime << "\t"
             << p[i].turnaroundTime << "\t"
             << p[i].waitingTime << "\t"
             << p[i].responseTime << endl;

        avgTAT += p[i].turnaroundTime;
        avgWT += p[i].waitingTime;
        avgRT += p[i].responseTime;
    }

    // Print averages
    cout << "\nAverage TAT = " << avgTAT / n;
    cout << "\nAverage WT = " << avgWT / n;
    cout << "\nAverage RT = " << avgRT / n << endl;

    return 0;
}

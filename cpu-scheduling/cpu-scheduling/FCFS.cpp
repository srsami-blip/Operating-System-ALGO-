#include <iostream>
using namespace std;

int main() {
    int n;

    // Input number of processes
    cout << "Enter number of processes: ";
    cin >> n;

    int arrival[n], burst[n];
    int start[n], completion[n];
    int waiting[n], turnaround[n], response[n];

    // Take Arrival time first, then Burst time
    for(int i = 0; i < n; i++) {
        cout << "Enter arrival time of P" << i+1 << ": ";
        cin >> arrival[i];

        cout << "Enter burst time of P" << i+1 << ": ";
        cin >> burst[i];
    }

    // Sort processes according to arrival time (simple bubble sort)
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arrival[j] > arrival[j+1]) {

                // Swap arrival times
                swap(arrival[j], arrival[j+1]);

                // Swap burst times
                swap(burst[j], burst[j+1]);
            }
        }
    }

    int current_time = 0;
    float total_wt = 0, total_tat = 0;

    // Calculate times
    for(int i = 0; i < n; i++) {

        // If CPU is idle, move time forward
        if(current_time < arrival[i]) {
            current_time = arrival[i];
        }

        // Start time
        start[i] = current_time;

        // Completion time
        completion[i] = start[i] + burst[i];

        // Turnaround time = CT - AT
        turnaround[i] = completion[i] - arrival[i];

        // Waiting time = TAT - BT
        waiting[i] = turnaround[i] - burst[i];

        // Response time = Start - Arrival
        response[i] = start[i] - arrival[i];

        // Add to totals
        total_wt += waiting[i];
        total_tat += turnaround[i];

        // Update current time
        current_time = completion[i];
    }

    // Output table header
cout << "\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n";

for(int i = 0; i < n; i++) {
    cout << "P" << i+1 << "\t"
         << arrival[i] << "\t"
         << burst[i] << "\t"
         << completion[i] << "\t"
         << turnaround[i] << "\t"   // TAT
         << waiting[i] << "\t"      // WT
         << response[i] << endl;    // RT
}


    // Print averages
    cout << "\nAverage Waiting Time: " << total_wt / n << endl;
    cout << "Average Turnaround Time: " << total_tat / n << endl;

    return 0;
}

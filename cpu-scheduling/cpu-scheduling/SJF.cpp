#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter number of processes: ";
    cin >> n;

    int arrival[n], burst[n], process[n];
    int completion[n], turnaround[n], waiting[n], response[n];
    bool completed[n];

    //  Take Arrival time first, then Burst time
    for(int i = 0; i < n; i++) {
        cout << "Enter arrival time of P" << i+1 << ": ";
        cin >> arrival[i];

        cout << "Enter burst time of P" << i+1 << ": ";
        cin >> burst[i];

        process[i] = i+1;    // Process ID
        completed[i] = false; // Initially not completed
    }

    //  Step 1: Bubble sort by Arrival Time
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(arrival[j] > arrival[j+1]) {
                swap(arrival[j], arrival[j+1]);
                swap(burst[j], burst[j+1]);
                swap(process[j], process[j+1]);
            }
        }
    }

    int currentTime = 0;
    int done = 0;
    float totalWT = 0, totalTAT = 0;

    while(done < n) {
        int shortest = -1;
        int minBurst = 9999;

        //  Find shortest job among arrived processes
        for(int i = 0; i < n; i++) {
            if(arrival[i] <= currentTime && !completed[i]) {
                // If burst time smaller, select
                if(burst[i] < minBurst) {
                    minBurst = burst[i];
                    shortest = i;
                }
                // If burst time same, choose earlier arrival
                else if(burst[i] == minBurst) {
                    if(arrival[i] < arrival[shortest])
                        shortest = i;
                    // If even arrival same, choose smaller process ID
                    else if(arrival[i] == arrival[shortest] && process[i] < process[shortest])
                        shortest = i;
                }
            }
        }

        if(shortest == -1) {
            currentTime++;
        } else {
            response[shortest] = currentTime - arrival[shortest];
            currentTime += burst[shortest];
            completion[shortest] = currentTime;
            turnaround[shortest] = completion[shortest] - arrival[shortest];
            waiting[shortest] = turnaround[shortest] - burst[shortest];

            totalWT += waiting[shortest];
            totalTAT += turnaround[shortest];

            completed[shortest] = true;
            done++;
        }
    }

    //  Output Table
    cout << "\nP\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << process[i] << "\t"
             << arrival[i] << "\t"
             << burst[i] << "\t"
             << completion[i] << "\t"
             << turnaround[i] << "\t"
             << waiting[i] << "\t"
             << response[i] << "\n";
    }

    //  Average Waiting & Turnaround Time
    cout << "\nAverage Waiting Time: " << totalWT/n;
    cout << "\nAverage Turnaround Time: " << totalTAT/n << endl;

    return 0;
}

#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int arrival[n], burst[n], remaining[n], process[n];
    int completion[n], turnaround[n], waiting[n], response[n];
    bool started[n];

    //  Input Arrival Time and Burst Time
    for(int i = 0; i < n; i++) {
        cout << "Enter arrival time of P" << i+1 << ": ";
        cin >> arrival[i];

        cout << "Enter burst time of P" << i+1 << ": ";
        cin >> burst[i];

        remaining[i] = burst[i]; // Remaining time initially = burst time
        process[i] = i+1;        // Process ID
        started[i] = false;      // To check first start for RT
    }

    int currentTime = 0, completedCount = 0;
    float totalWT = 0, totalTAT = 0;

    while(completedCount < n) {
        int idx = -1;
        int minRemaining = 9999;

        //  Find process with smallest remaining time among arrived
        for(int i = 0; i < n; i++) {
            if(arrival[i] <= currentTime && remaining[i] > 0) {
                if(remaining[i] < minRemaining) {
                    minRemaining = remaining[i];
                    idx = i;
                }
                else if(remaining[i] == minRemaining) {
                    // Tie-breaker: earlier arrival
                    if(arrival[i] < arrival[idx])
                        idx = i;
                    // Tie-breaker: smaller process ID
                    else if(arrival[i] == arrival[idx] && process[i] < process[idx])
                        idx = i;
                }
            }
        }

        if(idx == -1) {
            currentTime++; // No process available yet
        } else {
            //  First time process starts → set Response Time
            if(!started[idx]) {
                response[idx] = currentTime - arrival[idx];
                started[idx] = true;
            }

            //  Execute process for 1 unit of time
            remaining[idx]--;
            currentTime++;

            //  If process finishes
            if(remaining[idx] == 0) {
                completion[idx] = currentTime;
                turnaround[idx] = completion[idx] - arrival[idx];
                waiting[idx] = turnaround[idx] - burst[idx];

                totalWT += waiting[idx];
                totalTAT += turnaround[idx];

                completedCount++;
            }
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

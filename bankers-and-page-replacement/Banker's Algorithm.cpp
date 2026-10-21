#include <iostream>
using namespace std;

int main()
{
    int p, r;

    cout << "Enter number of processes: ";
    cin >> p;

    cout << "Enter number of resource types: ";
    cin >> r;

    int allocation[10][10], maximum[10][10], need[10][10];
    int available[10];
    int work[10];
    bool finish[10] = {false};
    int safeSequence[10];

    // Allocation Matrix
    cout << "\nEnter Allocation Matrix:\n";
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < r; j++)
        {
            cin >> allocation[i][j];
        }
    }

    // Maximum Matrix
    cout << "\nEnter Maximum Matrix:\n";
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < r; j++)
        {
            cin >> maximum[i][j];
        }
    }

    // Available Resources
    cout << "\nEnter Available Resources:\n";
    for(int i = 0; i < r; i++)
    {
        cin >> available[i];
        work[i] = available[i];
    }

    // Need = Maximum - Allocation
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < r; j++)
        {
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    // Print Need Matrix
    cout << "\nNeed Matrix:\n";
    for(int i = 0; i < p; i++)
    {
        for(int j = 0; j < r; j++)
        {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    int count = 0;

    while(count < p)
    {
        bool found = false;

        for(int i = 0; i < p; i++)
        {
            if(finish[i] == false)
            {
                bool possible = true;

                // Check if Need <= Work
                for(int j = 0; j < r; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if(possible)
                {
                    // Release allocated resources
                    for(int j = 0; j < r; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if(found == false)
        {
            break;
        }
    }

    if(count == p)
    {
        cout << "\nSystem is in Safe State.\n";
        cout << "Safe Sequence: ";

        for(int i = 0; i < p; i++)
        {
            cout << "P" << safeSequence[i];

            if(i != p - 1)
                cout << " -> ";
        }
    }
    else
    {
        cout << "\nSystem is NOT in Safe State.";
    }

    return 0;
}

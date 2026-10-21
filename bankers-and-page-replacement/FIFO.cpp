#include <iostream>
using namespace std;

int main()
{
    int n, f;

    cout << "Enter number of pages: ";
    cin >> n;

    int page[n];

    cout << "Enter page reference string: ";
    for (int i = 0; i < n; i++)
        cin >> page[i];

    cout << "Enter number of frames: ";
    cin >> f;

    int frame[f];

    // Initially all frames are empty
    for (int i = 0; i < f; i++)
        frame[i] = -1;

    int front = 0;      // Points to the oldest page (FIFO)
    int hit = 0;
    int fault = 0;

    // Traverse every page in the reference string
    for (int i = 0; i < n; i++)
    {
        bool found = false;

        // Check whether the page is already present
        for (int j = 0; j < f; j++)
        {
            if (frame[j] == page[i])
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            hit++;      // Page Hit
        }
        else
        {
            // Replace the oldest page
            frame[front] = page[i];

            // Move to the next oldest frame
            front = (front + 1) % f;

            fault++;    // Page Fault
        }
    }

    cout << "\nTotal Page Hit = " << hit << endl;
    cout << "Total Page Fault = " << fault << endl;

    // Hit Ratio = Hits / Total Pages
    cout << "Hit Ratio = " << (float)hit / n << endl;

    // Fault Ratio = Faults / Total Pages
    cout << "Fault Ratio = " << (float)fault / n << endl;

    return 0;
}

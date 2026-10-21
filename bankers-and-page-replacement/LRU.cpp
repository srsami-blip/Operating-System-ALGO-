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

    int hit = 0;
    int fault = 0;

    // Traverse every page
    for (int i = 0; i < n; i++)
    {
        bool found = false;

        // Check whether page is already present
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
            fault++;    // Page Fault

            bool empty = false;

            // Check for an empty frame
            for (int j = 0; j < f; j++)
            {
                if (frame[j] == -1)
                {
                    frame[j] = page[i];
                    empty = true;
                    break;
                }
            }

            // If no empty frame, apply LRU replacement
            if (!empty)
            {
                int pos = -1;
                int least = i;

                // Check every page in the frame
                for (int j = 0; j < f; j++)
                {
                    int k;

                    // Search backward to find last use
                    for (k = i - 1; k >= 0; k--)
                    {
                        if (frame[j] == page[k])
                            break;
                    }

                    // Keep the page used farthest in the past
                    if (k < least)
                    {
                        least = k;
                        pos = j;
                    }
                }

                // Replace the least recently used page
                frame[pos] = page[i];
            }
        }
    }

    cout << "\nTotal Page Hit = " << hit << endl;
    cout << "Total Page Fault = " << fault << endl;

    cout << "Hit Ratio = " << (float)hit / n << endl;
    cout << "Fault Ratio = " << (float)fault / n << endl;

    return 0;
}

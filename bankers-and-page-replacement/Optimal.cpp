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

            // If no empty frame, apply Optimal replacement
            if (!empty)
            {
                int pos = -1;
                int farthest = -1;

                // Check every page in the frame
                for (int j = 0; j < f; j++)
                {
                    int k;

                    // Find next use of frame[j]
                    for (k = i + 1; k < n; k++)
                    {
                        if (frame[j] == page[k])
                            break;
                    }

                    // If page is never used again, replace it
                    if (k == n)
                    {
                        pos = j;
                        break;
                    }

                    // Keep the page used farthest in the future
                    if (k > farthest)
                    {
                        farthest = k;
                        pos = j;
                    }
                }

                // Replace the selected page
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

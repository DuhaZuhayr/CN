#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int WINDOW_SIZE = 4;
const int TOTAL_FRAMES = 10;

int main()
{
    srand(time(0)); // Seed random number generator

    bool received[TOTAL_FRAMES] = {false}; // Track received frames
    int base = 0;

    while (base < TOTAL_FRAMES)
    {
        cout << "\nSender Window: [" << base << " - "
             << min(base + WINDOW_SIZE - 1, TOTAL_FRAMES - 1) << "]" << endl;

        // Send frames that haven't been received
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i)
        {
            if (!received[i])
            {
                cout << "Sending frame: " << i << endl;
            }
        }

        // Simulate reception of each frame
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i)
        {
            if (!received[i])
            {
                if (rand() % 10 < 3)
                {
                    cout << "Frame " << i << " lost!" << endl;
                }
                else
                {
                    received[i] = true;
                    cout << "Received frame: " << i << " (ACK sent)" << endl;
                }
            }
        }

        // Slide window base forward for all consecutively received frames
        while (base < TOTAL_FRAMES && received[base])
        {
            ++base;
        }
    }

    cout << "\nAll frames sent successfully!" << endl;
    return 0;
}

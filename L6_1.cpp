#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int WINDOW_SIZE = 4;
const int TOTAL_FRAMES = 10;

int main()
{
    srand(time(0)); // Seed for random number generation

    int base = 0;

    while (base < TOTAL_FRAMES)
    {
        cout << "\nSender Window: [" << base << " - "
             << min(base + WINDOW_SIZE - 1, TOTAL_FRAMES - 1) << "]" << endl;

        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i)
        {
            cout << "Sending frame: " << i << endl;
        }

        int lostFrame = (rand() % 10 < 3) ? (base + rand() % WINDOW_SIZE) : -1;

        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; ++i)
        {
            if (i == lostFrame)
            {
                cout << "Frame " << i << " lost!" << endl;
                break;
            }
            else
            {
                cout << "Received frame: " << i << endl;
            }
        }

        if (lostFrame != -1)
        {
            cout << "Timeout! Retransmitting from frame " << lostFrame << endl;
            base = lostFrame;
        }
        else
        {
            base += WINDOW_SIZE;
        }
    }

    cout << "\nAll frames sent successfully!" << endl;
    return 0;
}

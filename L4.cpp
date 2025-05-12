#include <iostream>
using namespace std;

int main() {
    int fs, gs;
    cout << "\nEnter Frame size: ";
    cin >> fs;
    if (fs <= 0 || fs > 20) {
        cout << "\nInvalid frame size. Please enter a size between 1 and 20.";
        return 1;
    }

    int f[20];
    cout << "\nEnter Frame (only 0s and 1s): \n";
    for (int i = 0; i < fs; i++) {
        cin >> f[i];
        if (f[i] != 0 && f[i] != 1) {
            cout << "\nInvalid input. Enter only binary values (0 or 1).";
            return 1;
        }
    }

    cout << "\nEnter Generator size: ";
    cin >> gs;
    if (gs <= 0 || gs > 20) {
        cout << "\nInvalid generator size. Please enter a size between 1 and 20.";
        return 1;
    }

    int g[20];
    cout << "\nEnter Generator (only 0s and 1s): \n";
    for (int i = 0; i < gs; i++) {
        cin >> g[i];
        if (g[i] != 0 && g[i] != 1) {
            cout << "\nInvalid input. Enter only binary values (0 or 1).";
            return 1;
        }
    }
    if (g[0] != 1) {
        cout << "\nInvalid generator. The first bit must be 1.";
        return 1;
    }

    int rs = gs - 1;
    cout << "\nNumber of 0's to be appended: " << rs;
    for (int i = fs; i < fs + rs; i++) {
        f[i] = 0;
    }

    int temp[20];
    for (int i = 0; i < 20; i++) {
        temp[i] = f[i];
    }

    for (int i = 0; i < fs; i++) {
        if (temp[i] == 1) {
            for (int j = 0, k = i; j < gs; j++, k++) {
                temp[k] = (temp[k] == g[j]) ? 0 : 1;
            }
        }
    }

    int crc[15];
    for (int i = 0, j = fs; i < rs; i++, j++) {
        crc[i] = temp[j];
    }

    cout << "\nCRC bits: ";
    for (int i = 0; i < rs; i++) {
        cout << crc[i];
    }

    int tf[20];
    for (int i = 0; i < fs; i++) {
        tf[i] = f[i];
    }
    for (int i = fs, j = 0; i < fs + rs; i++, j++) {
        tf[i] = crc[j];
    }

    cout << "\nTransmitted Frame: ";
    for (int i = 0; i < fs + rs; i++) {
        cout << tf[i];
    }

    int rf[20];
    cout << "\n\nReceiver Side - Enter Received Frame (including CRC bits, only 0s and 1s): \n";
    for (int i = 0; i < fs + rs; i++) {
        cin >> rf[i];
        if (rf[i] != 0 && rf[i] != 1) {
            cout << "\nInvalid input. Enter only binary values (0 or 1).";
            return 1;
        }
    }

    for (int i = 0; i < fs + rs; i++) {
        temp[i] = rf[i];
    }

    for (int i = 0; i < fs; i++) {
        if (temp[i] == 1) {
            for (int j = 0, k = i; j < gs; j++, k++) {
                temp[k] = (temp[k] == g[j]) ? 0 : 1;
            }
        }
    }

    int rrem[15];
    cout << "\nRemainder after division: ";
    bool errorDetected = false;
    for (int i = fs, j = 0; i < fs + rs; i++, j++) {
        rrem[j] = temp[i];
        cout << rrem[j];
        if (rrem[j] != 0) {
            errorDetected = true;
        }
    }

    if (!errorDetected) {
        cout << "\nSince Remainder is 0, the message is CORRECT!";
    } else {
        cout << "\nSince Remainder is NOT 0, the message contains an ERROR!";
    }

    return 0;
}

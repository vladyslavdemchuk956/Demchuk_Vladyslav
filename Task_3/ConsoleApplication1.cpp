#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int main() {
    srand(time(0));

    int n, k;
    int v = 11;

    cout << "n: ";
    cin >> n;
    cout << "k: ";
    cin >> k;

    int** a = new int* [n];
    for (int i = 0; i < n; i++) {
        a[i] = new int[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % (21 - (-21) + 1) + (-21);
        }
    }

    cout << "\nMatrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }

    int count3 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i && j >= n - 1 - i) {
                if (a[i][j] < k) {
                    count3++;
                }
            }
        }
    }

    int min_val = a[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] < min_val) {
                min_val = a[i][j];
            }
        }
    }

    int count6 = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > n - 1 - j && i > j) {
                count6++;
                a[i][j] = min_val;
            }
        }
    }

    cout << "\nCount Sector 3: " << count3 << endl;
    cout << "Min value: " << min_val << endl;
    cout << "Count Sector 6: " << count6 << endl;

    cout << "\nNew Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << a[i][j];
        }
        cout << endl;
    }

    for (int i = 0; i < n; i++) {
        delete[] a[i];
    }
    delete[] a;

    system("pause");
    return 0;
}
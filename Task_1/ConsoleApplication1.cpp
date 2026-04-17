#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <future>
#include <iomanip>

using namespace std;

void printArray(const vector<int>& arr, string message) {
    cout << message << ": ";
    for (int i = 0; i < (arr.size() < 15 ? arr.size() : 15); i++) {
        cout << arr[i] << " ";
    }
    cout << "... [size: " << arr.size() << "]" << endl;
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;
    int max_val = *max_element(arr.begin(), arr.end());
    vector<int> count(max_val + 1, 0);
    for (int x : arr) count[x]++;
    int index = 0;
    for (int i = 0; i <= max_val; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
}


int binarySearch(const vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    vector<long> sizes = { 15, 150, 2000, 9000, 40000, 140000 };

    cout << "Table of results (t=f(n)):" << endl;
    cout << "n\t| Insertion\t| Counting\t| Quick Sort" << endl;
    cout << "----------------------------------------------------" << endl;

    for (long n : sizes) {
        vector<int> base(n);
        for (int i = 0; i < n; i++) base[i] = rand() % 10000;


        auto s1 = chrono::high_resolution_clock::now();
        vector<int> a = base;
        if (n <= 40000) insertionSort(a);
        auto e1 = chrono::high_resolution_clock::now();

        auto s2 = chrono::high_resolution_clock::now();
        vector<int> b = base;
        countingSort(b);
        auto e2 = chrono::high_resolution_clock::now();

        auto s3 = chrono::high_resolution_clock::now();
        vector<int> c = base;
        sort(c.begin(), c.end());
        auto e3 = chrono::high_resolution_clock::now();

        chrono::duration<double> t1 = e1 - s1;
        chrono::duration<double> t2 = e2 - s2;
        chrono::duration<double> t3 = e3 - s3;

        cout << n << "\t| " << fixed << setprecision(5);
        if (n > 40000) cout << "Too long\t| "; else cout << t1.count() << "s\t| ";
        cout << t2.count() << "s\t| " << t3.count() << "s" << endl;
    }
    cout << "\nStarting asynchronous sorting for 40000 elements..." << endl;
    vector<int> async_data(40000);
    for (int& x : async_data) x = rand() % 10000;

    auto future_res = async(launch::async, [&]() {
        auto start = chrono::high_resolution_clock::now();
        sort(async_data.begin(), async_data.end());
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration<double>(end - start).count();
        });

    cout << "Main thread is free while sorting..." << endl;
    double async_time = future_res.get();
    cout << "Asynchronous sorting finished in: " << async_time << "s" << endl;


    int target;
    cout << "\nEnter number to find (0-10000): ";
    cin >> target;
    int pos = binarySearch(async_data, target);
    if (pos != -1) cout << "Element found at index: " << pos << endl;
    else cout << "Element not found." << endl;

    return 0;
}
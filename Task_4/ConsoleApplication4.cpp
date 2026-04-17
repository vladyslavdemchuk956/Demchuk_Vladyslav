#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    ifstream fin("input.txt.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    vector<string> sentences;
    string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            sentences.push_back(line);
        }
    }
    fin.close();

    if (sentences.size() < 2) {
        cout << "Need at least 2 sentences!" << endl;
        return 0;
    }

    int max_diff = -1;
    string res1 = "";
    string res2 = "";

    for (int i = 0; i < sentences.size(); i++) {
        long long sum1 = 0;
        for (char c : sentences[i]) {
            sum1 += (int)c;
        }

        for (int j = i + 1; j < sentences.size(); j++) {
            long long sum2 = 0;
            for (char c : sentences[j]) {
                sum2 += (int)c;
            }

            int diff = abs((int)(sum1 - sum2));
            if (diff > max_diff) {
                max_diff = diff;
                res1 = sentences[i];
                res2 = sentences[j];
            }
        }
    }

    cout << "Max difference found: " << max_diff << endl;
    cout << "Sentences saved to output.txt" << endl;

    fout << "Sentence 1: " << res1 << endl;
    fout << "Sentence 2: " << res2 << endl;
    fout << "Difference: " << max_diff << endl;

    fout.close();

    system("pause");
    return 0;
}
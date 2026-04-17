#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Game {
    string title;
    string genre;
    int year;
    float criticScore;
    float userScore;
};

int main() {
    int choice;
    string filename = "games.txt";

    while (true) {
        cout << "\n1. Add Game\n2. View All Games\n3. Top 3 Games\n4. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) {
            Game g;
            cout << "Title: "; cin.ignore(); getline(cin, g.title);
            cout << "Genre: "; getline(cin, g.genre);
            cout << "Year: "; cin >> g.year;
            cout << "Critic Score: "; cin >> g.criticScore;
            cout << "User Score: "; cin >> g.userScore;

            ofstream fout(filename, ios::app);
            fout << g.title << "|" << g.genre << "|" << g.year << "|" << g.criticScore << "|" << g.userScore << endl;
            fout.close();
        }
        else if (choice == 2) {
            ifstream fin(filename);
            string line;
            cout << "\nAll Games:\n";
            while (getline(fin, line)) {
                cout << line << endl;
            }
            fin.close();
        }
        else if (choice == 3) {
            ifstream fin(filename);
            vector<Game> games;
            string t, gn;
            int y;
            float cs, us;

            string line;
            while (getline(fin, line)) {
                size_t p1 = line.find('|');
                size_t p2 = line.find('|', p1 + 1);
                size_t p3 = line.find('|', p2 + 1);
                size_t p4 = line.find('|', p3 + 1);

                if (p1 != string::npos) {
                    Game temp;
                    temp.title = line.substr(0, p1);
                    temp.genre = line.substr(p1 + 1, p2 - p1 - 1);
                    temp.year = stoi(line.substr(p2 + 1, p3 - p2 - 1));
                    temp.criticScore = stof(line.substr(p3 + 1, p4 - p3 - 1));
                    temp.userScore = stof(line.substr(p4 + 1));
                    games.push_back(temp);
                }
            }
            fin.close();

            // Сортування за сумою оцінок
            sort(games.begin(), games.end(), [](Game a, Game b) {
                return (a.criticScore + a.userScore) > (b.criticScore + b.userScore);
                });

            cout << "\nTOP 3 Games:\n";
            for (int i = 0; i < games.size() && i < 3; i++) {
                cout << i + 1 << ". " << games[i].title << " (Sum: " << games[i].criticScore + games[i].userScore << ")" << endl;
            }
        }
        else if (choice == 4) break;
    }

    return 0;
}
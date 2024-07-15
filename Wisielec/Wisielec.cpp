#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>

using namespace std;

void loadWords(const string& filename, vector<string>& words) {
    ifstream file(filename);
    if (!file) {
        cerr << "Nie mozna otworzyc pliku: " << filename << endl;
        exit(1);
    }

    string word;
    while (file >> word) {
        words.push_back(word);
    }
}

string selectRandomWord(const vector<string>& words) {
    srand(static_cast<unsigned int>(time(0)));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

void displayCurrentProgress(const string& word, const string& guessed) {
    for (char ch : word) {
        if (guessed.find(ch) != string::npos) {
            cout << ch << ' ';
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool isWordGuessed(const string& word, const string& guessed) {
    for (char ch : word) {
        if (guessed.find(ch) == string::npos) {
            return false;
        }
    }
    return true;
}

int main() {
    vector<string> words;
    loadWords("words.txt", words);

    string word = selectRandomWord(words);
    string guessed;
    int maxAttempts = 6;
    int wrongAttempts = 0;

    cout << "Gra w wisielca!" << endl;

    while (wrongAttempts < maxAttempts) {
        cout << "Slowo: ";
        displayCurrentProgress(word, guessed);

        char guess;
        cout << "Podaj litere: ";
        cin >> guess;
        guess = tolower(guess);

        if (guessed.find(guess) != string::npos) {
            cout << "Ta litera juz zostala podana!" << endl;
            continue;
        }

        guessed += guess;

        if (word.find(guess) == string::npos) {
            wrongAttempts++;
            cout << "Zla litera! Pozostalo prob: " << (maxAttempts - wrongAttempts) << endl;
        }
        else {
            cout << "Dobra litera!" << endl;
        }

        if (isWordGuessed(word, guessed)) {
            cout << "Gratulacje! Odgadles slowo: " << word << endl;
            break;
        }
    }

    if (wrongAttempts == maxAttempts) {
        cout << "Przegrales! Slowo to: " << word << endl;
    }

    return 0;
}

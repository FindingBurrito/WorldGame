#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>


using namespace std;

struct ScoreEntry {
    string playerName;
    int score;
};


class Game {
private:
    vector<string> wordBank;
    vector<ScoreEntry> highScores;


public:
    Game() {
        wordBank = {"computer", "keyboard", "program", "compile", "algorithm", "debug", "syntax"};
        srand(time(0));
    }

    string getScrambledWord(string word) {
        string scrambled = word;
        for (int i = scrambled.size() - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            swap(scrambled[i], scrambled[j]);
        }
        return scrambled;
    }

    string getRandomWord() {
        int index = rand() % wordBank.size();
        return wordBank[index];
    }
    void start() {
        loadScoresFromFile();

        int score = 0;
        string choice;

        cout << "Welcome to the Word Scramble Game!\n";
        cout << "Type 'quit' anytime to exit.\n\n";

        while (true) {
            string word = getRandomWord();
            string scrambled = getScrambledWord(word);

            cout << "Unscramble this word: " << scrambled << "\nYour guess: ";
            cin >> choice;

            if (choice == "quit") {
                break;
            }

            if (choice == word) {
                cout << "Correct!\n";
                score += 10;
            } else {
                cout << "Wrong! The correct word was: " << word << "\n";
            }

            cout << "Current score: " << score << "\n\n";
        }

        cout << "Game Over! Your final score is: " << score << "\n";

        string playerName;
        cout << "Enter your name for the high score list: ";
        cin >> playerName;

        addScore(playerName, score);
        showHighScores();
        saveScoresToFile();


    }
    void addScore(string name, int score) {
    highScores.push_back({name, score});

    // Bubble Sort to sort scores in descending order
    for (size_t i = 0; i < highScores.size(); ++i) {
        for (size_t j = 0; j < highScores.size() - i - 1; ++j) {
            if (highScores[j].score < highScores[j + 1].score) {
                swap(highScores[j], highScores[j + 1]);
            }
        }
    }
}

    void showHighScores() {
    cout << "\n--- High Scores ---\n";
    int limit = min(5, (int)highScores.size());
    for (int i = 0; i < limit; ++i) {
        cout << i + 1 << ". " << highScores[i].playerName << " - " << highScores[i].score << "\n";
    }
    cout << "-------------------\n";
}

    void saveScoresToFile() {
    ofstream outFile("highscores.txt");
    for (const auto& entry : highScores) {
        outFile << entry.playerName << " " << entry.score << "\n";
    }
    outFile.close();
}

    void loadScoresFromFile() {
    ifstream inFile("highscores.txt");
    string name;
    int score;
    highScores.clear();

    while (inFile >> name >> score) {
        highScores.push_back({name, score});
    }

    inFile.close();

    // Sort after loading
    for (size_t i = 0; i < highScores.size(); ++i) {
        for (size_t j = 0; j < highScores.size() - i - 1; ++j) {
            if (highScores[j].score < highScores[j + 1].score) {
                swap(highScores[j], highScores[j + 1]);
            }
        }
    }
}

};

int main() {
    Game game;
    game.start();
    return 0;
}


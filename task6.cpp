#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
using namespace std;

int calculateCost(int currentIndex, int totalWords, vector<int>& wordLengths, int lineWidth, vector<int>& minCostMemo, vector<int>& breakPoints) {
    if (currentIndex >= totalWords)
        return 0;

    if (minCostMemo[currentIndex] != -1)
        return minCostMemo[currentIndex];

    int currentLineLength = 0;
    int minCost = INT_MAX;

    for (int i = currentIndex; i < totalWords; i++) {
        currentLineLength += wordLengths[i];
        int totalLengthWithSpaces = currentLineLength + (i - currentIndex);

        if (totalLengthWithSpaces > lineWidth)
            break;

        int cost;
        if (i != totalWords - 1) {
            cost = (lineWidth - totalLengthWithSpaces) * (lineWidth - totalLengthWithSpaces) + calculateCost(i + 1, totalWords, wordLengths, lineWidth, minCostMemo, breakPoints);
        }
        else {
            cost = 0;
        }

        if (cost < minCost) {
            minCost = cost;
            breakPoints[currentIndex] = i;
        }
    }

    return minCostMemo[currentIndex] = minCost;
}

void wrapWords(vector<string>& words, int lineWidth) {
    int totalWords = words.size();
    vector<int> wordLengths(totalWords);
    for (int i = 0; i < totalWords; ++i) {
        wordLengths[i] = words[i].length();
    }

    vector<int> minCostMemo(totalWords, -1);
    vector<int> breakPoints(totalWords, -1);
    int totalCost = calculateCost(0, totalWords, wordLengths, lineWidth, minCostMemo, breakPoints);

    int currentWord = 0;
    int lineNumber = 1;

    cout << "Output:" << endl;
    while (currentWord < totalWords) {
        int lastWordInLine = breakPoints[currentWord];
        cout << "line " << lineNumber++ << ": ";
        for (int i = currentWord; i <= lastWordInLine; ++i) {
            cout << words[i];
            if (i < lastWordInLine) {
                cout << " ";
            }
        }
        cout << endl;
        currentWord = lastWordInLine + 1;
    }

    cout << "Total cost: " << totalCost << endl;
}

int main() {
    int lineWidth;
    cout << "Enter the line width: ";
    cin >> lineWidth;
    cin.ignore();

    cout << "Enter the words: ";
    string input;
    getline(cin, input);

    stringstream ss(input);
    vector<string> words;
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    wrapWords(words, lineWidth);

    return 0;
}

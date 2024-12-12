// task1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<algorithm>

using namespace std;

//THE SORTING APPROACH (O(nlogn))

bool isAnagram_sorting(string word1, string word2) {
	if (word1.length() != word2.length()) {
		return false;
	}

	sort(word1.begin(), word1.end());
	sort(word2.begin(), word2.end());

	return word1 == word2;
}

//THE NESTED LOOPS APPROACH (O(n^2))

bool isAnagram_nested(string word1, string word2) {
	if (word1.length() != word2.length()) {
		return false;
	}

	for (int i = 0; i < word1.length(); i++) {
		bool found = false;
		for (int j = 0; j < word2.length(); j++) {
			if (word1[i] == word2[j]) {
				word2[j] = '\0';
				found = true;
				break;
			}
		}
		if (!found) {
			return false;
		}
	}
	return true;
}

int main()
{
	string w, w2;
	cout << "Enter two words: " << endl;
	getline(cin, w);
	getline(cin, w2);

	if (isAnagram_nested(w, w2)) {
		cout << w << " and " << w2 << " are anagrams." << endl;

	}
	else {
		cout << w << " and " << w2 << " are not anagrams." << endl;
	}


}
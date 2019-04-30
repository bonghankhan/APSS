#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

bool match(const string& pattern, const string& word) {
	int position = 0;

	while (position < word.size()
			&& position < pattern.size()
			&& (pattern[position] == '?' || pattern[position] == word[position])) {
		++position;
	}

	if (position == pattern.size()) {
		return position == word.size();
	}

	if (pattern[position] == '*') {
		for (int skip = 0; position + skip <= word.size(); ++skip) {
			if (match(pattern.substr(position + 1), word.substr(position + skip))) {
				return true;
			}
		}
	}

	return false;
}

int main() {
	int testCase, fileNameCount;
	string pattern, fileName;
	vector<string> result;

	cin >> testCase;

	while (testCase--) {
		cin >> pattern;
		cin >> fileNameCount;

		while (fileNameCount--) {
			cin >> fileName;

			if (match(pattern, fileName)) {
				result.push_back(fileName);
			}	
		}
	}

	for (string word : result) {
		cout << word << endl;
	}

	return 0;
}
/*
3
he?p
3
help
heap
helpp
*p*
3
help
papa
hellp
*bb*
1
babbbc

*/

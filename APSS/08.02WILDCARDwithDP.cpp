#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

int cache[101][101];
string pattern, word;

int matchMemorized(int p, int w) {
	int& ret = cache[p][w];

	if (ret != -1) {
		return ret;
	}

	while (w < word.size() && p < pattern.size()
		&& (pattern[p] == '?' || pattern[p] == word[w])) {

		/*++p;
		++w;*/
		return matchMemorized(p + 1, w + 1);
	}

	if (p == pattern.size()) {
		return w == word.size();
	}

	/*if (pattern[p] == '*') {
		for (int skip = 0; w <= word.size(); ++skip) {
			if (matchMemorized(p + 1, w + skip)) {
				return ret = 1;
			}
		}
	}*/

	if (pattern[p] == '*') {
		if (matchMemorized(p + 1, w)
			|| (w < word.size() && matchMemorized(p, w + 1))) {

			return ret = 1;
		}
	}

	return ret = 0;
}

int main() {
	int testCase, fileNameCount;
	vector<string> result;

	cin >> testCase;

	while (testCase--) {
		memset(cache, -1, sizeof(cache));
		cin >> pattern;
		cin >> fileNameCount;

		while (fileNameCount--) {
			cin >> word;

			if (matchMemorized(0, 0)) {
				result.push_back(word);
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

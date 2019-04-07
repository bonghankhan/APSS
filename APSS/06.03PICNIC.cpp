#include <iostream>
#include <iterator>

using namespace std;

int studentCount, result[50];
bool areFriends[10][10];
bool checkPair[10];

int countPairings(bool taken[10]) {
	int firstFree = -1;

	for (int i = 0; i < studentCount; i++) {
		if (!taken[i]) {
			firstFree = i;
			break;
		}
	}

	if (firstFree == -1) {
		return 1;
	}

	int ret = 0;

	for (int pairWith = firstFree + 1; pairWith < studentCount; pairWith++) {
		if (!taken[pairWith] && areFriends[firstFree][pairWith]) {
			taken[firstFree] = taken[pairWith] = true;
			ret += countPairings(taken);
			taken[firstFree] = taken[pairWith] = false;
		}
	}

	return ret;
}

int main() {
	int testCase;
	cin >> testCase;

	for (int cycle = 0; cycle < testCase; cycle++) {
		for (auto & temp : areFriends) {
			fill(temp, temp + size(temp), false);
		}

		fill(checkPair, checkPair + size(checkPair), false);

		int pairCount;
		cin >> studentCount >> pairCount;

		for (int pairCycle = 0; pairCycle < pairCount; pairCycle++) {
			int a, b;
			cin >> a >> b;

			areFriends[a][b] = true;
			areFriends[b][a] = true;
		}

		result[cycle] = countPairings(checkPair);
	}

	for (int cycle = 0; cycle < testCase; cycle++) {
		cout << result[cycle] << endl;
	}

	return 0;
}
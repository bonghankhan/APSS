#include <iostream>
using namespace std;



int numOfTestcase, totalStudent, numOfFriendPair;



bool areFriends[10][10] = { false };
bool havePair[10] = { false };

int countPairs(bool havePair[10]) {


	int minFree = -1;

	for (int i = 0; i<totalStudent; i++) {
		if (!havePair[i]) {
			minFree = i;
			break;
		}
	}


	if (minFree == -1) return 1;

	int count = 0;

	for (int student = minFree + 1; student<totalStudent; student++) {

		if (!havePair[student] && areFriends[minFree][student]) {
			//find first pair
			havePair[minFree] = true;
			havePair[student] = true;

			//From recursive call, we can find the pair of remaining friends
			count += countPairs(havePair);

			//After finding one count, we should restart the for loop to find the different combinations
			//Therefore, need to reset havePair to check other cases
			havePair[minFree] = false;
			havePair[student] = false;

		}
	}

	return count;

}

int main() {

	cin >> numOfTestcase;

	for (int i = 0; i<numOfTestcase; i++) {

		cin >> totalStudent >> numOfFriendPair;

		//        bool* areFriends[totalStudent][totalStudent]={false};
		//        bool* havePair[totalStudent]={false};


		//Set up the areFriends table
		int x, y;
		for (int j = 0; j < numOfFriendPair; j++) {

			cin >> x >> y;
			areFriends[x][y] = areFriends[y][x] = true;
		}
		cout << countPairs(havePair);

	}

	return 0;
}
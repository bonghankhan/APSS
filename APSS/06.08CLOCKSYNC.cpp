#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#define MAX 31

using namespace std;

const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
const char linked[SWITCHES][CLOCKS + 1] = {
	//1234567890123456
	 "xxx.............",
	 "...x...x.x.x....",
	 "....x.....x...xx",
	 "x...xxxx........",
	 "......xxx.x.x...",
	 "x.x...........xx",
	 "...x..........xx",
	 "....xx.x......xx",
	 ".xxxxx..........",
	 "...xxx...x...x.." };

bool areAligned(const vector<int>& clocks) {
	for(int value : clocks){
		if (value != 12) {
			return false;
		}
	}
	return true;
}

void push(vector<int>& clocks, int swtch) {
	for (int clock = 0; clock < CLOCKS; clock++) {
		if (linked[swtch][clock] == 'x') {
			clocks[clock] += 3;
			if (clocks[clock] == 15) {
				clocks[clock] = 3;
			}
		}
	}
}

int solve(vector<int>& clocks, int swtch) {
	if (swtch == SWITCHES) {
		return areAligned(clocks) ? 0 : INF;
	}

	int ret = INF;
	for (int cnt = 0; cnt < 4; cnt++) {
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch);
	}

	return ret;
}

int main() {
	int testCase, result[MAX];
	cin >> testCase;

	for (int cycle = 0; cycle < testCase; cycle++) {
		int hour;
		vector<int> data;
		for (int i = 0; i < CLOCKS; i++) {
			cin >> hour;
			data.push_back(hour);
		}

		result[cycle] = solve(data, 0);
	}

	for (int i = 0; i < testCase; i++) {
		cout << result[i] << endl;
	}

	return 0;
}

//12 6 6 6 6 6 12 12 12 12 12 12 12 12 12 12
//12 9 3 12 6 6 9 3 12 9 12 9 12 12 6 6
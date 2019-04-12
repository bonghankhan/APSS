#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 20001

using namespace std;

/*
int bruteForce(const vector<int>&  h) {
	int ret        = 0;
	int panelCount = h.size();

	for (int left = 0; left < panelCount; left++) {
		int minHeight = h[left];

		for (int right = left; right < panelCount; right++) {
			minHeight = min(minHeight, h[right]);
			ret       = max(ret, (right - left + 1) * minHeight);
		}
	}

	return ret;
}
*/

vector<int> panelHeight(MAX);

int solve(int left, int right) {
	if (left == right) {
		return panelHeight[left];
	}

	int mid = (left + right) / 2;
	int ret = max(solve(left, mid), solve(mid + 1, right));

	int lo = mid, hi = mid + 1;
	int height = min(panelHeight[lo], panelHeight[hi]);

	ret = max(ret, height * 2);

	while (left < lo || hi < right) {
		if (hi < right && (lo == left || panelHeight[lo - 1] < panelHeight[hi + 1])) {
			hi++;
			height = min(height, panelHeight[hi]);
		}
		else {
			lo--;
			height = min(height, panelHeight[lo]);
		}

		ret = max(ret, height * (hi - lo + 1));
	}

	return ret;

}

int main() {
	int testCase, panelCount, size, result[50];
	cin >> testCase;

	for (int cycle = 0; cycle < testCase; cycle++) {
		cin >> panelCount;
		
		for (int i = 0; i < panelCount; i++) {
			cin >> size;
			panelHeight[i] = size;
		}

		//result[cycle] = bruteForce(panelHeight);
		result[cycle] = solve(0, panelCount - 1);

	}

	for (int i = 0; i < testCase; i++) {
		cout << result[i] << endl;
	}

	return 0;
}

/*
input
3
7
7 1 5 9 6 7 3
7 
1 4 4 4 4 1 1
4
1 8 2 2

output
20
16
8
*/
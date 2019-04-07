#include <iostream>
#include <vector>
#define MAX 31

using namespace std;

const int coverType[4][3][2] = {
	{{0, 0}, {1, 0}, {0, 1}},
	{{0, 0}, {0, 1}, {1, 1}},
	{{0, 0}, {1, 0}, {1, 1}},
	{{0, 0}, {1, 0}, {1, -1}}
};

bool set(vector<vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true;

	for (int i = 0; i < 3; i++) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];

		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size()) {
			ok = false;
		}else if ((board[ny][nx] += delta) > 1) {
			ok = false;
		}
	}

	return ok;
}

int cover(vector<vector<int>>& board) {
	int y = -1, x = -1;

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 0) {
				y = i;
				x = j;
				break;
			}
		}

		if (y != -1) {
			break;
		}
	}

	if (y == -1) {
		return 1;
	}

	int ret = 0;

	for (int type = 0; type < 4; type++) {
		if (set(board, y, x, type, 1)) {
			ret += cover(board);
		}

		set(board, y, x, type, -1);
	}

	return ret;
}

int main() {
	int testCase, result[MAX];
	cin >> testCase;

	for (int cycle = 0; cycle < testCase; cycle++) {
		int height, width, count = 0;
		cin >> height >> width;

		vector<vector<int>> board;
		for (int h = 0; h < height; h++)
		{
			vector<int> temp;
			char value;
			for (int w = 0; w < width; w++)
			{
				cin >> value;

				if ('.' == value) {
					temp.push_back(0);
					count++;
				}else{
					temp.push_back(1);
				}
			}
			board.push_back(temp);
		}

		if (count % 3 == 0) {
			result[cycle] = cover(board);
		}
		else {
			result[cycle] = 0;
		}	
	}

	for (int i = 0; i < testCase; i++) {
		cout << result[i] << endl;
	}

	return 0;
}
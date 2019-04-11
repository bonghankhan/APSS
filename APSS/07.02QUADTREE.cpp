#include <iostream>
#include <string>

using namespace std;

string reverse(string::iterator& it) {
	char head = *it;
	++it;

	if (head == 'b' || head == 'w') {
		return string(1, head);
	}

	string upperLeft  = reverse(it);
	string upperRight = reverse(it);
	string lowerLeft  = reverse(it);
	string lowerRight = reverse(it);

	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main() {
	int testCase;
	string result [50] = { "" };
	
	cin >> testCase;

	for (int cycle = 0; cycle < testCase; cycle++) {
		string compressionString;
		cin >> compressionString;

		string::iterator it = compressionString.begin();
		result[cycle] = reverse(it);

	}

	for (int i = 0; i < testCase; i++) {
		cout << result[i] << endl;
	}

	return 0;
}

/* ¿¹Á¦
4
w
xbwwb
xbwxwbbwb
xxwwwbxwxwbbbwwxxxwwbbbwwwwbb

https://stackoverrun.com/ko/q/1764930
http://blog.naver.com/PostView.nhn?blogId=hyoguri81&logNo=150086054529&viewDate=&currentPage=1&listtype=0
*/
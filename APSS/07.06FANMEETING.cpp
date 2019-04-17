#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

void normalize(vector<int>& num) {
	num.push_back(0);

	for (int i = 0; i < num.size() - 1; i++) {
		if (num[i] < 0) {
			int borrow  = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i]     += borrow * 10;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i]     %= 10;
		}
	}

	if (num.back() == 0) {
		num.pop_back();
	}	
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector <int> c(a.size() + b.size() + 1, 0);

	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}

	//normalize(c);

	return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
	a.resize(max(a.size(), b.size() + k));
	for (int i = 0; i < b.size(); i++) {
		a[i + k] += b[i];
	}

	//normalize(a);
}

void subFrom(vector<int>&a, const vector<int>& b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < b.size(); i++) {
		a[i] -= b[i];
	}

	//normalize(a);
}

vector<int> karatsuba(const vector<int>& a, const vector<int>& b) {
	int an = a.size(), bn = b.size();
	
	
	if (an < bn) {
		return karatsuba(b, a);
	}


	if (an == 0 || bn == 0) {
		return vector<int>();
	}

	if (an <= 2) {
		return multiply(a, b);
	}

	int half = an / 2;

	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());

	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);

	addTo(a0, a1, 0);
	addTo(b0, b1, 0);

	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);

	return ret;
}

int hugs(const string& members, const string& fans) {
	vector<int> A, B;

	for (char c : members) {
		A.push_back(c == 'M');
	}

	for (char c : fans) {
		B.push_back(c == 'M');
	}

	/*
		팬미팅 문제를 karatsuba 알고리즘을 이용하기 위해서는
		a * b = 1234 * 1234가 아닌 a * b = 1234 * 4321로 인수를 전달해야 한다.
	*/
	reverse(B.begin(), B.end());
	
	vector<int> C = karatsuba(A, B);
	int allHugs   = 0;
	// 멤버전체가 팬들과 만나야 되므로 결과의 중간을 취해서 카운트를 해야 한다.
	vector<int> sub(C.begin() + A.size() - 1, C.begin() + B.size()); 
	
	for (int i : sub) {
		if (!i) {
			allHugs++;
		}
	}

	/*int N = A.size(), M = B.size();
	for (int i = N - 1; i < M ; i++) {
		if (C[i] == 0) {
			allHugs++;
		}
	}*/

	return allHugs;
}

int main() {
	int testCase;
	vector<int> result;
	string members, fans;

	cin >> testCase;

	while (testCase--) {
		cin >> members;
		cin >> fans;

		result.push_back(hugs(members, fans));
	}

	for (int count : result) {
		cout << count << endl;
	}

	return 0;
}

/*
input:
8
FFFMMM
MMMFFF
FFFFF
FFFFFFFFFF
FFFFM
FFFFFMMMMF
MFMFMFFFMMMFMF
MMFFFFFMFFFMFFFFFFMFFFMFFFFMFMMFFFFFFF
MF
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMFMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMFMMMMMMMMMMMMMMMMMMMMMMF
MM
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFMFFFFFFFFF
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF

output:
1
6
2
2
2
127
0
11
*/
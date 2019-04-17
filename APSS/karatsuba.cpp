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
			int borrow = (abs(num[i]) + 9) / 10;
			num[i + 1] -= borrow;
			num[i]     += borrow * 10;
		}
		else {
			num[i + 1] += num[i] / 10;
			num[i]     %= 10;
		}
	}

	while (num.size() > 1 && num.back() == 0)
	{
		num.pop_back();
	}
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);

	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}

	normalize(c);

	return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
	a.resize(max(a.size(), b.size() + k));

	for (int i = 0; i < b.size(); i++) {
		a[i + k] += b[i];
	}

	normalize(a);
}

void subFrom(vector<int>&a, const vector<int>& b) {
	a.resize(max(a.size(), b.size()));
	for (int i = 0; i < b.size(); i++) {
		a[i] -= b[i];
	}

	normalize(a);
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

	/*
		(a0 + a1) * (b0 + b1) =  a1 * b1                + (a1 * b0 + a0 * b1)             + a0 * b0
		    a     *     b     = (a1 * b1) * (10 ^ 256)  + (a1 * b0 + a0 * b1) *(10 ^ 128) + a0 * b0
			                  = z2                      + z1                              + z0
			               z1 = (a0 + a1) * (b0 + b1) - z1 - z2
	*/
	vector<int> a0(a.begin(), a.begin() + half);
	vector<int> a1(a.begin() + half, a.end());

	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

	vector<int> z2 = karatsuba(a1, b1);
	vector<int> z0 = karatsuba(a0, b0);

	//z1 = (a0 + a1) * (b0 + b1) - z1 - z2
	addTo(a0, a1, 0);
	addTo(b0, b1, 0);

	vector<int> z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	//a     *     b     = (a1 * b1) * (10 ^ 256)  + (a1 * b0 + a0 * b1) *(10 ^ 128) + a0 * b0
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);

	return ret;
}


int main() {
	vector<int> result, A, B;
	string first, second;

	cin >> first >> second;

	for (char c : first) {
		A.push_back(c - '0');
	}

	for (char c : second) {
		B.push_back(c - '0');
	}

	//123456789 -> 987654321
	reverse(A.begin(), A.end());
	reverse(B.begin(), B.end());

	result = karatsuba(A, B);
	reverse(result.begin(), result.end());

	cout << '\n';

	for (int value : result) {
		cout << value;
	}

	return 0;
}

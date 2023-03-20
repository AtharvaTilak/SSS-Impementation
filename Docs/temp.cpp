#include <iostream>
#include <sstream>
#include "InfInt.h"

using namespace std;

class User {
private:
	string name;
	vector<InfInt> shakey;
public:
	void setdata(int i, string n, vector<InfInt> s) {
		if (i == 1) {
			cout << "Enter " << i << "st name: ";
		}
		else if (i == 2) {
			cout << "Enter " << i << "nd name: ";
		}
		else if (i == 3) {
			cout << "Enter " << i << "rd name: ";
		}
		else {
			cout << "Enter " << i << "th name: ";
		}
		cin >> n;
		this->name = n;
		this->shakey = s;
	}

	void getdata() {
		cout << name << " -> ";
		cout << "(" << shakey.at(0) << ", " << shakey.at(1) << ")" << endl;
	}

	void setshakey(InfInt t) {
		shakey.push_back(t);
	}

};

class SSS {
private:
	string seckey;
	InfInt enc;
	InfInt tshare;
	InfInt rshare;
	InfInt x = 1;
	stringstream ss;
	User user[10];
public:
	void setseckey(string t) {
		seckey = t;
	}
	InfInt getseckey() {
		return seckey;
	}
	void settshare(InfInt t) {
		tshare = t;
	}
	InfInt gettshare() {
		return tshare;
	}
	void setrshare(InfInt t) {
		rshare = t;
	}
	InfInt getrshare() {
		return rshare;
	}
	
	InfInt encode(string m) {
		string e;
		for (int i = 0; i < m.length(); i++) {
			char c = m[i];
			string a = to_string(int(c));
			e += a;
		}
		enc = e;
		return enc;
	}

	string decode(InfInt t) {
		int i = 0;
		int a = 3, b = 2;
		string result, finalresult;
		string decstr = t.toString();
		while (i != decstr.length()) {
			if (decstr[i] == '1') {
				string temp;
				int num = 0;
				while (a) {
					temp = temp + decstr[i];
					a--;
					i++;
				}
				stringstream ss;
				ss << temp;
				ss >> num;
				result = char(num);
			}
			else {
				string temp;
				int num = 0;
				while (b) {
					temp = temp + decstr[i];
					//cout << "temp: " << temp << ", decsrt[i]: " << decstr[i] << ", b: " << b << ", i: " << i << endl;
					b--;
					i++;
				}
				stringstream ss;
				ss << temp;
				ss >> num;
				//cout << "num: " << num << ", i: " << i << endl;
				result = char(num);
			}
			if (a == 0 || b == 0) {
				a = 3;
				b = 2;
			}
			finalresult += result;
		}
		return finalresult;
	}

	void genshakey(InfInt t, InfInt r) {
		cout << "Enter names of shared key holders:" << endl;
		InfInt b = 15;
		//InfInt b = InfInt::randomInfIntInRange(1000, 1500);
		string t1;
		if (r == 2) {
			cout << "Encrypting plain text....." << endl;
			for (int i = 0; i < t.toInt(); i++) {
				InfInt y = encode(seckey) + (b * x);
				vector<InfInt> v;
				v.push_back(x);
				v.push_back(y);
				user[i].setdata(i+1, t1, v);
				x++;
			}
		}
	}

	void verify(vector<InfInt> v1, vector<InfInt> v2) {
		string t;
		InfInt x1 = v1.front(), x2 = v2.front(), y1 = v1.back();
		InfInt y2 = v2.back();
		InfInt fx = ((y1 * (-x2)) / (x1 - x2)) + ((y2 * (-x1)) / (x2 - x1));
		ss << decode(fx);
		ss >> t;
		if (seckey == t) {
			cout << "Access granted, Vault is Open." << endl;
		}
		else {
			cout << "Shared key entered are incorrect. Try Again" << endl;
		}
	}

	void show() {
		for (int i = 0; i < tshare.toInt(); i++) {
			user[i].getdata();
		}
	}
};



int main() {
	SSS sss;
	string t;
	InfInt t1, t2;
	InfInt u1, u2;
	vector<InfInt> v1, v2;
	cout << "Enter secret key: ";
	cin >> t;
	sss.setseckey(t);
	cout << "Enter total number of shares to be generated: ";
	cin >> t1;
	sss.settshare(t1);
	cout << "Enter minimum number of shares required to unlock: ";
	cin >> t1;
	sss.setrshare(t1);
	sss.genshakey(sss.gettshare(), sss.getrshare());
	cout << "Secret key is secured, shared keys have been created" << endl;
	sss.show();
	cout << "To unlock enter any 2 shared keys. If your shared key is (a, b)," << endl;
	cout << "Enter 'a b'." << endl;
	cout << "First Key: ";
	cin >> u1 >> u2;
	v1.push_back(u1);
	v1.push_back(u2);
	cout << "Second Key: ";
	cin >> u1 >> u2;
	v2.push_back(u1);
	v2.push_back(u2);
	sss.verify(v1, v2);
}
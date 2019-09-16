#include <iostream>
#include <string>

using namespace std;

const string HEADER = "___________";

int main() {

	string currentCodedChar;
	string message = "";

	getline(cin, currentCodedChar);
	getline(cin, currentCodedChar);

	while (currentCodedChar != HEADER) {

		char currentChar = 0;
		int power = 1;

		for (int i = 0; i < 9; ++i) {

			if (i != 3) {

				if (currentCodedChar[9 - i] == 'o')
					currentChar += power;

				power *= 2;

			}

		}

		message += currentChar;

		getline(cin, currentCodedChar);

	}

	cout << message;

	return 0;

}

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main() {

	int randomNumber, guessNumber, guessCount = 0;

	srand(time(0));

	randomNumber = rand() % 100 + 1;

	cout << "Please enter the your guess number between 1 and 100: ";

	while (true) {

		cin >> guessNumber;

		if (guessNumber < 1 || guessNumber > 100) {

			cout << "Wrong number entered. Please enter between 1 and 100!";
			continue;

		}
		guessCount++;

		if (guessNumber == randomNumber) {

			cout << "Entered right number. Congralulations!" << "\nYour guess count is: " << guessCount;
			break;

		}
		else {

			if (guessNumber < randomNumber) {
				cout << "You entered smaller number!" << endl;
				continue;
			}
			if (guessNumber > randomNumber) {
				cout << "You entered bigger number!" << endl;
				continue;
			}

		}
	}

}

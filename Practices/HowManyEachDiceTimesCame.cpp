#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main() {

	int dice, numbers[7] = { 0,0,0,0,0,0,0 };

	srand(time(0));

	cout << "How many did each dice come out ?" << endl;

	for (int i = 1; i <= 100; i++) {

		dice = rand() % 6 + 1;

		numbers[dice]++;

	}
	for (int j = 1; j < 7; j++) {

		cout << j << ". " << numbers[j] << " times." << endl;

	}

	return 0;
}

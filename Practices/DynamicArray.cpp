#include <iostream>

using namespace std;

int main() {

	int sizeOfArray;
	cout << "Enter the size of array: ";
	cin >> sizeOfArray;
	int* array = new int[sizeOfArray];

	for (int i = 0; i < sizeOfArray; i++) {

		cout << i + 1 << ". = ";
		cin >> array[i];

	}

	for (int i = 0; i < sizeOfArray; i++) {
		cout << *(array + i) << " ";
	}

	delete[]array;
	array = NULL;

	return 0;
}

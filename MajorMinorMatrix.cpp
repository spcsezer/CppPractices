#include <iostream>

using namespace std;

int main() {

	int i,j, matrix_size;

	cout << "Please enter the square matrix size: ";
	cin >> matrix_size;

	int matrix[matrix_size][matrix_size];

	for (i = 0; i < matrix_size; i++) {

		for (j = 0; j < matrix_size; j++) {

			matrix[i][j] = 0;

		}

	}

	for (i = 0; i < matrix_size; i++) {

		for (j = 0; j < matrix_size; j++) {

			matrix[i][i] = 1;
			matrix[i][matrix_size - i - 1] = 1;

		}

	}

	for (i = 0; i < matrix_size; i++) {

		for (j = 0; j < matrix_size; j++) {

			cout << matrix[i][j] << "  ";

		}
		cout << endl;

	}

	return 0;
}

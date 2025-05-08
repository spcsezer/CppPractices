#include <iostream>

using namespace std;

int main() {

	float subject_number, subject_credit, sumofgrade = 0.00,  sumofgrades = 0.00, sumofcredits = 0.00, cgpa = 0.00;
	string subject_grade;

	cout << "Welcome to the CGPA Calculator\nA+ is 4.00\nA is 3.75\nA- is 3.50\nB+ is 3.25\nB is 3.00\nB- is 2.75\nC+ is 2.50\nC- is 2.25\nD is 2.00\nF is 0.00" << endl;

	cout << "How many subject do you have: ";
	cin >> subject_number;

	for (int i = 1; i <= subject_number; i++) {

		cout << "What is your " << i << "." << " subject grade (A+, A, ... etc.): ";
		cin >> subject_grade;

		cout << "What is your " << i << "." << " subject credit: ";
		cin >> subject_credit;

		if (subject_grade != "A+" && subject_grade != "A" && subject_grade != "A-"
			&& subject_grade != "B+" && subject_grade != "B" && subject_grade != "B-"
			&& subject_grade != "C+" && subject_grade != "C-" && subject_grade != "D"
			&& subject_grade != "F") {

			cout << "Please write valid subject grade!";
			break;

		}

		if (subject_grade == "A+") {
			sumofgrade = 4.00 * subject_credit;
		}
		else if (subject_grade == "A") {
			sumofgrade = 3.75 * subject_credit;
		}
		else if (subject_grade == "A-") {
			sumofgrade = 3.50 * subject_credit;
		}
		else if (subject_grade == "B+") {
			sumofgrade = 3.25 * subject_credit;
		}
		else if (subject_grade == "B") {
			sumofgrade = 3.00 * subject_credit;
		}
		else if (subject_grade == "B-") {
			sumofgrade = 2.75 * subject_credit;
		}
		else if (subject_grade == "C+") {
			sumofgrade = 2.50 * subject_credit;
		}
		else if (subject_grade == "C-") {
			sumofgrade = 2.25 * subject_credit;
		}
		else if (subject_grade == "D") {
			sumofgrade = 2.00 * subject_credit;
		}
		else if (subject_grade == "F") {
			sumofgrade = 0.00 * subject_credit;
		}

		sumofgrades += sumofgrade;
		sumofcredits += subject_credit;

	}

	cgpa = sumofgrades / sumofcredits;

	cout << "Your CGPA score is: " << cgpa;

	return 0;
}

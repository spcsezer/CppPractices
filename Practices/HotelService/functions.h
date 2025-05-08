#include "classes.h"



Hotel::Hotel() {

	type1 = 10, type2 = 10;

	entry_page();

}

void Hotel::entry_page() {

	actions entry_actions;

	while (true) {
		cout << "-----Welcome to the spcBooking-----\n\n";
		cout << "Write 1 for the login\nIf you don't have any account then write 2 for the register\nWrite 3 for the admin panel\nWrite 0 for the exit\n\n\n\n\n";
		cin >> entry_actions.button;

		switch (entry_actions.button)
		{
		case 1:
			login_page(); break;
		case 2:
			register_page(); break;
		case 3:
			admin_panel_entry(); break;
		case 0:
			break;
		default:
			cout << "Please write 1, 2, 3 or 0\n\n\n\n\n";
			break;
		}
		break;
	}

}

void Hotel::login_page() {

	actions login_actions;

	while (true) {
		cout << "-----LOGIN PAGE-----\n\n(Write -1 to username field for the back to the entry page)\n\n\n";
		cout << "Username: ";
		cin >> login_actions.username;
		if (login_actions.username == "-1") {
			entry_page();
			break;
		}
		else {
			cout << "Password: ";
			cin >> login_actions.password;

			for (login_actions.index = 0; login_actions.index < 100; login_actions.index++) {
				if (id_check[login_actions.index] == 0) {
					continue;
				}
				if (login_actions.username == *customer_username[login_actions.index] && login_actions.password == *customer_password[login_actions.index]) {
					cout << "\nSuccessfully logged in!\n\n";
					global_index = login_actions.index;
					main_lobby();
					break;
				}
			}
			cout << "\nUsername or password was incorrect!\n\n\n";
			break;
		}
	}
}

void Hotel::register_page() {

	actions register_actions;

	while (true) {
		cout << "-----REGISTER PAGE-----\n\n(Write -1 to username field for the back to the entry page)\n\n\n";
		cout << "Username: ";
		cin >> register_actions.username;
		if (register_actions.username == "-1") {
			entry_page();
			break;
		}
		else {
			cout << "Name: ";
			cin >> register_actions.name;
			cout << "Surname: ";
			cin >> register_actions.surname;
			cout << "Password: ";
			cin >> register_actions.password;
			cout << "Confirmation password: ";
			cin >> register_actions.confirmation_password;

			if (register_actions.password == register_actions.confirmation_password) {
				for (register_actions.index = 0; register_actions.index < 100; register_actions.index++) {
					if (id_check[register_actions.index] == 0) {
						customer_username[register_actions.index] = new string;
						*customer_username[register_actions.index] = register_actions.username;
						customer_name[register_actions.index] = new string;
						*customer_name[register_actions.index] = register_actions.name;
						customer_surname[register_actions.index] = new string;
						*customer_surname[register_actions.index] = register_actions.surname;
						customer_password[register_actions.index] = new string;
						*customer_password[register_actions.index] = register_actions.password;

						id_check[register_actions.index] = 1;

						room[register_actions.index] = new int;
						*room[register_actions.index] = 0;
						ttype1[register_actions.index] = new int;
						*ttype1[register_actions.index] = 0;
						ttype2[register_actions.index] = new int;
						*ttype2[register_actions.index] = 0;

						user_count++;

						cout << "\nSuccessfully registered!\n\n\n";
						login_page();
						break;
					}
				}
			}
			else {
				cout << "Password and confirmation password didn't match!\n\n\n";
				continue;
			}
		}
	}
}

void Hotel::main_lobby() {

	actions main_actions;

	cout << "-----MAIN LOBBY PAGE-----\n\n\n";
	cout << "Hello mr/mrs " << *customer_name[global_index] << ".\nYou have " << *room[global_index] << " rooms and you have " << *ttype1[global_index] << " rooms with one bed and " << *ttype2[global_index] << " rooms with two bed.\n\n";
	cout << "Write 1 for rent room\nWrite 2 for check-out\nWrite 3 for delete this account\nWrite 4 for back to the entry page\n\n\n";
	cin >> main_actions.button;

	switch (main_actions.button)
	{
	case 1:
		rent_room(); break;
	case 2:
		check_out(); break;
	case 3:
		delete_account(); break;
	case 4:
		entry_page(); break;
	default:
		cout << "Please write 1, 2 or 3\n\n\n\n\n";
		main_lobby();
		break;
	}
}

void Hotel::rent_room() {

	actions rent_actions;
	int type1_count, type2_count, total_type1_cost, total_type2_cost;

	cout << "-----RETING ROOM PAGE-----\n\n(Write 0 to room field for the back to the main page)\n\n\n";
	cout << "Type 1 rooms: rooms with one bed 100 dollars each AND Type 2 rooms: rooms with two bed 200 dollars each\n\n";
	cout << "Available type 1 rooms: " << type1 << "\nAvailable type 2 rooms: " << type2 << "\n\n";
	cout << "How many you want type 1 room: ";
	cin >> rent_actions.button;
	if (rent_actions.button < 0) {
		cout << "Type positive numbers!!!\n";
		rent_room();
	}
	if (rent_actions.button > type1) {
		cout << "Too many type 1 rooms typed!!!\n";
		rent_room();
	}
	if (rent_actions.button != 0) {
		type1_count = rent_actions.button;
		total_type1_cost = type1_count * type1_cost;
	}
	else {
		main_lobby();
	}
	cout << "How many you want type 2 room: ";
	cin >> rent_actions.button;
	if (rent_actions.button < 0) {
		cout << "Type positive numbers!!!\n";
		rent_room();
	}
	if (rent_actions.button > type2) {
		cout << "Too many type 2 rooms typed!!!\n";
		rent_room();
	}
	if (rent_actions.button != 0) {
		type2_count = rent_actions.button;
		total_type2_cost = type2_count * type2_cost;
	}
	*room[global_index] = type1_count + type2_count;
	*ttype1[global_index] = type1_count;
	*ttype2[global_index] = type2_count;

	type1 -= type1_count;
	type2 -= type2_count;

	profit = total_type1_cost + total_type2_cost;
	total_profit += profit;
	customer_count++;
	cout << "Successfully bought rooms! and they cost " << profit << "\n\n";
	main_lobby();

}

void Hotel::check_out() {

	actions checkout_actions;

	cout << "-----CHECK-OUT PAGE-----\n\n\n";
	cout << "Do you wanna chek-out the " << *room[global_index] << " rooms\n\n";
	cout << "Write 1 for the check-out\nWrite 2 for the cancel and back to the main page\n";
	cin >> checkout_actions.button;

	switch (checkout_actions.button)
	{
	case 1:
		*room[global_index] = 0;
		type1 += *ttype1[global_index];
		type2 += *ttype2[global_index];
		*ttype1[global_index] = 0;
		*ttype2[global_index] = 0;
		customer_count--;
		cout << "Successfully checked-out!\n\n";
		main_lobby(); break;
	case 2:
		main_lobby(); break;
	default:
		cout << "Please write 1 or 2\n\n\n\n\n";
		check_out();
		break;
	}

}

void Hotel::delete_account() {

	actions delete_actions;

	cout << "-----DELETING ACCOUNT PAGE-----\n\n\n";
	cout << "Write 1 if you sure for deleting your account or write 0 for back to the main page\n";
	cin >> delete_actions.button;

	if (*room[global_index] == 0) {

		switch (delete_actions.button)
		{
		case 1:
			delete customer_username[global_index];
			delete customer_name[global_index];
			delete customer_surname[global_index];
			delete customer_password[global_index];
			id_check[global_index] = 0;
			delete room[global_index];
			delete ttype1[global_index];
			delete ttype2[global_index];
			
			user_count--;
			cout << "Successfully deleted your account!\n\n";
			entry_page(); break;
		case 0:
			main_lobby(); break;
		default:
			cout << "Please write 1 or 0\n\n\n\n\n";
			delete_account();
			break;
		}
	}
	else {
		cout << "You still have rooms. You can't delete account until check-out!!!\n\n";
		main_lobby();
	}

}

void Hotel::admin_panel_entry() {
	actions admin_panel_entry;
	cout << "What is the admin code: ";
	cin >> admin_panel_entry.button;
	if (admin_panel_entry.button == 12345) {
		admin_panel();
	}
	else {
		cout << "Wrong admin code!!!\n\n";
		entry_page();
	}
}

void Hotel::admin_panel() {

	actions admin_panel;

	cout << "-----ADMIN PANEL PAGE-----\n\n\n";
	cout << "---USERS---\n\n";
	for (int i = 0; i < 100; i++) {
		if (id_check[i] == 0) {
			continue;
		}
		if (id_check[i] == 1) {
			cout << *customer_name[i] << " " << *customer_surname[i] << " - " << *customer_username[i] << "\n\n";
		}
	}
	cout << "Available rooms: " << type1 + type2 << "\n";
	cout << "Type 1: " << type1 << " AND type 2: " << type2 << "\n\n";

	cout << "Write any number for the back to the entry page: ";
	cin >> admin_panel.button;
	entry_page();
}

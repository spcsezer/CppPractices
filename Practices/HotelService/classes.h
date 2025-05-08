#include "libraries.h"

struct actions {
	int button;
	string username;
	string password;
	string confirmation_password;
	string name;
	string surname;
	int index;
};

class Hotel {

	string* customer_name[100], * customer_surname[100], * customer_username[100], * customer_password[100];
	int* ttype1[100], * ttype2[100], * room[100];
	int type1, type2;
	int type1_cost = 100;
	int type2_cost = 200;
	int profit = 0;
	int total_profit = 0;
	bool id_check[100] = {0};
	int customer_count = 0;
	int user_count = 0;
	int global_index = 0;
	int type1_count = 0;
	int type2_count = 0;

public:
	Hotel();
	void entry_page();
	void login_page();
	void register_page();
	void admin_panel_entry();
	void admin_panel();
	void main_lobby();
	void rent_room();
	void check_out();
	void delete_account();

};

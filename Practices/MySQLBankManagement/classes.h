#include "libs.h"

using namespace std;

struct vmanagement {

	int button;
	string username;
	string name;
	string surname;
	string password;
	string confirm_password;
	int sending_money;
	string sending_iban;

};

class Management {

	const string sql_server = "tcp://127.0.0.1:3306";
	const string sql_username = "root";
	const string sql_password = "";
	sql::Driver* sql_driver;
	sql::Connection* connection;

public:

	Management();
	void entry();
	void create();
	void login();
	void man_login();
	void manager_page();
	void search(char rchars[], string username);
	void db_create(string username, string name, string surname, string password, sql::Connection* connection);
	void db_login(string username, string password, sql::Connection* connection);
	void main_page(string username, sql::Connection* connection);
	void sending_money(string username, sql::Connection* connection, int money);

};

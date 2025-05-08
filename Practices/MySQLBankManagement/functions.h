#include "classes.h"
char rchars[] = { '+', '-', '\\', '/', ':', '*', '?', '"', '<', '>', '|', '(', ')', '{', '}', '\'', '%', ';', '^', '$', '&', '~', '`', '€' };

string GenerateIBAN();

Management::Management() {

	sql_driver = sql::mysql::get_mysql_driver_instance();
	connection = sql_driver->connect(sql_server, sql_username, sql_password);
	connection->setSchema("bank_management");
	entry();

}

void Management::entry() {
	vmanagement ventry;
	cout << "##################################\n";
	cout << "###### WELCOME TO THE BANK #######\n";
	cout << "##################################\n";
	cout << "##################################\n";
	cout << "##################################\n";
	cout << "#### 1. Create a bank account ####\n";
	cout << "## 2. Login to the bank account ##\n";
	cout << "###### 3. Bank manager login #####\n";
	cout << "############ 4. Exit #############\n";
	cout << "##################################\n";
	cin >> ventry.button;

	switch (ventry.button)
	{
	case 1:
		create(); break;
	case 2:
		login(); break;
	case 3:
		man_login(); break;
	case 4:
		exit(0); break;
	default:
		cerr << "!!TYPED WRONG NUMBER!!\n\n";
		entry();
		break;
	}

}

void Management::login() {

	vmanagement vlogin;

	cout << "##################################\n";
	cout << "############# LOGIN ##############\n";
	cout << "##################################\n";
	cout << "##type -1 for back to entry page##\n";
	cout << "############# Username: ";
	cin >> vlogin.username;
	if (vlogin.username == "-1") {
		entry();
	}
	if (vlogin.username.length() > 16) {
		cerr << "!!Maximum username character is 16!!\n\n";
		create();
	}
	else if (vlogin.username.length() <= 0) {

		cerr << "!!You didn't type username!!\n\n";
		create();
	}
	search(rchars, vlogin.username);

	cout << "############# Password: ";
	cin >> vlogin.password;
	if (vlogin.password == "-1") {
		entry();
	}
	if (vlogin.password.length() > 16) {
		cerr << "!!Maximum password character is 16!!\n\n";
		create();
	}
	else if (vlogin.password.length() <= 0) {

		cerr << "!!You didn't type password!!\n\n";
		create();
	}
	else if (vlogin.password.length() <= 5) {

		cerr << "!!Minimum password length is 6!!\n\n";
		create();
	}
	search(rchars, vlogin.password);

	db_login(vlogin.username, vlogin.password, connection);

	cout << "##################################\n";
	cout << "######Successfully logged in######\n";
	cout << "##################################\n\n";
	main_page(vlogin.username, connection);
}

void Management::create(){

	vmanagement vcreate;

	cout << "##################################\n";
	cout << "############# CREATE #############\n";
	cout << "##################################\n";
	cout << "##type -1 for back to entry page##\n";
	cout << "##################################\n";
	cout << "############# Username: ";
	cin >> vcreate.username;
	if (vcreate.username == "-1") {
		entry();
	}
	if (vcreate.username.length() > 16) {
		cerr << "!!Maximum username character is 16!!\n\n";
		create();
	}
	else if (vcreate.username.length() <= 0) {

		cerr << "!!You didn't type username!!\n\n";
		create();
	}
	search(rchars, vcreate.username);

	cout << "############# Name: ";
	cin >> vcreate.name;
	if (vcreate.name == "-1") {
		entry();
	}
	if (vcreate.name.length() > 32) {
		cerr << "!!Maximum name character is 32!!\n\n";
		create();
	}
	else if (vcreate.name.length() <= 0) {

		cerr << "!!You didn't type name!!\n\n";
		create();
	}

	cout << "############# Surname: ";
	cin >> vcreate.surname;
	if (vcreate.surname == "-1") {
		entry();
	}
	if (vcreate.surname.length() > 32) {
		cerr << "!!Maximum surname character is 32!!\n\n";
		create();
	}
	else if (vcreate.surname.length() <= 0) {

		cerr << "!!You didn't type surname!!\n\n";
		create();
	}

	cout << "############# Password: ";
	cin >> vcreate.password;
	if (vcreate.password == "-1") {
		entry();
	}
	if (vcreate.password.length() > 16) {
		cerr << "!!Maximum password character is 16!!\n\n";
		create();
	}
	else if (vcreate.password.length() <= 0) {

		cerr << "!!You didn't type password!!\n\n";
		create();
	}
	else if (vcreate.password.length() <= 5) {

		cerr << "!!Minimum password length is 6!!\n\n";
		create();
	}
	search(rchars, vcreate.password);

	cout << "##### Confirm Password: ";
	cin >> vcreate.confirm_password;
	if (vcreate.confirm_password != vcreate.password) {
		cerr << "!!Confirm password and password didn't match!!\n\n";
		create();
	}

	db_create(vcreate.username, vcreate.name, vcreate.surname, vcreate.password, connection);

	cout << "##################################\n";
	cout << "#Successfully created an account##\n";
	cout << "##################################\n\n";
	entry();
}

void Management::man_login() {

	vmanagement manlogin;
	cout << "Manager Password (-1 for back to entry page): ";
	cin >> manlogin.button;
	if (manlogin.button == 12345) {
		manager_page();
	}
	else if (manlogin.button == -1) {
		entry();
	}
	else {
		cerr << "!!WRONG PASSWORD!!\n\n";
		man_login();
	}
}

void Management::manager_page() {

	vmanagement vmanager;

	cout << "##################################\n";
	cout << "########## MANAGER PAGE ##########\n";
	cout << "##################################\n";
	cout << "##type -1 for back to entry page##\n";
	cout << "##################################\n";
	cout << "########## 1. User List ##########\n";
	cout << "######## 2. Transfer Logs ########\n";
	cout << "##################################\n";
	cin >> vmanager.button;

	switch (vmanager.button)
	{
	case 1: {
		sql::Statement* usernameStatement = connection->createStatement();
		sql::ResultSet* usernameResult = usernameStatement->executeQuery("SELECT username, money FROM users");
		int num = 1;
		while (usernameResult->next()) {
			cout << num << ": " << usernameResult->getString("username") << "| Money: "<< usernameResult->getInt("money") << endl;
			cout << "--------------------------------------------------" << endl;
			num++;
		}
		delete usernameStatement;
		delete usernameResult;
		manager_page();
		break;
	}
	case 2: {
		sql::Statement* logStatement = connection->createStatement();
		sql::ResultSet* logResult = logStatement->executeQuery("SELECT sender_username, receiver_username, transfered_money, send_date FROM logs");
		int num2 = 1;
		while (logResult->next()) {
			cout << num2 << ". Sender Username: " << logResult->getString("sender_username") << "| Receiver Username: " << logResult->getString("receiver_username") << "| Transfered Money: " << logResult->getInt("transfered_money") << "| Send Date: " << logResult->getString("send_date") << endl;
			cout << "--------------------------------------------------" << endl;
			num2++;
		}
		delete logStatement;
		delete logResult;
		manager_page();
		break;
	}
	case -1:
		entry();
		break;
	default:
		cerr << "!!TYPED WRONG NUMBER!!\n\n";
		manager_page();
		break;
	}
}

void Management::search(char rchars[], string username) {

	int rchars_size = sizeof(rchars) / sizeof(rchars[0]);
	int lusername = username.length();

	for (int i = 0; i < lusername; i++) {
		if (username[i] == ' ') {
			cerr << "!!You can't leave space!!\n\n";
			create();
		}
		for (int j = 0; j < rchars_size; j++) {
			if (username[i] == rchars[j]) {
				cerr << "!!You can't type restricted characters!!\n\n";
				create();
			}
		}
	}

}

void Management::db_login(string username, string password, sql::Connection* connection) {

	sql::PreparedStatement* printStatement = connection->prepareStatement("SELECT password FROM users WHERE username = ?");
	printStatement->setString(1, username);
	sql::ResultSet* result = printStatement->executeQuery();

	if (result->next()) {

		string storedPassword = result->getString("password");

		if (storedPassword != password) {
			cerr << "!!Uncorrect password!!\n\n";
			entry();
		}
	}
	else {
		cerr << "!!Username not found!!\n\n";
		entry();
	}

	delete printStatement;
	delete result;
}

void Management::db_create(string username, string name, string surname, string password, sql::Connection* connection) {

	int default_money = 100000;

	sql::PreparedStatement* checkStatement = connection->prepareStatement("SELECT COUNT(*) FROM users WHERE username = ?");
	checkStatement->setString(1, username);
	sql::ResultSet* result = checkStatement->executeQuery();

	int count = 0;
	if (result->next()) {
		count = result->getInt(1);
	}
	delete checkStatement;
	delete result;

	if (count > 0) {
		cerr << username << " already using. Please type another username!!\n\n";
		create();
	}

	string iban = GenerateIBAN();
	sql::PreparedStatement* checkIBAN = connection->prepareStatement("SELECT COUNT(*) FROM users WHERE iban = ?");
	checkIBAN->setString(1, iban);
	sql::ResultSet* ibanResult = checkIBAN->executeQuery();
	while (ibanResult->next() && ibanResult->getInt(1) > 0) {
		iban = GenerateIBAN();
	}
	delete checkIBAN;
	delete ibanResult;

	sql::PreparedStatement* printStatement = connection->prepareStatement("INSERT INTO users (username, name, surname, password, money, iban) VALUES (?, ?, ?, ?, ?, ?)");
	printStatement->setString(1, username);
	printStatement->setString(2, name);
	printStatement->setString(3, surname);
	printStatement->setString(4, password);
	printStatement->setInt(5, default_money);
	printStatement->setString(6, iban);
	printStatement->executeUpdate();
	delete printStatement;

}

void Management::main_page(string username, sql::Connection* connection) {
	string name, surname, iban;
	vmanagement vmain;
	int money;

	sql::PreparedStatement* printInfo = connection->prepareStatement("SELECT name, surname, money, iban FROM users WHERE username = ?");
	printInfo->setString(1, username);
	sql::ResultSet* resultInfo = printInfo->executeQuery();
	if (resultInfo->next()) {
		name = resultInfo->getString("name");
		surname = resultInfo->getString("surname");
		iban = resultInfo->getString("iban");
		money = resultInfo->getInt("money");
	}

	cout << "##################################\n";
	cout << "############## MAIN ##############\n";
	cout << "##################################\n";
	cout << "##type -1 for back to entry page##\n";
	cout << "##################################\n";
	cout << "##################################\n";
	cout << "#Welcome to the bank, " << name << " " << surname << endl;
	cout << "##################################\n";
	cout << "#IBAN: " << iban << endl;
	cout << "##################################\n";
	cout << "#Money: " << money << endl;
	cout << "##################################\n";
	cout << "##################################\n";
	cout << "########## 1. Send money #########\n";
	cout << "############# 2. Exit ############\n";
	cout << "##################################\n";
	cin >> vmain.button;

	switch (vmain.button)
	{
	case 1:
		
		sending_money(username, connection, money);

	case 2:
		entry(); break;
	default:
		cerr << "!!TYPED WRONG NUMBER!!\n\n";
		main_page(username, connection);
		break;
	}
}

void Management::sending_money(string username, sql::Connection* connection, int money) {

	vmanagement vsending;

	cout << "#How much you gonna send? ";
	cin >> vsending.sending_money;

	if (vsending.sending_money > money) {
		cerr << "!!YOU DON'T HAVE ENOUGH MONEY!!\n\n";
		main_page(username, connection);
	}

	if (vsending.sending_money <= 0) {
		cerr << "!!YOU ENTERED WRONG NUMBER!!\n\n";
		main_page(username, connection);
	}

	cout << "#What IBAN you gonna send? ";
	cin >> vsending.sending_iban;

	if (vsending.sending_iban.length() != 22) {
		cerr << "!!ENTERED WRONG IBAN!!";
		main_page(username, connection);
	}
	
	//update receiver
	sql::PreparedStatement* rmoneyStatement = connection->prepareStatement("SELECT money, username FROM users WHERE iban = ?");
	rmoneyStatement->setString(1, vsending.sending_iban);
	sql::ResultSet* rmoneyResult = rmoneyStatement->executeQuery();

	int rmoney;
	string rusername;
	if (rmoneyResult->next()) {
		rmoney = rmoneyResult->getInt("money");
		rusername = rmoneyResult->getString("username");
	}
	else {
		cerr << "!!THERE IS NO SUCH IBAN!!\n\n";
		main_page(username, connection);
	}
	delete rmoneyStatement;
	delete rmoneyResult;

	int total_money = rmoney + vsending.sending_money;
	sql::PreparedStatement* setrmoneyStatement = connection->prepareStatement("UPDATE users SET money = ? WHERE iban = ?");
	setrmoneyStatement->setInt(1, total_money);
	setrmoneyStatement->setString(2, vsending.sending_iban);
	setrmoneyStatement->executeUpdate();
	delete setrmoneyStatement;

	//update sender

	int remaining_money = money - vsending.sending_money;
	sql::PreparedStatement* printStatement = connection->prepareStatement("UPDATE users SET money = ? WHERE username = ?");
	printStatement->setInt(1, remaining_money);
	printStatement->setString(2, username);
	printStatement->executeUpdate();
	delete printStatement;
	cout << "##################################\n";
	cout << "#########SUCCESSFULLY SENT########\n";
	cout << "##################################\n\n";

	//save log

	time_t currentTime = time(0);
	char* tm = ctime(&currentTime);
	string cTime = tm;

	sql::PreparedStatement* saveLogStatement = connection->prepareStatement("INSERT INTO logs (sender_username, receiver_username, transfered_money, send_date) VALUES (?, ?, ?, ?)");
	saveLogStatement->setString(1, username);
	saveLogStatement->setString(2, rusername);
	saveLogStatement->setInt(3, vsending.sending_money);
	saveLogStatement->setString(4, cTime);
	saveLogStatement->executeUpdate();
	delete saveLogStatement;

	main_page(username, connection);
}

string GenerateIBAN() {

	ostringstream iban;

	iban << "TR";

	iban << setw(4) << setfill('0') << rand() % 10000;

	for (int i = 0; i < 16; i++) {
		iban << rand() % 10;
	}

	return iban.str();
}

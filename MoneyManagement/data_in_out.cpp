#include"data_in_out.h"
#include"account.h"
#include"ledger.h"
#include<mysql.h>
#include<iostream>
#include<vector>
#include<iterator>
#include<string>
#include<map>

void account_reclaim(MYSQL* conn) {
	if (mysql_query(conn, "SELECT id, name, holder, number, money FROM subaccount")) {     //查询数据
		std::cerr << "SELECT query failed. Error: " << mysql_error(conn) << std::endl;
	}
	MYSQL_RES* result = mysql_store_result(conn);
	if (result == NULL) {
		std::cerr << "mysql_store_result() failed. Error: " << mysql_error(conn) << std::endl;
	}
	MYSQL_ROW row;
	int id;
	std::string name;
	std::string holder;
	std::string number;
	double money;
	std::string delete_query;
	while ((row = mysql_fetch_row(result)) != NULL) {
		id = atoi(row[0]);
		name = row[1];
		holder = row[2];
		number = row[3];
		money = atof(row[4]);
		Account* ptr = new Account(name, holder, number, money);
		all_subaccount.push_back(ptr);
		delete_query = "DELETE FROM subaccount WHERE id = " + std::to_string(id);
		mysql_query(conn, delete_query.c_str());
	}
	std::cout << "账户载入完毕" << std::endl;
}

void account_storage(MYSQL* conn){
	std::vector<Account*>::iterator it = all_subaccount.begin();
	std::string insert_query;
	std::string name;
	std::string holder;
	std::string number;
	double money;
	while (it != all_subaccount.end()) {
		name = (*it)->get_name();
		holder = (*it)->get_holder();
		number = (*it)->get_number();
		money = (*it)->get_money();
		insert_query = "INSERT INTO subaccount(name, holder, number, money) VALUES('" + name + "', '" + holder + "', '" + number + "', " + std::to_string(money) + ")";
		mysql_query(conn, insert_query.c_str());
		delete (*it);
		it = all_subaccount.erase(it);       //更新迭代器，防止指针悬空
	}
	std::cout << "账户信息已保存" << std::endl;
}

void ledger_reclaim(MYSQL* conn) {
	if (mysql_query(conn, "SELECT id, date1, date2, transaction_partners, account, in_or_out, transaction_amount, sle_type, note  FROM book")) {     //查询数据
		std::cerr << "SELECT query failed. Error: " << mysql_error(conn) << std::endl;
	}
	MYSQL_RES* result = mysql_store_result(conn);
	MYSQL_ROW row;
	int date1, date2;
	int id, year, month, day, hour, minute, in_or_out;
	std::string transaction_partners, account, sle_type, note,delete_query;
	double transaction_amount;
	while ((row = mysql_fetch_row(result)) != NULL) {
		id = atoi(row[0]);
		date1 = atoi(row[1]);
		month = date1 % 100;
		year = (date1 - month) / 100;
		date2 = atoi(row[2]);
		minute = date2 % 100;
		hour = ((date2 - minute) / 100) % 100;
		day = (((date2 - minute) / 100) - hour) / 100;
		Date d(year, month, day, hour, minute);
		transaction_partners = row[3];
		account = row[4];
		in_or_out = atoi(row[5]);
		transaction_amount = atof(row[6]);
		sle_type = row[7];
		note = row[8];
		std::vector<Account*>::iterator it;
		it = find_if(all_subaccount.begin(), all_subaccount.end(), [account](Account* temp) {
			return account == temp->get_name();
			});
		Account* ptr = (*it);
		Ledger* ledger_ptr = new Ledger(d, transaction_partners, ptr, in_or_out, transaction_amount, sle_type, note);
		Book.push_back(ledger_ptr);
		delete_query = "DELETE FROM book WHERE id = " + std::to_string(id);
		mysql_query(conn, delete_query.c_str());
	}
	std::cout << "记账本载入完毕" << std::endl;
}

void ledger_storage(MYSQL* conn) {
	std::vector<Ledger*>::iterator it = Book.begin();
	int date1, date2;
	int in_or_out;
	std::string transaction_partners, account, sle_type, note, insert_query;
	double transaction_amount;
	while (it != Book.end()) {
		date1 = (*it)->date.code1();
		date2 = (*it)->date.code2();
		transaction_partners = (*it)->get_transaction_partners();
		account = (*it)->get_subaccount();
		in_or_out = (*it)->get_in_or_out();
		transaction_amount = (*it)->get_transaction_amount();
		sle_type = (*it)->get_sle_type();
		note = (*it)->get_note();
		insert_query = "INSERT INTO book(date1, date2, transaction_partners, account, in_or_out, transaction_amount, sle_type, note) VALUES(" + std::to_string(date1) + ", " + std::to_string(date2) 
		+ ", '"+transaction_partners + "', '" + account + "', " + std::to_string(in_or_out) + ", " + std::to_string(transaction_amount) + ", '" + sle_type + "', '" + note + "')";
		mysql_query(conn, insert_query.c_str());
		delete (*it);
		it = Book.erase(it);
	}
	std::cout << "记账本信息已保存" << std::endl;
}

void plan_reclaim(MYSQL* conn) {
	if (mysql_query(conn, "SELECT id, medicine, food, accomodation, transportation, entertainment, investment, social_connect, other, sum  FROM plan_collection")) {     //查询数据
		std::cerr << "SELECT query failed. Error: " << mysql_error(conn) << std::endl;
	}
	MYSQL_RES* result = mysql_store_result(conn);
	MYSQL_ROW row;
	int id;
	double sum;
	std::string delete_query;
	std::map<std::string, double> plan_out_type = {
		{"医疗", 0.0},{"食品", 0.0},{"住房", 0.0},
		{"交通", 0.0},{"娱乐", 0.0},{"投资", 0.0},
		{"社交", 0.0},{"其他", 0.0}
	};
	while ((row = mysql_fetch_row(result)) != NULL) {
		id = atoi(row[0]);
		plan_out_type["医疗"] = atof(row[1]);
		plan_out_type["食品"] = atof(row[2]);
		plan_out_type["住房"] = atof(row[3]);
		plan_out_type["交通"] = atof(row[4]);
		plan_out_type["娱乐"] = atof(row[5]);
		plan_out_type["投资"] = atof(row[6]);
		plan_out_type["社交"] = atof(row[7]);
		plan_out_type["其他"] = atof(row[8]);
		sum = atof(row[9]);
		Plan p(sum, plan_out_type);
		plan_collection.push_back(p);
		delete_query = "DELETE FROM plan_collection WHERE id = " + std::to_string(id);
		mysql_query(conn, delete_query.c_str());
	}
	std::cout << "消费规划载入完毕" << std::endl;
}

void plan_storage(MYSQL* conn) {
	std::vector<Plan>::iterator it = plan_collection.begin();
	std::string insert_query;
	double medicine, food, accomodation, transportation, entertainment, investment, social_connect, other, sum;
	while (it != plan_collection.end()) {
		sum = it->get_plan_out_sum();
		medicine = it->plan_out_type["医疗"];
		food = it->plan_out_type["食品"];
		accomodation = it->plan_out_type["住房"];
		transportation = it->plan_out_type["交通"];
		entertainment = it->plan_out_type["娱乐"];
		investment = it->plan_out_type["投资"];
		social_connect = it->plan_out_type["社交"];
		other = it->plan_out_type["其他"];
		insert_query = "INSERT INTO plan_collection(medicine, food, accomodation, transportation, entertainment, investment, social_connect, other, sum) VALUES(" 
			+ std::to_string(medicine) + ", " + std::to_string(food) + ", " + std::to_string(accomodation) + ", " + std::to_string(transportation) + ", " + std::to_string(entertainment) 
			+ ", " + std::to_string(investment) + ", " + std::to_string(social_connect) + ", " + std::to_string(other) + ", " + std::to_string(sum) + ")";
		mysql_query(conn, insert_query.c_str());
		++it;
	}
	std::cout << "消费规划已保存" << std::endl;
}
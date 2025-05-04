#include "Database.h"
#include <iostream>
#include <QMessageBox>


void createTable(sqlite3* db){
	char* errMsg{nullptr};
	const char* sql = "CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT NOT NULL, description TEXT, due_date TEXT, status TEXT NOT NULL);";
	int rc = sqlite3_exec(db,sql,nullptr,nullptr,&errMsg);
	if(rc != SQLITE_OK){
		std::cerr << "createTable->CREATE TABLE ERROR: " << errMsg << std::endl;
		QMessageBox::critical(nullptr,"ERROR",QString("CREATE TABLE ERROR\n%1").arg(errMsg));
		return;
	}
}



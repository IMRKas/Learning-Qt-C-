#include "Database.h"
#include <iostream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

void createTable(){
	QSqlQuery query;
	query.prepare("CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT NOT NULL, description TEXT, due_date TEXT, status TEXT NOT NULL);");
	if(!query.exec()){
		QMessageBox::critical(nullptr,"ERROR","createTable ERROR:\n" + query.lastError().text());
		return;
	}
}



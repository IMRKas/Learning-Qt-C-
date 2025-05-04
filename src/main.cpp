#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <sqlite3.h>
#include <iostream>
//#include "MainWindow.h"
#include "TaskForm.h"
#include "Database.h"


int main(int argc, char *argv[]){
	QApplication app(argc,argv);

	sqlite3* db;
	int rc = sqlite3_open("db/tasks.db", &db);
	if(rc != SQLITE_OK){
		std::cerr << "ERROR OPENING DATABASE: " << sqlite3_errmsg(db) << std::endl;
		QMessageBox::critical(nullptr, "ERROR", QString("ERROR OPENING DATABASE:\n%1").arg(sqlite3_errmsg(db)));
		return -1;
	}

	createTable(db);

	// MainWindow mainW(db);
	// mainW.show();

	TaskForm newForm;
	newForm.show();



	int appExec = app.exec();
	sqlite3_close(db);
	return appExec;
}

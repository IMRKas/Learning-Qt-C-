#include <QApplication>
#include <QDir>
#include <QSqlDatabase>
#include <QSqlError>
#include <QMessageBox>
#include <sqlite3.h>
#include <iostream>
//#include "MainWindow.h"
#include "TaskForm.h"
#include "Database.h"


int main(int argc, char *argv[]){
	QApplication app(argc,argv);
	QDir().mkpath("db");
	QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName("db/tasks.db");

	if(!db.open()){
		QMessageBox::critical(nullptr,"ERRO","Erro ao abrir banco de dados\n" + db.lastError().text());
			return -1;
	}

	createTable();

	// MainWindow mainW(db);
	// mainW.show();

	TaskForm newForm;
	newForm.show();



	return app.exec();
}

#include "MainWindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent){
	setWindowTitle("Gerenciado de Tarefas");

	// Buttons
	newTaskBtn = new QPushButton("Nova Tarefa", this);
	editTaskBtn = new QPushButton("Editar Tarefa", this);
	completeTaskBtn = new QPushButton("Completar Tarefa", this);
	deleteTaskBtn = new QPushButton("Excluir Tarefa", this);
	searchTaskLe = new QLineEdit(this);

	// Layouts 
	mainLayout = new QHBoxLayout(this);
	menuLayout = new QVBoxLayout;
	tableView = new QTableView;
	model = new QSqlQueryModel;


	// Setting Layouts
	menuLayout->addWidget(searchTaskLe);
	menuLayout->addWidget(newTaskBtn);
	menuLayout->addWidget(editTaskBtn);
	menuLayout->addWidget(completeTaskBtn);
	menuLayout->addWidget(deleteTaskBtn);
	mainLayout->addLayout(menuLayout, 3);
	mainLayout->addWidget(tableView, 7);
		

// ---------------------------------------------------------------------------------------- //

	// Connects
		// Delete Task
		connect(deleteTaskBtn, &QPushButton::clicked, this, &MainWindow::deleteTask);
		
		// New Task
		connect(newTaskBtn, &QPushButton::clicked, this, [=](){
				if(!newTaskForm){
					newTaskForm = new TaskForm();
					newTaskForm->show();
					
					// Free memory after closing taskForm window
					connect(newTaskForm, &QObject::destroyed, this, [this](){
							this->newTaskForm = nullptr;
							loadTasks();
					});
				}
		});

// ---------------------------------------------------------------------------------------- //
	// Aux settings
		// Table View
		tableView->setModel(model);


		// search bar
		searchTaskLe->setPlaceholderText("Buscar...");
	loadTasks();
}



void MainWindow::loadTasks(){

	model->setQuery("SELECT id, title, description, due_date, status FROM tasks;");
	model->setHeaderData(0,Qt::Horizontal,"ID");
	model->setHeaderData(1,Qt::Horizontal,"Título");
	model->setHeaderData(2,Qt::Horizontal,"Descrição");
	model->setHeaderData(3,Qt::Horizontal,"Data Limite");
	model->setHeaderData(4,Qt::Horizontal,"Status");

	tableView->resizeColumnsToContents();
}

void MainWindow::deleteTask(){
	QModelIndex selectedRow = tableView->currentIndex();
	if(!selectedRow.isValid()){
		QMessageBox::information(this, "Atenção", "Selecione uma tarefa para excluir.");
		return;
	}
	
	if(QMessageBox::question(this,"Excluir Tarefa", "Tem certeza que deseja excluir esta tarefa ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){

		// Getting the id of the selected row
		int taskID = model->data(model->index(selectedRow.row(),0)).toInt();

		QSqlQuery deleteRow;
		deleteRow.prepare("DELETE FROM tasks WHERE id = ?;");
		deleteRow.addBindValue(taskID);

		if(!deleteRow.exec()){
			QMessageBox::critical(this, "ERRO", "Erro ao excluir tarefa:\n" + deleteRow.lastError().text());
			return;
		} else {
			QMessageBox::information(this,"SUCESSO","Tarefa excluida com sucesso.");
			loadTasks();
		}
	}
}

#include "MainWindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent){
	setWindowTitle("Gerenciado de Tarefas");

	// Buttons
	newTask = new QPushButton("Nova Tarefa", this);
	editTask = new QPushButton("Editar Tarefa", this);
	completeTask = new QPushButton("Completar Tarefa", this);
	deleteTask = new QPushButton("Excluir Tarefa", this);
	searchTask = new QLineEdit(this);

	// Layouts 
	mainLayout = new QHBoxLayout(this);
	menuLayout = new QVBoxLayout;
	tableView = new QTableView;
	model = new QSqlQueryModel;


	// Setting Layouts
	menuLayout->addWidget(searchTask);
	menuLayout->addWidget(newTask);
	menuLayout->addWidget(editTask);
	menuLayout->addWidget(completeTask);
	menuLayout->addWidget(deleteTask);
	mainLayout->addLayout(menuLayout, 3);
	mainLayout->addWidget(tableView, 7);
		


	// Connects
		// New Task
		connect(newTask, &QPushButton::clicked, this, [=](){
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

	// Aux settings
		// Table View
		tableView->setModel(model);


		// search bar
		searchTask->setPlaceholderText("Buscar...");
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

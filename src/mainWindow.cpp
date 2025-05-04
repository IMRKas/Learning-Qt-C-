#include "MainWindow.h"

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


	// Setting Layouts
	menuLayout->addWidget(searchTask);
	menuLayout->addWidget(newTask);
	menuLayout->addWidget(editTask);
	menuLayout->addWidget(completeTask);
	menuLayout->addWidget(deleteTask);
	mainLayout->addLayout(menuLayout, 3);
	mainLayout->addWidget(tableView, 7);
		







	// Aux settings
		// search bar
		searchTask->setPlaceholderText("Buscar...");
}

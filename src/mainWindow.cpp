#include "MainWindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QHeaderView>

MainWindow::MainWindow(QWidget* parent) : QWidget(parent){
	setWindowTitle("Gerenciado de Tarefas");

	// Buttons
	newTaskBtn = new QPushButton("Nova Tarefa", this);
	editTaskBtn = new QPushButton("Editar Tarefa", this);
	completeTaskBtn = new QPushButton("Completar Tarefa", this);
	deleteTaskBtn = new QPushButton("Excluir Tarefa", this);
	searchTaskLe = new QLineEdit(this);
	statusFilter = new QComboBox(this);

	// Layouts 
	mainLayout = new QHBoxLayout(this);
	menuLayout = new QVBoxLayout;
	tableView = new QTableView;
	model = new QSqlQueryModel;


	// Setting Layouts
	menuLayout->addWidget(searchTaskLe);
	menuLayout->addWidget(statusFilter);
	menuLayout->addWidget(newTaskBtn);
	menuLayout->addWidget(editTaskBtn);
	menuLayout->addWidget(completeTaskBtn);
	menuLayout->addWidget(deleteTaskBtn);
	mainLayout->addLayout(menuLayout, 3);
	mainLayout->addWidget(tableView, 7);
		
		// Combo Box settings
		statusFilter->addItem("Todas");
		statusFilter->addItem(Status::Pending, DbStatus::pending);
		statusFilter->addItem(Status::InProgress, DbStatus::inProgress);
		statusFilter->addItem(Status::Completed, DbStatus::completed);
		

// ---------------------------------------------------------------------------------------- //

	// Connects
		// Search Bar
		connect(searchTaskLe, &QLineEdit::textChanged, this, &MainWindow::searchTaskByAnyColumn);
		// Status Filter
		connect(statusFilter, &QComboBox::currentTextChanged, this, &MainWindow::filterTasksByStatus);
		// Complete Task
		connect(completeTaskBtn, &QPushButton::clicked, this, &MainWindow::completeTask);
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

		// Edit Task
		connect(editTaskBtn, &QPushButton::clicked, this, [=](){
				QModelIndex selectedRow = tableView->currentIndex();
				if(!selectedRow.isValid()){
					QMessageBox::information(this, "Atenção", "Selecione uma linha para editar.");
					return;
					}
				int taskID = model->data(model->index(selectedRow.row(),0)).toInt();
				
				if(!newTaskForm){
				newTaskForm = new TaskForm(taskID);
				newTaskForm->show();

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
	tableView->resizeRowsToContents();
	tableView->setWordWrap(true);
			
			// Header View settingsQ
			QHeaderView* header = tableView->horizontalHeader();
			header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
			header->setSectionResizeMode(1, QHeaderView::Stretch);
			header->setSectionResizeMode(2, QHeaderView::Stretch);
			header->setSectionResizeMode(3, QHeaderView::ResizeToContents);
			header->setSectionResizeMode(4, QHeaderView::ResizeToContents);


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

void MainWindow::completeTask(){
	QModelIndex selectedRow = tableView->currentIndex();
	if(!selectedRow.isValid()){
		QMessageBox::information(this, "Atenção", "Selecione uma tarefa para mudar o status.");
		return;
	}

	if(QMessageBox::question(this, "Atenção", "Deseja alterar status da tarefa para \"Concluida\" ?", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
		int taskID = model->data(model->index(selectedRow.row(),0)).toInt();

		QSqlQuery completeQuery;
		completeQuery.prepare("UPDATE tasks SET status = ? WHERE id = ?;");
		completeQuery.addBindValue(DbStatus::completed); // namespace is defined in TaskForm.h
		completeQuery.addBindValue(taskID);

		if(!completeQuery.exec()){
			QMessageBox::critical(this, "ERRO", "Erro ao alterar status da tarefa:\n" + completeQuery.lastError().text());
			return;
		} else {
			QMessageBox::information(this, "Sucesso", "Tarefa concluida com sucesso.");
			loadTasks();
		}
	}
}

void MainWindow::filterTasksByStatus(){
	QString statusSelected;

	if(statusFilter->currentText() == "Todas"){
		loadTasks();
		return;
	} else if(statusFilter->currentData() == DbStatus::pending){
		statusSelected = DbStatus::pending;
	} else if(statusFilter->currentData() == DbStatus::inProgress) {
		statusSelected = DbStatus::inProgress;
	} else {
		statusSelected = DbStatus::completed;
	}

	QSqlQuery filterStatusQuery;
	filterStatusQuery.prepare("SELECT id, title, description, due_date, status FROM tasks WHERE status = ?;");
	filterStatusQuery.addBindValue(statusSelected);

	if(!filterStatusQuery.exec()){
		QMessageBox::critical(this, "ERRO", "Falha ao filtrar tarefas:\n" + filterStatusQuery.lastError().text());
		return;
	}

	model->setQuery(filterStatusQuery);
	model->setHeaderData(0,Qt::Horizontal,"ID");
	model->setHeaderData(1,Qt::Horizontal,"Título");
	model->setHeaderData(2,Qt::Horizontal,"Descrição");
	model->setHeaderData(3,Qt::Horizontal,"Data Limite");
	model->setHeaderData(4,Qt::Horizontal,"Status");

	tableView->resizeColumnsToContents();
	tableView->resizeRowsToContents();
	tableView->setWordWrap(true);
}

void MainWindow::searchTaskByAnyColumn(){
	if(searchTaskLe->text().isEmpty()){
		loadTasks();
		return;
	} else {
		QSqlQuery searchQuery;
		searchQuery.prepare("SELECT id, title, description, due_date, status FROM tasks WHERE id LIKE ? OR title LIKE ? OR description LIKE ? OR due_date LIKE ? OR status LIKE ?;");
		QString likeQuery = '%' + searchTaskLe->text() + '%';
		searchQuery.addBindValue(likeQuery);
		searchQuery.addBindValue(likeQuery);
		searchQuery.addBindValue(likeQuery);
		searchQuery.addBindValue(likeQuery);
		searchQuery.addBindValue(likeQuery);

		if(!searchQuery.exec()){
			QMessageBox::critical(this, "ERRO", "Falha ao buscar dados:\n" + searchQuery.lastError().text());
			this->close();
			return;
		}
	
		model->setQuery(searchQuery);
		model->setHeaderData(0,Qt::Horizontal,"ID");
		model->setHeaderData(1,Qt::Horizontal,"Título");
		model->setHeaderData(2,Qt::Horizontal,"Descrição");
		model->setHeaderData(3,Qt::Horizontal,"Data Limite");
		model->setHeaderData(4,Qt::Horizontal,"Status");

		tableView->resizeColumnsToContents();
		tableView->resizeRowsToContents();
		tableView->setWordWrap(true);
	}
}

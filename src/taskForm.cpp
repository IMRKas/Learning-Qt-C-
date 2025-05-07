#include "TaskForm.h"
#include <QDate>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>


namespace Status {
	const QString Pending = "Pendente";
	const QString Completed = "Concluída";
	const QString InProgress = "Em andamento";
}

TaskForm::TaskForm(int taskID, QWidget* parent) : QWidget(parent){
	setWindowTitle("Editar Tarefa");
	setAttribute(Qt::WA_DeleteOnClose);

	// Buttons
	saveButton = new QPushButton("Salvar", this);
	cancelButton = new QPushButton("Cancelar", this);

	// Layout
	mainLayout = new QVBoxLayout(this);
	buttonsRow = new QHBoxLayout;
	taskForm = new QFormLayout;
	dateStatusRow = new QHBoxLayout;

	// FormFields
	taskTitle = new QLineEdit(this);
	taskDescription = new QTextEdit(this);
	taskDeadLine = new QDateEdit(this);
	taskStatus = new QComboBox(this);
		// Date popUp settings
		taskDeadLine->setCalendarPopup(true);
		taskDeadLine->setDisplayFormat("dd-MM-yyyy");
		taskDeadLine->setLocale(QLocale(QLocale::Portuguese, QLocale::Brazil));
		// ComboBox settings
		taskStatus->addItem(Status::Pending, DbStatus::pending);
		taskStatus->addItem(Status::Completed, DbStatus::completed);
		taskStatus->addItem(Status::InProgress, DbStatus::inProgress);

	// Form Layout
	taskForm->addRow("Título", taskTitle);
	taskForm->addRow("Descrição", taskDescription);
	taskForm->addRow("Data Limite", dateStatusRow);
		//dateStatusRow
		comboBox = new QLabel("Status");
		dateStatusRow->addWidget(taskDeadLine);
		dateStatusRow->addWidget(comboBox);
		dateStatusRow->addWidget(taskStatus);

	// Set Layouts
	buttonsRow->addWidget(saveButton);
	buttonsRow->addWidget(cancelButton);
	mainLayout->addLayout(taskForm);
	mainLayout->addLayout(buttonsRow);

	// Load data from db
	QSqlQuery loadTaskData;
	loadTaskData.prepare("SELECT title, description, due_date, status FROM tasks WHERE id = ?;");
	loadTaskData.addBindValue(taskID);
	if(loadTaskData.exec() && loadTaskData.next()){
		taskTitle->setText(loadTaskData.value(0).toString());
		taskDescription->setText((loadTaskData.value(1).isNull()) ? "" : loadTaskData.value(1).toString());
		taskDeadLine->setDate(QDate::fromString(loadTaskData.value(2).toString(), "yyyy-MM-dd"));
		if(loadTaskData.value(3).toString() == Db::pending){
			taskStatus->setCurrentText(Status::Pending);
		} else if (loadTaskData.value(3).toString() == Db::completed) {
			taskStatus->setCurrentText(Status::Completed);
		} else {
			taskStatus->setCurrentText(Status::InProgress);
		} 
	} else {
		QMessageBox::critical(this, "ERROR","TAREFA NÃO ENCONTRADA");
		this->close();
		return;
	}


	// connects
	connect(cancelButton, &QPushButton::clicked, this, &QWidget::close);
	connect(saveButton, &QPushButton::clicked, this, [=](){
			if(taskTitle->text().isEmpty()){
				QMessageBox::critical(this, "Erro", "O Campo 'Título' não pode ficar vazio");
				} else {
					QSqlQuery updateTaskQuery;
					updateTaskQuery.prepare("UPDATE tasks SET title = ?, description = ?, due_date = ?, status = ? WHERE id = ?;");
					updateTaskQuery.addBindValue(taskTitle->text());
					updateTaskQuery.addBindValue((taskDescription->toPlainText().isEmpty()) ? QVariant(QVariant::String) : QVariant(taskDescription->toPlainText()));
					updateTaskQuery.addBindValue(taskDeadLine->date().toString("yyyy-MM-dd"));
					updateTaskQuery.addBindValue(taskStatus->currentData().toString().toLower());
					updateTaskQuery.addBindValue(taskID);

					if(!updateTaskQuery.exec()){
						QMessageBox::critical(this, "ERRO", "Falha ao Atualizar Tarefa:\n" + updateTaskQuery.lastError().text());
						return;
						} else {
						QMessageBox::information(this, "SUCESSO", "Tarefa Atualizada");
						this->close();
						}
				}
			});


}

TaskForm::TaskForm(QWidget* parent) : QWidget(parent){
	setWindowTitle("Nova Tafera");
	setAttribute(Qt::WA_DeleteOnClose);

	// Buttons
	saveButton = new QPushButton("Salvar", this);
	cancelButton = new QPushButton("Cancelar", this);

	// Layouts
	mainLayout = new QVBoxLayout(this);
	buttonsRow = new QHBoxLayout;
	taskForm = new QFormLayout;
	dateStatusRow = new QHBoxLayout;


	// Form Fields
	taskTitle = new QLineEdit(this);
	taskDescription = new QTextEdit(this);
	taskDeadLine = new QDateEdit(this);
	taskStatus = new QComboBox(this); // Pending, completed, in progress


	// FormLayout
	taskForm->addRow("Título", taskTitle);
	taskForm->addRow("Descrição",taskDescription);
	taskForm->addRow("Data Limite", dateStatusRow);


	// Window Layout
	mainLayout->addLayout(taskForm);
	mainLayout->addLayout(buttonsRow);
	buttonsRow->addWidget(saveButton);
	buttonsRow->addWidget(cancelButton);



	// Connects
		// CancelButton
		connect(cancelButton, &QPushButton::clicked, this, &QWidget::close);

		// saveButton
		connect(saveButton, &QPushButton::clicked, this, [=](){
				if(taskTitle->text().isEmpty()){
					QMessageBox::information(this, "Atenção", "O campo \"Título\" não pode ficar em branco");
				} else {

					QSqlQuery insertQuery;
					insertQuery.prepare("INSERT INTO tasks(title, description, due_date, status) VALUES (?, ?, ?, ?);");
					insertQuery.addBindValue(taskTitle->text());
					insertQuery.addBindValue((taskDescription->toPlainText().isEmpty()) ? QVariant(QVariant::String) : QVariant(taskDescription->toPlainText()));
					insertQuery.addBindValue(taskDeadLine->date().toString("yyyy-MM-dd"));
					insertQuery.addBindValue(taskStatus->currentData().toString().toLower());

					if(!insertQuery.exec()){
						QMessageBox::critical(this, "ERRO", "Erro ao adicionar tarefa:\n" + insertQuery.lastError().text());
						} else {
							QMessageBox::information(this, "Sucesso", "Tarefa adicionada com sucesso.");
							this->close();
						}
				}
				});


	// Aux Settings
		// Date Setting
		QDate currentDate = QDate::currentDate();
		taskDeadLine->setDate(currentDate);
		taskDeadLine->setCalendarPopup(true);
		taskDeadLine->setDisplayFormat("dd/MM/yyyy");
		taskDeadLine->setLocale(QLocale(QLocale::Portuguese, QLocale::Brazil));

		// ComboBox
		taskStatus->addItem(Status::Pending, DbStatus::pending); 
		taskStatus->addItem(Status::Completed, DbStatus::completed);
		taskStatus->addItem(Status::InProgress, DbStatus::inProgress);

			// dateStatusRow
			comboBox = new QLabel("Status");
			dateStatusRow->addWidget(taskDeadLine);
			dateStatusRow->addWidget(comboBox);
			dateStatusRow->addWidget(taskStatus);

	taskTitle->setFocus();

}

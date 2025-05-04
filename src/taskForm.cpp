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
	taskDL = new QDateEdit(this);
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
					insertQuery.addBindValue(taskDL->date().toString("yyyy-MM-dd"));
					insertQuery.addBindValue(taskStatus->currentData().toString());

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
		taskDL->setDate(currentDate);
		taskDL->setCalendarPopup(true);
		taskDL->setDisplayFormat("dd/MM/yyyy");
		taskDL->setLocale(QLocale(QLocale::Portuguese, QLocale::Brazil));

		// ComboBox
		taskStatus->addItem(Status::Pending, "pendente");
		taskStatus->addItem(Status::Completed, "concluida");
		taskStatus->addItem(Status::InProgress, "em_andamento");

			// dateStatusRow
			comboBox = new QLabel("Status");
			dateStatusRow->addWidget(taskDL);
			dateStatusRow->addWidget(comboBox);
			dateStatusRow->addWidget(taskStatus);

	taskTitle->setFocus();

}

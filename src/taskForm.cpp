#include "TaskForm.h"
#include <QDate>
#include <QMessageBox>

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
				}

				});



	// Aux Settings
		// Current Date
		QDate currentDate = QDate::currentDate();
		taskDL->setDate(currentDate);
		taskDL->setCalendarPopup(true);

		// ComboBox
		taskStatus->addItems({"Pendente","Concluída","Em andamento"});

		// dateStatusRow
			comboBox = new QLabel("Status");
			dateStatusRow->addWidget(taskDL);
			dateStatusRow->addWidget(comboBox);
			dateStatusRow->addWidget(taskStatus);

}

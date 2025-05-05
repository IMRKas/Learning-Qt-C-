#ifndef TASK_FORM_H
#define TASK_FORM_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <string>

namespace DbStatus {
	const QString pendente = "pendente";
	const QString concluida = "concluida";
	const QString emAndamento = "em_andamento";
}
	

class QPushButton;

class TaskForm : public QWidget {
	Q_OBJECT
	public:
		//Constructors
		TaskForm(QWidget* parent = nullptr);

	
	private:

		// Layouts
		QVBoxLayout* mainLayout;
		QHBoxLayout* buttonsRow;
		QFormLayout* taskForm;
		QHBoxLayout* dateStatusRow;

		//Buttons
		QPushButton* saveButton;
		QPushButton* cancelButton;

		// Form Fields
		QLineEdit* taskTitle;
		QTextEdit* taskDescription;
		QDateEdit* taskDL;
		QComboBox* taskStatus;

		// Labels
		QLabel* comboBox;
};
#endif

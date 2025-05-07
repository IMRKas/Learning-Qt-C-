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
	const QString pending = "pendente";
	const QString completed = "concluida";
	const QString inProgress = "em_andamento";
}
	
namespace Status {
	const QString Pending = "Pendente";
	const QString Completed = "Concluída";
	const QString InProgress = "Em andamento";
}

class QPushButton;

class TaskForm : public QWidget {
	Q_OBJECT
	public:
		//Constructors
		TaskForm(QWidget* parent = nullptr);
		TaskForm(int taskID, QWidget* parent = nullptr);

	
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
		QDateEdit* taskDeadLine;
		QComboBox* taskStatus;

		// Labels
		QLabel* comboBox;
};
#endif

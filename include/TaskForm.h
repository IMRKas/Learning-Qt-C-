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

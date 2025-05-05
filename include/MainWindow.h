#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include "TaskForm.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QSqlQueryModel>
#include <QModelIndex>

class MainWindow : public QWidget {
	Q_OBJECT

	public:
		MainWindow(QWidget* parent = nullptr);

		void loadTasks();
		void deleteTask();
		void completeTask();





	private:
		// Buttons
		QPushButton* newTaskBtn{nullptr};
		QPushButton* editTaskBtn{nullptr};
		QPushButton* completeTaskBtn{nullptr};
		QPushButton* deleteTaskBtn{nullptr};

			// Search "button"
			QLineEdit* searchTaskLe{nullptr};

	
		// Layouts
		QHBoxLayout* mainLayout{nullptr};
		QVBoxLayout* menuLayout{nullptr};
		QTableView* tableView{nullptr};
		QSqlQueryModel* model{nullptr};

		// Creating a pointer to TaskForm to control the use of newTask button
		// Nullptr means that there is no newTask window open
		TaskForm* newTaskForm{nullptr};



};
#endif

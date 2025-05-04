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





	private:
		// Buttons
		QPushButton* newTask{nullptr};
		QPushButton* editTask{nullptr};
		QPushButton* completeTask{nullptr};
		QPushButton* deleteTask{nullptr};

			// Search "button"
			QLineEdit* searchTask{nullptr};

	
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

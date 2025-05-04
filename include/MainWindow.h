#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
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
		QModelIndex* model{nullptr};

};
#endif

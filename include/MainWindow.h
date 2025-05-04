#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <sqlite3.h>


class MainWindow : public QWidget {
	Q_OBJECT

	public:
		MainWindow(sqlite3* db, QWidget* parent = nullptr);





	private:


};
#endif

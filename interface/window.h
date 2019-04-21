#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

#include "./display/view.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit Window(QWidget *parent = 0);
	~Window();
	
	void AddView();
	void DeleteView();
	void SelectView(int index);
	
private:
	Ui::Window *ui;
	std::vector<View> views;
	std::vector<View*> curViews;
};

#endif // WINDOW_H

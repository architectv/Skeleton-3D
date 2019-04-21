#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

//#include "view.h"

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
	
private slots:
	void on_actionLoadScene_triggered();
	
	void on_actionSaveScene_triggered();
	
	void on_actionLine_triggered();
	
	void on_actionRect_triggered();
	
	void on_actionCircle_triggered();
	
	void on_actionPolygon_triggered();
	
	void on_actionCut_triggered();
	
	void on_actionCopy_triggered();
	
	void on_actionPaste_triggered();
	
	void on_actionCube_triggered();
	
	void on_actionSphere_triggered();
	
	void on_actionCone_triggered();
	
	void on_actionTorus_triggered();
	
	void on_actionUnion_triggered();
	
	void on_actionIntersect_triggered();
	
	void on_actionTrim_triggered();
	
	void on_actionCylinder_triggered();
	
	void on_actionLift_triggered();
	
	void on_actionSection_triggered();
	
	void on_actionPyramid_triggered();
	
	void on_actionMove_triggered();
	
	void on_actionScale_triggered();
	
	void on_actionRotate_triggered();
	
	void on_actionProjection_triggered();
	
private:
	Ui::Window *ui;
	/*std::vector<View> views;
	std::vector<View*> curViews;*/
};

#endif // WINDOW_H

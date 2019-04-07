#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>

#include <iostream>

#include "model.h"
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	
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
	Ui::MainWindow *ui;
	std::string FileName;
	View MainView;
	
};

#endif // MAINWINDOW_H

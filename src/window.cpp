#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::Window)
{
	ui->setupUi(this);
}

Window::~Window()
{
	delete ui;
}

void Window::on_actionLoadScene_triggered()
{
	
}

void Window::on_actionSaveScene_triggered()
{
	
}

void Window::on_actionLine_triggered()
{
    
}

void Window::on_actionRect_triggered()
{
    
}

void Window::on_actionCircle_triggered()
{
    
}

void Window::on_actionPolygon_triggered()
{
    
}

void Window::on_actionCut_triggered()
{
    
}

void Window::on_actionCopy_triggered()
{
    
}

void Window::on_actionPaste_triggered()
{
    
}

void Window::on_actionCube_triggered()
{
    
}

void Window::on_actionSphere_triggered()
{
    
}

void Window::on_actionCone_triggered()
{
    
}

void Window::on_actionTorus_triggered()
{
    
}

void Window::on_actionUnion_triggered()
{
    
}

void Window::on_actionIntersect_triggered()
{
    
}

void Window::on_actionTrim_triggered()
{
    
}

void Window::on_actionCylinder_triggered()
{
    
}

void Window::on_actionLift_triggered()
{
    
}

void Window::on_actionSection_triggered()
{
    
}

void Window::on_actionPyramid_triggered()
{
    
}

void Window::on_actionMove_triggered()
{
    
}

void Window::on_actionScale_triggered()
{
    
}

void Window::on_actionRotate_triggered()
{
    
}

void Window::on_actionProjection_triggered()
{
    
}

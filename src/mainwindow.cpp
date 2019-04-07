#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <vector>
using std::vector;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	MainView()
{
	ui->setupUi(this);
	setWindowTitle("Skeleton3D");
	
	filename = nullptr;
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionLoadScene_triggered()
{
	QString str = QFileDialog::getOpenFileName(this, "Открыть файл",
											   QDir::currentPath(),
											   "Skeleton 3D Files (*.sk3d);;"
											   "All files (*.*)");
	if (!str)
		return;
	FileName = str.toStdString();
	
	ifstream InputFile;
	InputFile.open(FileName);
	if (!InputFile.is_open())
		return;
	
	InputFile.close();
}

void MainWindow::on_actionSaveScene_triggered()
{
	QString str = QFileDialog::getSaveFileName(this, "Открыть файл",
											   QDir::currentPath(),
											   "Skeleton 3D Files (*.sk3d);;"
											   "All files (*.*)");
	if (!str)
		return;
	FileName = str.toStdString();
	
	ofstream OutputFile;
	OutputFile.open(FileName);
	if (!OutputFile.is_open())
		return;
	
	vector<Model> Models = MainView.getModels();
	OutputFile << Models.size() << std::endl;
	for (int i = 0; i < Models.size(); i++)
	{
		vector<Point> Points = Models[i].getPoints();
		vector<Edge> Edges = Models[i].getEdges();
		vector<Surface> Surfaces = Models[i].getSurfaces();
		OutputFile << Points.size() << ' ' << Edges.size() << ' ' <<
					  Surfaces.size() << std::endl << std::endl;
		
		for (int j = 0; j < Points.size(); j++)
			OutputFile << Points[j].x << ' ' << Points[j].y << ' ' <<
						  Points[j].z << std::endl;
		OutputFile << std::endl;
		
		for (int j = 0; j < Edges.size(); j++)
			OutputFile << Edges[j].start.index << ' ' <<
						  Edges[j].finish.index << std::endl;
		OutputFile << std::endl;
		
		for (int j = 0; j < Surfaces.size(); j++)
		{
			OutputFile << Surfaces[j].numberEdges << ' ';
			for (int k = 0; k < Surfaces[j].numberEdges; k++)
				OutputFile << Surfaces[j].edges[k].index << ' ';
		}
		OutputFile << std::endl;
	}
	
	OutputFile.close();
}

void MainWindow::on_actionLine_triggered()
{
    
}

void MainWindow::on_actionRect_triggered()
{
    
}

void MainWindow::on_actionCircle_triggered()
{
    
}

void MainWindow::on_actionPolygon_triggered()
{
    
}

void MainWindow::on_actionCut_triggered()
{
    
}

void MainWindow::on_actionCopy_triggered()
{
    
}

void MainWindow::on_actionPaste_triggered()
{
    
}

void MainWindow::on_actionCube_triggered()
{
    
}

void MainWindow::on_actionSphere_triggered()
{
    
}

void MainWindow::on_actionCone_triggered()
{
    
}

void MainWindow::on_actionTorus_triggered()
{
    
}

void MainWindow::on_actionUnion_triggered()
{
    
}

void MainWindow::on_actionIntersect_triggered()
{
    
}

void MainWindow::on_actionTrim_triggered()
{
    
}

void MainWindow::on_actionCylinder_triggered()
{
    
}

void MainWindow::on_actionLift_triggered()
{
    
}

void MainWindow::on_actionSection_triggered()
{
    
}

void MainWindow::on_actionPyramid_triggered()
{
    
}

void MainWindow::on_actionMove_triggered()
{
    
}

void MainWindow::on_actionScale_triggered()
{
    
}

void MainWindow::on_actionRotate_triggered()
{
    
}

void MainWindow::on_actionProjection_triggered()
{
    
}

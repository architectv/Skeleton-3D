#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "window.h"
#include "./display/scene.h"

class Application : public QApplication
{
public:
	Application(int argc, char **argv);
	
	void NewScene();
	void LoadScene();
	void SaveScene();
	
private:
	Window mainWindow;
	std::vector<Scene> scenes;
	Scene *curScene;
	std::string fileName;
};

#endif // APPLICATION_H

#ifndef MODELCREATOR_H
#define MODELCREATOR_H

#include <model.h>

class ModelCreator: public Model {
 public:
    Model CreateCube(Point, double);
    Model CreateSphere(Point, double);
    Model CreateCylinder(Point, double, double);
    Model CreateCone(Point, double, double);
    Model CreateTorus(Point, double, double);
};

#endif // MODELCREATOR_H

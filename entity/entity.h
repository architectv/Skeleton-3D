#ifndef ENTITY_H
#define ENTITY_H

class Point;

class Entity {
    public:
        Entity();
        virtual ~Entity();
        virtual void Move(const double&, const double&, const double&);
        virtual void Rotate(const double&, const double&, const double&, const Point&);
        virtual void Scale(const double&, const double&, const double&, const Point&);
};

#endif // ENTITY_H

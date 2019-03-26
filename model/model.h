#include <iostream>

class Model {
 public:
  // constructor
  Model();

  // destructor
  ~Model();

  // сколько точек всего в модели
  const size_t CountPoints() const;

  // сколько ребер в модели
  const size_t CountEdges() const;

  // сколько граней в модели
  const size_t CountSurface() const;

 private:
  // количество точек
  size_t numberPoints;

  // количество ребер
  size_t numberEdges;

  // количество граней
  size_t numberSurface;
};
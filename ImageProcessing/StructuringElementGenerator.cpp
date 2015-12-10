#include "StructuringElementGenerator.h"

StructuringElementGenerator::StructuringElementGenerator()
{
}

StructuringElement StructuringElementGenerator::neighborhood4()
{
  StructuringElement structuringElement(3, 3);

  structuringElement.setValue(false, 0, 0);
  structuringElement.setValue(false, 2, 0);
  structuringElement.setValue(false, 0, 2);
  structuringElement.setValue(false, 2, 2);

  return structuringElement;
}

StructuringElement StructuringElementGenerator::neighborhood8()
{
  StructuringElement structuringElement(3, 3);
  return structuringElement;
}

StructuringElement StructuringElementGenerator::circle(unsigned int radius)
{
  unsigned int size = radius * 2 + 1;
  StructuringElement structuringElement(size, size);
  structuringElement.setAllValues(false);
  structuringElement.setCircle(true, Circle(structuringElement.getReferencePoint(), radius));

  return structuringElement;
}

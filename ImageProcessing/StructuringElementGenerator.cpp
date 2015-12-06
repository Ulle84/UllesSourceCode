#include "StructuringElementGenerator.h"

StructuringElementGenerator::StructuringElementGenerator()
{
}

StructuringElement StructuringElementGenerator::neighborhood4()
{
  StructuringElement structuringElement(3, 3);
  structuringElement.setAllValues(true);

  structuringElement.setValue(false, 0, 0);
  structuringElement.setValue(false, 2, 0);
  structuringElement.setValue(false, 0, 2);
  structuringElement.setValue(false, 2, 2);

  return structuringElement;
}

StructuringElement StructuringElementGenerator::neighborhood8()
{
  StructuringElement structuringElement(3, 3);
  structuringElement.setAllValues(true);
  return structuringElement;
}

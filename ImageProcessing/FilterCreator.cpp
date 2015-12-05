#include "FilterCreator.h"

FilterCreator::FilterCreator()
{
}

Filter FilterCreator::mean(unsigned int width, unsigned int height)
{
  if (height == 0)
  {
    height = width;
  }

  Filter filter(width, height);

  filter.setAllValues(1);
  filter.setPreFactor(1.0 / (width * height));

  return filter;
}

Filter FilterCreator::binomial(unsigned int width, unsigned int height)
{
  if (height == 0)
  {
    height = width;
  }

  if (width % 2 == 0)
  {
    width++;
  }

  if (height % 2 == 0)
  {
    height++;
  }

  Filter filter(width, height);
  filter.setBinomialValues();
  filter.setPreFactor(1.0 / filter.getSumOfAllValues());

  return filter;
}

Filter FilterCreator::laplacian()
{
  Filter filter(3, 3);

  filter.setValue(-1, 1, 0);
  filter.setValue(-1, 0, 1);
  filter.setValue( 4, 1, 1);
  filter.setValue(-1, 2, 1);
  filter.setValue(-1, 1, 2);

  return filter;
}

Filter FilterCreator::laplacianBig()
{
  Filter filter(9, 9);

  // TODO set values

  filter.printValuesToConsole("laplacianBig");

  return filter;
}

Filter FilterCreator::laplacian2()
{
  Filter filter(3, 3);
  filter.setAllValues(-1);
  filter.setValue(8, 1, 1);

  filter.printValuesToConsole("laplacian2");

  return filter;
}

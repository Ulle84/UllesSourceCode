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

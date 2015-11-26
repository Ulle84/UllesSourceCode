#ifndef HISTOGRAM_H
#define HISTOGRAM_H


class Histogram
{
public:
  Histogram();
  Histogram(const Histogram& rhs);
  ~Histogram();

  Histogram& operator= (const Histogram& rhs);

  // TODO declare copy and assignment operator

  void print(unsigned int threshold);
  void clear();

  unsigned int getMaxValue() const;

private:
  unsigned int m_size;
  unsigned int* m_values;

  friend class Image;
};

#endif // HISTOGRAM_H

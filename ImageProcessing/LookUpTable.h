#ifndef LOOKUPTABLE_H
#define LOOKUPTABLE_H


class LookUpTable
{
public:
  LookUpTable();
  LookUpTable(const LookUpTable& rhs);
  ~LookUpTable();

  LookUpTable& operator= (const LookUpTable& rhs);

  void clear();

private:
  unsigned int m_size;
  unsigned char* m_values;

  friend class Image;
};

#endif // LOOKUPTABLE_H

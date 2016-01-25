#ifndef BASE_PRIVATE_H
#define BASE_PRIVATE_H

class BasePrivate
{
public:
  BasePrivate(Base* base) : base(base)
  {
    std::cout << "construction of BasePrivate" << std::endl;
  }

  void reset();

  Base* base;
  int value;
};

void BasePrivate::reset()
{
  std::cout << "BasePrivate::reset()" << std::endl;
  value = 42;
  base->update();
}

#endif // BASE_PRIVATE_H

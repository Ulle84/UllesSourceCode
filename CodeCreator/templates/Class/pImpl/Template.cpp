#include "Template.h"
#include "TemplateImpl.h"

#include <utility>

Template::Template()
  : m(new TemplateImpl())
{
}

Template::Template(const Template& rhs)
  : m(new TemplateImpl(*rhs.m))
{
}

Template::Template(Template&& rhs)
  : m(nullptr)
{
  std::swap(m, rhs.m);
}

Template& Template::operator=(const Template& rhs)
{
  if(this != &rhs)
  {
    *m = *(rhs.m);
  }
  return *this;
}

Template::~Template()
{
  delete m;
}

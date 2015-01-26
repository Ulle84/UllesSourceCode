#include "Template.h"
#include "TemplateImpl.h"

#include <utility>

Template::Template()
  : m(new TemplateImpl())
{
}

Template::~Template()
{
  delete m;
}

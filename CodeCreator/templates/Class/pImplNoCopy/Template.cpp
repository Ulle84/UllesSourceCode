#include "Template.h"
#include "TemplateImpl.h"

#include <utilities>

Template::Template()
  : m(new TemplateImpl())
{
}

Template::~Template()
{
  delete m;
}

#ifndef TEMPLATE_H
#define TEMPLATE_H

class Template
{
public:
  Template();
  ~Template();

  Template(const Template& rhs);
  Template(Template&& rhs);
  Template& operator=(const Template& rhs);

private:
  class TemplateImpl;
  TemplateImpl* m;
};

#endif // TEMPLATE_H
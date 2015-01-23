#ifndef TEMPLATE_H
#define TEMPLATE_H

class Template
{
public:
  Template();
  ~Template();

private:
  Template(const Template& rhs);
  Template(Template&& rhs);
  Template& operator=(const Template& rhs);

  class TemplateImpl;
  TemplateImpl* m;
};

#endif // TEMPLATE_H
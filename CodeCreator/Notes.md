# Bugs

# ToDo
## General
* check occurences of friend classes
* CodeHelper -> get Interfacename etc --> all conventions (trailing I etc) should be encapsulated -> same procedure for member

## Decorator
* !!! Next TODO !!!
* decorator: declare default constructor private?
* decorator: implement custom cunstructor
* complete generator for decorator
* test code

## State
* understand state pattern
* complete generator for state

## Class
* members: auto include headers of used members (?)
* full move operator and move constructor support (with member copy etc.)
* improve include handling - include of template parameters
* optional: create ui file

## Misc
* remove Template directory, when not needed anymore
* List-Widget - button duplicate
* monotype font for code inputs
* check of codec of generated files are correct - use UTF-8 if possible for Visual-Studio and QtCreator
* namespace support for all generators

# Ideas
* save and laod interfaces - define a interface with the interface-generator and use it in class-generator for example
* support for operators (<, >, ==, != etc.)
* save current folder at folder selection
* class: q-Pointer support -> pointing to overlaying class
* const method support
* type input (bool, int, double etc.) with suggestions and or combo-box
* Templates -> generate project per template?
* template for exporting dll
* more patterns
  * Factory
  * Command
  * Adapter
  * Template Method
  * Iterator
  * Composite
  * State
  * Proxy
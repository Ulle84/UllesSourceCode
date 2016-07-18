# Bugs

# ToDo
## General
* CodeHelper -> get Interfacename etc --> all conventions (trailing I etc) should be encapsulated -> same procedure for member

## Decorator
* decorator: declare default constructor private?
* decorator: implement custom cunstructor
* complete generator for decorator

## Observer
* test generator
* support for multiple observers

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
* use interface editor consequently
* namespace support for all generators

# Ideas
* support for operators (<, >, ==, != etc.)
* save current folder at folder selection
* class: q-Pointer support -> pointing to overlaying class
* const method support
* implementation of  methods -> return something valid for compiler - always mark as "ToDo"
* type input (bool, int, double etc.) with suggestions and or combo-box
* Templates -> generate project per template?
* template for exporting dll
* more patterns
  * Factory
  * Abstract Factory
  * Command
  * Adapter
  * Template Method
  * Iterator
  * Composite
  * State
  * Proxy

# Done
* looking in wrong folder for templates -> needs to be configurable!!!
* namespace
* no template files -> write code instead -> much more flexible
* singleton support -> override options (no public constructor etc.), before creating
* d-Pointer support
* base implementation of GeneratorInterface
* persistance of interface
* implementation of interfaces
* set splitter width
* implement button define methods
* save and load (xml) interface
* change GeneratorInterface to new GeneratorI style
* full support for methods (gui + xml + code generation)
* class: support for members (gui + xml + code generation)
* class: new class Members with hasPublicMembers etc.
* members: support for prefix
* members: getter and setter
* members: element initialization in constructors
* members: if type contains '*' -> do not copy - mark as todo
* class: getter for bool -> prefix is
* remove CodeGenerator, InterfaceHelper and Options (and all other) classes
* class: support for additional declarations QStringList if(declaration.startWith(m_className ... -> print after constructors
* class: support for additional implementations QList<QStringList>
* class: support for forward declarations
* class: support for additional declaration includes - #include <algorithm> for example
* class: support for additional implementation includes - #include <algorithm> for example
* complete generator for observer

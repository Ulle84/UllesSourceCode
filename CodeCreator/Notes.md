# Bugs

# ToDo
* remove template mechanism from existing generators -> create new generators with Prefix 'Generator'
* remove CodeGenerator, InterfaceHelper and Options (and all other) classes, when not needed anymore
* remove Template directory

# Ideas
* save current folder at folder selection
* class: q-Pointer support -> pointing to overlaying class
* const method support
* implementation of  methods -> return something valid for compiler - always mark as "ToDo"
* type input (bool, int, double etc.) with suggestions and or combo-box
* Templates -> generate project per template?
* xml helper -> checkbox, lineedit, plaintextedit in xml und zurück -> static functions
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

# Bugs

# ToDo
* Class Template
  * full support for methods (gui + xml)
  * remove Class::checkOptions() -> must be handled in GUI
  * const method support
  * save to file -> generate
  * implementation of  methods
  * methods
    * protected and private declarations
    * all implementations
  * finish GeneratorInterface
  * q-Pointer support -> pointing to overlaying class
  * singleton and dPointer combined?
* save current folder at folder selection
* remove template mechanism from existing generators -> create new generators with Prefix 'Generator'
* remove CodeGenerator and Options class, when not needed anymore

# Ideas
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

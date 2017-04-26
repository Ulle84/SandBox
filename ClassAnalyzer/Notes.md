# ​ToDo
* parse list of folders
* attach namespaces to base classes, if needed (how?)
  - check if class is in same namespace
  - check if class has already namespace-prefix
  - do this for all namespaces from inner to outer
* create links: base classes to derived classes
* Show all classes in tree
  - sorted alphabetically
  - expand base classes and derived classes on demand
  - expand even further if requested by user
  - see visual studio class browser for implementatiom
* generate class hierarchy
  - every class has a score of 0 initially
  - iterate list of classes, each base class gets the own score plus one (the score of the base class remaons unchanged if score is already greater)
  - reduction of levels (top-bottom - only do linebreak if a baseclass is already drawn - see next point)
* Visualize class hierarchy
  - same level -> same line
  - sort columns alphabetically
  - first textual
  - second visual
* Tab Visualization if there are self-contained class-structures
* analyze methods and members
* visualize methods and members
  - 1st only class instances
  - 2nd methods
  - 3rd members (without class instances)
* If member is a class create link to class or visualize dependency
* Create links to lines of code: definition and implementation (jump to code line - only appliable in QtCreator Plugin)

Further Ideas
* get access path - I am in class A and want to use a functioality of class Z - is there an existing way (path) to access this class?
* develop a test suite

Done
* Create test class files A1 A2, B1, B2, B3 etc create at least two self-contained structures
* read all files and parse class names - generate a list of classes
* save last selected folder
* filter templates i. e. InstanceTracer<NamedValueMap, 100> (content between brackets must be filtered out)
* ignore typedefs: typedef std::vector<class String> StringList; (ignore keyword class if ';' comes before '{');
* remove comments before parsing (first remove block comments, than remove line comments) - be careful and test good!!!
* ignore foward-declarations
* parse base classes
* parse namespaces and attach to class name (fully qualified name)

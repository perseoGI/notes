Scope determines where a variable is accessible. Duration determines where a
variable is created and destroyed. Linkage determines whether the variable can
be exported to another file or not.

Global variables have global scope (aka. file scope), which means they can be
accessed from the point of declaration to the end of the file in which they are
declared.

Global variables have static duration, which means they are created when the
program is started, and destroyed when it ends.

Global variables can have either internal or external linkage, via the static
and extern keywords respectively.




When applied to a global variable, the static keyword defines the global
variable as having internal linkage, meaning the variable cannot be exported to
other files.

When applied to a local variable, the static keyword defines the local variable
as having static duration, meaning the variable will only be created once, and
will not be destroyed until the end of the program.


## Namespaces
### Unnamed namespaces

Internal linkage (same as declare function static), but also internal linkage for variables

### Inline Namespaces

inline namespace v1{ void foo() }

namespace v2 {void foo() }

foo(); // default namespace -> v1
v1::foo(); // v1 version
v2::foo(); // v2 version


Useful to keep API intact and allow using newer versions with v2::xxx
Useful to push newer versions changing the inline namespace

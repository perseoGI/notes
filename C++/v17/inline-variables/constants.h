#ifndef CONSTANTS
#define CONSTANTS

// Inline variable:  inline variable is one that is allowed to be defined in
// multiple files without violating the one definition rule. Inline global
// variables have external linkage by default.
// The linker will consolidate all inline definitions of a variable into a
// single variable definition (thus meeting the one definition rule). This
// allows us to define variables in a header file and have them treated as if
// there was only one definition in a .cpp file somewhere
namespace constants {
   inline constexpr double PI = 3.1415;
   inline constexpr double E = 2.71828;
}

#endif // !CONSTANTS

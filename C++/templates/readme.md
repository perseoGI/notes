# Templates 

## Template instantiation

- A function template is invoked
- Taking address of a function template
```cpp
int (*function)(int, int) = max;
```
- Using explicit instantiation

```cpp
template char max(char a, char b);
```

- Creating explicit specialization


## Explicit Specialization

- Template specialized for a particular type
- Provides correct semantics for some datatype
- Or implements an algorithm optimally for a specific type
- Explicitly specialized functions must be defined in .cpp files
- Primary template definition should occur before specialization


```cpp
template <> const char *max<const char *>(const char *a, const char *b) {
  return strcmp(a, b) > 0 ? a : b;
}

// Or a short form without specifying the type after function name
template <> float max(float a, float b) { return a > b ? a : b; }
```


## Nontype Template Arguments

 - Expression that is computed at compile time within a template argument list
 - Must be a constant expression (addresses, references, integrals, nullptr, enums)
 - Part of the template types


## Short hand vs long hand notation

When defining a class template, all occurrences of the class name can be written in the short hand notation, eg.

```cpp
template<typename T, typename U>
class Foo{
    Foo(const Foo &foo){...}
    Foo create();
};
```

But outside the class definition context, the long hand notation must me explicitly written, eg.

```cpp
template <typename T, typename U>
Foo<T, U> Foo<T, U>::create(){}
```

## Partial specialization


## Alias templates

The main difference between `typedef` alias and `using` (C++11) alias is that
`using` alias allows to create alias templates.

Also, is more natural to read.

```cpp

template <typename T>
using ContainerList = std::vector<std::list<T>>;

ContainerList<std::string> names;
```

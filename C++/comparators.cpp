#include <iostream>
#include <string>
#include <set>

struct Foo {
    std::string key;
    std::string value;
};

struct Comparator {
    bool operator()(const Foo &lhs, const Foo &rhs) const { return lhs.key < rhs.key; }

    // Transparent comparator enabled, declared both side comparators (templatized to avoid unnecessary runtime
    // castings)
    using is_transparent = int;
    template <typename T>
    bool operator()(const T &lhs, const Foo &rhs) const
    {
        return lhs < rhs.key;
    }

    template <typename T>
    bool operator()(const Foo &rhs, const T &lhs) const
    {
        return rhs.key < lhs;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<Foo, T> set)
{
    for (const auto &[key, value] : set) {
        os << key << ": " << value << '\n';
    }
    return os;
}

// Pure lambda
template <typename Type, typename... Comparator>
auto make_set(Comparator &&...comparator)
{
    struct Compare : std::decay_t<Comparator>... {
        using std::decay_t<Comparator>::operator()...;
        using is_transparent = int;
    };
    return std::set<Type, Compare>{Compare{std::forward<Comparator>(comparator)...}};
}

int main()
{
    std::set<Foo, decltype([](const Foo &lhs, const Foo &rhs) { return lhs.key < rhs.key; })> set;

    set.insert({"hi", "hola"});
    set.insert({"by", "adios"});

    std::cout << set << '\n';
    std::cout << set.count({"by"}) << '\n';  // A temporary object needs to be created -> inefficient

    std::set<Foo, Comparator> compSet;
    compSet.insert({"hi", "hola"});
    compSet.insert({"by", "adios"});
    std::cout << compSet << '\n';
    std::cout << compSet.count("hi") << '\n';  // Better approach

    // A pure lambda approach
    auto lambdaSet = make_set<Foo>([](const Foo &lhs, const Foo &rhs) { return lhs.key < rhs.key; },
                                   [](const auto &lhs, const Foo &rhs) { return lhs < rhs.key; },
                                   [](const Foo &lhs, const auto &rhs) { return lhs.key < rhs; });
    lambdaSet.insert({"hi", "hola"});
    lambdaSet.insert({"by", "adios"});
    std::cout << lambdaSet << '\n';
    std::cout << lambdaSet.count("hi") << '\n';  // Better approach

    return 0;
}

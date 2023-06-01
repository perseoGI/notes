#include <iostream>

template <typename T, int columns> 
class Printer {
  T *m_data;

public:
  Printer(T *data) : m_data{data} {}
  void print() {
    std::cout << "Columns: " << columns << '\n'
              << '{' << *m_data << '}' << std::endl;
  }
};

template <typename T> 
class Printer<T, 80> {
  T *m_data;

public:
  Printer(T *data) : m_data{data} {}
  void print() {
    std::cout << "Using default 80 old-school columns\n"
              << '{' << *m_data << '}' << std::endl;
  }
};

template <typename T>
class SmartPointer{
    T* m_data;

public:
    SmartPointer(T* data) : m_data{data} {}
    
    T*operator ->(){
        return m_data;
    }

    T &operator *(){
        return *m_data;
    }
    
    ~SmartPointer() {
        std::cout << "Free memory of m_data" << std::endl;
        delete m_data;
    }
};

// Array specialization
template <typename T>
class SmartPointer<T[]>{
    T* m_array;

public:
    SmartPointer(T* data) : m_array{data} {}

    T & operator [] (const int index){
        return m_array[index];
    }
    
    ~SmartPointer() {
        std::cout << "Free memory of m_array" << std::endl;
        delete [] m_array;
    }
};

int main(int argc, char *argv[]) {

  int data{42};
  Printer<int, 80> printer{&data};
  printer.print();

  SmartPointer<float> sm{new float(3.2)};
  std::cout << *sm << std::endl;

  SmartPointer<int[]> arrayPointer{new int[6]{0, 1, 2, 3, 4, 5}};
  std::cout << arrayPointer[4] << std::endl;

}

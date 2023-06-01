#include <iostream>

template <typename T, int size> class Queue {
  T data[size];
  int end{-1};

public:
  void enqueue(T &&elem) { data[++end] = elem; }
  T dequeue() { return data[end--]; }
  bool isEmpty() const { return end < 0; }
  bool isFull() const { return end == size - 1; }

  Queue() = default;

  // Short hand notation: no need to specify the template arguments inside the
  // class
  Queue(const Queue &queue) {
    std::cout << "Copy constructor\n";
    end = queue.end;
    std::copy(std::begin(queue.data), std::end(queue.data), data);
  }

  Queue(Queue &&queue);
  static Queue create();
};

// Long hand notation: outside the class, template parameters are needed
template <typename T, int size> Queue<T, size>::Queue(Queue &&queue) {
  std::cout << "Move constructor\n";
  end = std::move(queue.end);
  std::move(std::begin(queue.data), std::end(queue.data), data);
}

template <typename T, int size> Queue<T, size> Queue<T, size>::create() {
  return Queue<T, size>();
}

int main(int argc, char *argv[]) {

  auto queue{Queue<int, 3>()};
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  auto copy{queue};
  while (!copy.isEmpty()) {
    std::cout << copy.dequeue() << ' ';
  }
  std::cout << std::endl;

  auto test{Queue<float, 10>::create()};
  auto moved{std::move(test)};
  return 0;
}

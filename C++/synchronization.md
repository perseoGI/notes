# C++ Synchoronization methods

TBD

```cpp
#include <condition_variable>
#include <mutex>

class Foo {
public:
    Foo() {

    }

    void first(function<void()> printFirst) {
        std::lock_guard lock(mutex_);
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        ready1_ = true;
        cv1_.notify_one();
    }

    void second(function<void()> printSecond) {
        std::unique_lock<std::mutex> u_lock(mutex_);
        cv1_.wait(u_lock, [this]{return ready1_;});
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        ready2_ = true;
        cv2_.notify_one();
    }

    void third(function<void()> printThird) {
        std::unique_lock<std::mutex> u_lock(mutex_);
        cv2_.wait(u_lock, [this]{return ready2_;});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }

private:
    std::condition_variable cv1_;  // To allow T2 to wait for T1.
    bool ready1_ = false;
    std::condition_variable cv2_;  // To allow T3 to wait for T2.
    bool ready2_ = false;
    std::mutex mutex_;
};
```

```cpp
class Foo {
public:
  mutex a, b;

  Foo(){
    a.lock(), b.lock();
  }

  void first(function<void()> printFirst) {
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    a.unlock();
  }

  void second(function<void()> printSecond) {
    a.lock();
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    a.unlock(), b.unlock();
  }

  void third(function<void()> printThird) {
    b.lock();
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
    b.unlock();
  }

};
```

```cpp
class Foo {
public:
    std::atomic<std::size_t> n{0};

    void first(function<void()> printFirst) {
        printFirst();
        n.fetch_add(1);
    }

    void second(function<void()> printSecond) {
        while(n.load() != 1) {
            std::this_thread::yield();
        }
        printSecond();
        n.fetch_add(1);
    }

    void third(function<void()> printThird) {
        while(n.load() != 2) {
            std::this_thread::yield();
        }
        printThird();
    }
};
```

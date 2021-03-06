#pragma once

#include <condition_variable>
#include <atomic>

template<typename>
class Promise;

template<typename>
class Future;

class State {
public:
    std::atomic<bool> isReady;
    std::exception_ptr except;

    std::atomic<bool> hasPromise;
};

template<typename T>
class FutureState : public State {
public:

    friend class Promise<T>;
    friend class Future<T>;

private:
    T value;
};

template<>
class FutureState<void> : public State {
public:

    friend class Promise<void>;
    friend class Future<void>;

};

template<typename T>
class FutureState<T &> : public State {
  public:
    friend class Promise<T &>;
    friend class Future<T &>;

  private:
    T *value;
};

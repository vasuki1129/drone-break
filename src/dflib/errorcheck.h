#pragma once
#include "../dflib/cppmatch.h"
#include <variant>
#include <string>
#include <iostream>
struct _implErr {
  std::string error_message;
  _implErr* chain;
  _implErr(std::string error_message, _implErr* chain) {
    this->error_message = error_message;
    this->chain = chain;
  }
  _implErr(std::string error_message) {
    this->error_message = error_message;
    this->chain = nullptr;
  }
  ~_implErr() {
    delete this->chain;
  }
};

template <typename T>
struct _implOk {
    T val;
    _implOk(T val) {
      this->val = val;
    }
};

template <typename T>
using Error = std::variant<_implErr*, _implOk<T>*>;

template <typename T>
void ErrTrace(Error<T> err) // prints the error trace
{

  _implErr* cur = std::get<_implErr*>(err);
  int i = 0;
  while (cur != nullptr) {
    for (int c = 0; c < i; c++) {
      std::cout << "-";
    }
    std::cout << cur->error_message << "\n";
    cur = cur->chain;
  }
  delete std::get<_implErr*>(err);
}

template <typename T>
void ErrIgnore(Error<T> err) //deallocates the err stack but does nothing
{
  match {
    mcase(_implErr *){
       delete val;

    },
    mcase(_implOk<T> *) {
       delete val;
    }
  } eval_on(err);
}

template <typename T> Error<T> MakeOk(T value) {
  return new _implOk<T>(value);
}

template <typename T> Error<T> MakeErr(std::string message, _implErr* chain) {
  return new _implErr(message, chain);

}

template <typename T> Error<T> MakeErr(std::string message) {
  return new _implErr(message, nullptr);

}

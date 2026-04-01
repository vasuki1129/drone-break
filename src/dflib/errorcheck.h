#pragma once
#include <variant>
#include <string>
struct Err {
  std::string error_message;
  Err(std::string error_message) {
    this->error_message = error_message;

  }
};

template <typename T>
struct Ok {
    T val;
    Ok(T val) {
      this->val = val;
    }
};
template <typename T>
using Error = std::variant<Err, Ok<T>>;

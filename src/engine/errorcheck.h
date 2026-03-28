#pragma once
#include <variant>
#include <string>
struct Err {
    std::string error_message;
};
struct Ok {
    int val;
};

using Error = std::variant<Err, Ok>;

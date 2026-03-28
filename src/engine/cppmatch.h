//copyright 2025 deepfrog@deepfrog.org
//CPPMATCH
//adds a rust style variant matching syntactic construct
//in the form of the `match` keyword.
//AS A RESULT, ANY CODE THAT INCLUDES THIS FILE MUST TREAT `match`, `on`
//AND `mcase` AS RESERVED WORDS
//
//THIS BREAKS C++ STANDARD, THIS IS BY DESIGN, FUCK THE STANDARD
#pragma once
#include <variant>
#include <iostream>

template<class... Ts>
struct overload : Ts... {
    using Ts::operator()...;
};
template<class... Ts>
overload(Ts...) -> overload<Ts...>;

#define match {auto visitor = overload
#define on(x) ;auto _a = x;std::visit(visitor,_a);}
#define mcase(v) [this](v& val)

//usage example
/*
int main() {
  std::variant<int, float> message;
  message = 2.0f;

  match {
    mcase(float) { std::cout << val << "\n"; },
    mcase(int)   { std::cout << "Integers not supported." << "\n";},
  } on(message);

  mcase() captures `this`, so you can access class members just as you would normally

  the `x` in on(x) must be a std::variant type

  the value of the match is always stored in the variable `val`
  within mcases
}
*/

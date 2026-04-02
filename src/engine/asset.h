#pragma once


namespace engine {


class Asset {
public:
  virtual bool IsValid();
protected:
  bool valid = false;
};



}

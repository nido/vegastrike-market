#include "Economy.hpp"

Economy::Economy() : bases(std::vector<Base>()) {}

Economy::~Economy() {}

void Economy::addBase(const Base& base) { this->bases.push_back(base); }

void Economy::delBase(const Base& base) {
  for (std::vector<Base>::iterator iter = this->bases.begin();
       iter != this->bases.end(); ++iter) {
    if (base == *iter) {
      this->bases.erase(iter);
      break;
    }
  }
}

const std::vector<Base>& Economy::getBases() { return this->bases; }

void Economy::tick() {
  for (std::vector<Base>::iterator iter = this->bases.begin();
       iter != this->bases.end(); ++iter) {
    iter->Process();
  }
}

#include "Economy.hpp"

Economy::Economy() : bases(std::vector<Base>()) {}

Economy::~Economy() {}

void Economy::addBase(const Base &base) { this->bases.push_back(base); }

void Economy::delBase(const Base &base) {
  for (std::vector<Base>::iterator iter = this->bases.begin();
       iter != this->bases.end(); ++iter) {
    if (base == *iter) {
      this->bases.erase(iter);
      break;
    }
  }
}

const std::vector<Base> &Economy::getBases() { return this->bases; }

void Economy::tick() {
  for (std::vector<Base>::iterator iter = this->bases.begin();
       iter != this->bases.end(); ++iter) {
    iter->Process();
  }
}

void Economy::preallocate(unsigned int x) { this->bases.reserve(x); }

bool Economy::operator==(const Economy &that) const {
  return (this->bases == that.bases);
}

std::vector<Base>::const_iterator Economy::begin() const {
  return this->bases.begin();
}
std::vector<Base>::const_iterator Economy::end() const {
  return this->bases.end();
}

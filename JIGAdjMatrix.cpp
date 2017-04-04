// JIGAdjMatrix.cpp
// Ryan Stonebraker
// 4/1/2017
// adjacency matrix definition

#include "JIGAdjMatrix.h"
#include <stdexcept>
using namespace JIG;

JIG::Adjacent::Adjacent() : _editable{true} {}

JIG::Adjacent::Adjacent(std::unordered_map<std::string, unsigned> complete)
    : _complete{complete}, _editable{true} {}

void JIG::Adjacent::addEdge(std::string identifier, unsigned edges) {
  if (!this->_editable)
    throw std::runtime_error{"void JIG::Adjacent::addEdge(std::string "
                             "identifier, unsigned edges), cannot add edge "
                             "after complete map is created."};
  this->_complete.insert({identifier, edges});
}

void JIG::Adjacent::revokeAdding() { this->_editable = false; }

void JIG::Adjacent::removeEdge(std::string identifier) {
  this->_complete.erase(identifier);
}
void JIG::Adjacent::removeEdge(std::string identifier, unsigned edges) {
  if (this->_complete[identifier] <= edges)
    this->_complete.erase(identifier);
  else
    this->_complete[identifier] -= edges;
}

JIG::Adjacent::operator bool() const { return (_complete.empty()); }

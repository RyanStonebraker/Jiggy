// JIGAdjMatrix.h
// Ryan Stonebraker
// 4/1/2017
// Adjacency Matrix header

#ifndef JIGADJMATRIX_H
#define JIGADJMATRIX_H

#include <string>
#include <unordered_map>

namespace JIG {

class Adjacent {
public:
  operator bool() const;

  Adjacent();
  Adjacent(std::unordered_map<std::string, unsigned> complete);

  void addEdge(std::string identifier, unsigned edges);
  void addEdge(std::string identifier, unsigned edges, bool permissions);
  void removeEdge(std::string identifier);
  void removeEdge(std::string identifier, unsigned edges);
  void revokeAdding();

private:
  std::unordered_map<std::string, unsigned> _complete;
  bool _editable; // throw error if false
};

} // namespace JIG

#endif

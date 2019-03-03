#ifndef __INT_MATRIX_H___
#define __INT_MATRIX_H___
#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>
using namespace ::std;
template<typename T>
class Matrix
{
 private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(0) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(r, vector<T>(c)) {}
  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(rhs.rows) {}
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  Matrix & operator=(const Matrix<T> & rhs) {
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
    return *this;
  }
  const vector<T> & operator[](int index) const {
    assert(index < numRows);
    return rows[index];
  }
  vector<T> & operator[](int index) {
    assert(index < numRows);
    return rows[index];
  }
  bool operator==(const Matrix<T> & rhs) const {
    return numRows == rhs.numRows && numColumns == rhs.numColumns && rows == rhs.rows;
  }
  Matrix operator+(const Matrix & rhs) const {
    Matrix sum = Matrix(this->numRows, this->numColumns);
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        sum[i][j] = (*this)[i][j] + rhs[i][j];
      }
    }
    return sum;
  }
  template<typename U>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & rhs);
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  /* s << "[";
  for (typename std::vector<vector<T> >::iterator it = rhs.rows.begin(); it != rhs.rows.end();
       ++it) {
    if (it != rhs.rows.begin()) {
      s << ",\n{";
    }
    else {
      s << "{";
    }
    for (typename std::vector<T>::iterator ij = it->begin(); ij != it->end(); ++ij) {
      if (ij != it->begin()) {
        s << ", ";
      }
      s << *ij;
    }
    s << "}";
  }
  return s;*/
  s << "[ ";
  for (int i = 0; i < rhs.numRows; i++) {
    s << "{";
    for (int j = 0; j < rhs.numColumns; j++) {
      s << rhs.rows[i][j];
      if (j < rhs.numColumns - 1) {
        s << ", ";
      }
    }
    s << "}";
    if (i < rhs.numRows - 1) {
      s << ",\n";
    }
  }
  s << " ]";
  return s;
}

#endif

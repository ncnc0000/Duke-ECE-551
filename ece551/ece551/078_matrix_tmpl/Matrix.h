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
  vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}
  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new vector<T> *[r]) {
    for (int i = 0; i < r; i++) {
      rows[i] = new vector<T>(c);
    }
  }
  Matrix(const Matrix<T> & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new vector<T> *[rhs.numRows]) {
    for (int i = 0; i < numRows; i++) {
      rows[i] = new vector<T>(rhs.numColumns);
    }
    for (int i = 0; i < numRows; i++) {
      for (int j = 0; j < numColumns; j++) {
        (*rows[i])[j] = (*rhs.rows[i])[j];
      }
    }
  }
  ~Matrix() {
    for (int i = 0; i < this->numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
  }
  Matrix & operator=(const Matrix<T> & rhs) {
    if (*this == rhs) {
      return *this;
    }
    else {
      for (int i = 0; i < numRows; i++) {
        delete rows[i];
      }
      delete[] rows;
      numRows = rhs.numRows;
      numColumns = rhs.numColumns;
      rows = new vector<T> *[rhs.numRows]();
      for (int i = 0; i < numRows; i++) {
        rows[i] = new vector<T>(rhs.numColumns);
      }
      for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numColumns; j++) {
          (*rows[i])[j] = (*rhs.rows[i])[j];
        }
      }
    }
    return *this;
  }
  int getRows() const { return numRows; }
  int getColumns() const { return numColumns; }
  const vector<T> & operator[](int index) const {
    assert(index < numRows);
    return *rows[index];
  }
  vector<T> & operator[](int index) {
    assert(index < numRows);
    return *rows[index];
  }
  bool operator==(const Matrix<T> & rhs) const {
    if (numColumns != rhs.numColumns || numRows != rhs.numRows) {
      return false;
    }
    for (int i = 0; i < rhs.numRows; i++) {
      if (*rows[i] != rhs[i]) {
        return false;
      }
    }
    return true;
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
  s << "[ ";
  for (int i = 0; i < rhs.numRows; i++) {
    s << "{";
    for (int j = 0; j < rhs.numColumns; j++) {
      s << (*rhs.rows[i])[j];
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

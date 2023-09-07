//
// Created by Timofey on 22.08.2023.
//

#ifndef _S21_MATRIX_OOP_H_
#define _S21_MATRIX_OOP_H_

#include <algorithm>
#include <stdexcept>
#include <utility>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double* matrix_;   // pointer to the memory where the matrix will be allocated
  void Free() noexcept;

 public:
  S21Matrix() noexcept;                   // default constructor
  S21Matrix(int rows, int cols);          // parameterized constructor
  S21Matrix(const S21Matrix& other);      // copy constructor
  S21Matrix(S21Matrix&& other) noexcept;  // move constructor
  ~S21Matrix() noexcept;                  // destructor

  // some operators overloads
  S21Matrix& operator=(const S21Matrix& other);  // assignment operator overload
  double& operator()(int row, int col) const;    // index
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other) const;
  bool operator==(const S21Matrix& other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator*(const double num) const;
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);

  // some public methods
  int GetRows() const noexcept;
  int GetCols() const noexcept;
  void SetRows(int new_rows);
  void SetCols(int new_cols);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);

  friend S21Matrix operator*(const double num,
                             const S21Matrix& matrix) noexcept;

  void print_matrix() noexcept;
  void default_matrix() noexcept;

  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  S21Matrix get_minor(int row, int column) const;
};

#endif  // _S21_MATRIX_OOP_H_

#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    throw std::logic_error("The size of the matrix can't be less then 0.");
  }
  matrix_ = new double[rows_ * cols_]();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double[rows_ * cols_]();
  std::copy(other.matrix_, other.matrix_ + rows_ * cols_, matrix_);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

void S21Matrix::default_matrix() noexcept {
  int k = 1;
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      (*this)(i, j) = k;
      ++k;
    }
  }
}

double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || col < 0 || row >= rows_ || col >= cols_) {
    throw std::out_of_range("Index is out of range");
  }
  return matrix_[row * cols_ + col];
}

int S21Matrix::GetRows() const noexcept { return rows_; }
int S21Matrix::GetCols() const noexcept { return cols_; }

void S21Matrix::SetRows(int new_rows) {
  if (new_rows < 0) {
    throw std::logic_error("The size of the row must be greater than zero.");
  }
  if (rows_ != new_rows) {
    S21Matrix temp(new_rows, cols_);
    int min_rows = std::min(rows_, new_rows);
    for (int i = 0; i != min_rows; ++i) {
      for (int j = 0; j != cols_; ++j) {
        temp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(temp);
  }
}

void S21Matrix::SetCols(int new_cols) {
  if (new_cols < 0) {
    throw std::logic_error("The size of the column must be greater than zero.");
  }
  if (cols_ != new_cols) {
    int min_cols = std::min(new_cols, cols_);
    S21Matrix temp(rows_, new_cols);
    for (int i = 0; i != rows_; ++i) {
      for (int j = 0; j != min_cols; ++j) {
        temp(i, j) = (*this)(i, j);
      }
    }
    *this = std::move(temp);
  }
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(
        "Summation matrices must \
        have the same dimensions");
  }
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      (*this)(i, j) += other(i, j);
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error(
        "The matrices to be \
        subtracted must be of the same size.");
  }
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      (*this)(i, j) -= other(i, j);
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      (*this)(i, j) *= num;
    }
  }
}

void S21Matrix::Free() noexcept {
  delete[] matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::~S21Matrix() noexcept { Free(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i != rows_; ++i) {
    for (int j = 0; j != cols_; ++j) {
      if (std::abs((*this)(i, j) - other(i, j)) > 0.0000001) {
        return false;
      }
    }
  }
  return true;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  S21Matrix new_matrix(other);
  *this = std::move(new_matrix);
  return *this;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::logic_error(
        "The number of columns of \
        the first matrix must be equal to \
        the number of rows of the second matrix");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i != result.GetRows(); ++i) {
    for (int j = 0; j != result.GetCols(); ++j) {
      for (int k = 0; k != cols_; ++k) {
        result(i, j) += (*this)(i, k) * other(k, j);
      }
    }
  }
  *this = std::move(result);
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i != result.GetRows(); ++i) {
    for (int j = 0; j != result.GetCols(); ++j) {
      result(i, j) = (*this)(j, i);
    }
  }
  return result;
}

S21Matrix S21Matrix::get_minor(int row, int column) const {
  int result_row = 0;
  int result_column = 0;
  S21Matrix result_matrix(rows_ - 1, cols_ - 1);
  for (int i = 0; i != rows_; ++i) {
    if (i != row) {
      result_column = 0;
      for (int j = 0; j != cols_; ++j) {
        if (j != column) {
          result_matrix(result_row, result_column) = (*this)(i, j);
          ++result_column;
        }
      }
      ++result_row;
    }
  }
  return result_matrix;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::logic_error(
        "To calculate the determinant, the matrix must be square.");
  }
  if (rows_ == 1) {
    return (*this)(0, 0);
  }
  if (rows_ == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
  }
  double result = 0.0;
  for (int j = 0; j != cols_; ++j) {
    S21Matrix temp(rows_ - 1, cols_ - 1);
    temp = get_minor(0, j);
    if (j % 2) {
      result -= (*this)(0, j) * temp.Determinant();
    } else {
      result += (*this)(0, j) * temp.Determinant();
    }
    temp.Free();
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::logic_error(
        "To calculate the calc complements, the matrix must be square.");
  }
  S21Matrix result(rows_, cols_);
  double sign = 1;
  for (int i = 0; i != result.GetRows(); ++i) {
    for (int j = 0; j != result.GetCols(); ++j) {
      S21Matrix minor = get_minor(i, j);
      double det_minor = minor.Determinant();
      result(i, j) = sign * det_minor;
      minor.Free();
      sign *= -1;
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() const {
  S21Matrix result(rows_, cols_);
  double det_A = Determinant();
  if (std::abs(det_A) < 0.0000001) {
    throw std::logic_error("The matrix determinant can't be 0");
  }
  result = CalcComplements().Transpose() * (1 / det_A);
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.SumMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.SubMatrix(other);
  return temp;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix temp(*this);
  temp.MulMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(const double num) const {
  S21Matrix temp(*this);
  temp.MulNumber(num);
  return temp;
}
S21Matrix operator*(const double num, const S21Matrix& matrix) noexcept {
  S21Matrix temp = matrix * num;
  return temp;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

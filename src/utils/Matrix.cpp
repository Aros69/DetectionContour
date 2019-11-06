#include <opencv2/imgcodecs.hpp>
#include <values.h>
#include "Matrix.h"

Matrix::Matrix(unsigned int _row, unsigned int _column)
    : row(_row), column(_column) {
  matrix = new double[_row * _column];
}

Matrix::Matrix(const cv::Mat_<double> &m) {
  row = m.rows;
  column = m.cols;
  matrix = new double[m.rows * m.cols];
  for (int i = 0; i < m.rows; ++i) {
    for (int j = 0; j < m.cols; ++j) {
      setMatrixValue(i, j, m(i, j));
    }
  }
}

Matrix::~Matrix() {
  delete[]matrix;
  matrix = nullptr;
}

cv::Mat_<uchar> Matrix::convertToOpenCvMat() const {
  cv::Mat_<uchar> res(row, column);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      res(i, j) = getMatrixValue(i, j);
    }
  }
  return res;
}

void Matrix::setMatrixValue(unsigned int _row, unsigned int _column,
                            double value) {
  if (inMatrixSize(_row, _column)) {
    matrix[_row * column + _column] = value;
  } else {
    fprintf(stderr, "(%d, %d) is out of matrix Bound\n", _row, _column);
  }
}

double Matrix::getMatrixValue(unsigned int _row, unsigned int _column) const {
  if (inMatrixSize(_row, _column)) {
    return matrix[_row * column + _column];
  } else {
    fprintf(stderr, "(%d, %d) is out of matrix Bound\n", _row, _column);
    return 0;
  }
}

double Matrix::getValueOfQuantileX(int quantile) const {
  int resolution = nbRow() * nbCol();
  std::vector<int> values(floor(max() + 1), 0);
  if (quantile >= 100) {
    quantile = 50;
  }
  int nbOfValueToSkip = double(resolution * quantile) / 100.0;
  double thresholdValue = 0;
  // Define Threshold Value
  for (int i = 0; i < nbRow(); ++i) {
    for (int j = 0; j < nbCol(); ++j) {
      values[floor(getMatrixValue(i, j))]++;
    }
  }
  int cpt = 0, i = 0;
  while (cpt < nbOfValueToSkip && i < floor(max() + 1)) {
    cpt += values[i];
    ++i;
  }
  return i;
}

double Matrix::max() const {
  double res = MINDOUBLE;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      if (getMatrixValue(i, j) > res) {
        res = getMatrixValue(i, j);
      }
    }
  }
  return res;
}

double Matrix::min() const {
  double res = MAXDOUBLE;
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      if (getMatrixValue(i, j) < res) {
        res = getMatrixValue(i, j);
      }
    }
  }
  return res;
}

Matrix *Matrix::createSubMatrix(int beginRow, int endRow, int beginColumn,
                                int endColumn) const {
  Matrix *res = new Matrix(endRow - beginRow, endColumn - beginColumn);
  /*std::cout << "begR : " << beginRow << " endR :" << endRow << " begC :" << beginColumn
            << " endC :" << endColumn << "\n";*/
  for (int i = 0; i < endRow - beginRow; ++i) {
    for (int j = 0; j < endColumn - beginColumn; j++) {
      if (inMatrixSize(beginRow + i, beginColumn + j)) {
        res->setMatrixValue(i, j, getMatrixValue(beginRow + i, beginColumn + j));
      } else {
        res->setMatrixValue(i, j, 0);
      }
    }
  }
  return res;
}

Matrix Matrix::rotateClockwise90() const {
  Matrix res(column, row);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      res.setMatrixValue(j, i, getMatrixValue(i, j));
    }
  }
  return res;
}

Matrix *Matrix::addMatrix(const Matrix &m) const {
  if (row == m.nbRow() && column == m.nbRow()) {
    Matrix *res = new Matrix(row, column);
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < column; j++) {
        res->setMatrixValue(i, j, getMatrixValue(i, j) + m.getMatrixValue(i, j));
      }
    }
    return res;
  } else {
    fprintf(stderr, "Matrix should have the same size\n");
    return new Matrix();
  }
}

Matrix *Matrix::addFactor(double &x) const {
  Matrix *res = new Matrix(row, column);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; j++) {
      res->setMatrixValue(i, j, getMatrixValue(i, j) + x);
    }
  }
  return res;
}

Matrix *Matrix::multMatrix(const Matrix &m) const {

}

Matrix *Matrix::multMatrix(const double &factor) const {
  //print();
  Matrix *res = new Matrix(row, column);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; j++) {
      res->setMatrixValue(i, j, getMatrixValue(i, j) * factor);
    }
  }
  //res.print();
  return res;
}

Matrix *Matrix::multP2PMatrix(const Matrix &m) const {
  if (row == m.nbRow() && column == m.nbRow()) {
    Matrix *res = new Matrix(row, column);
    for (int i = 0; i < row; ++i) {
      for (int j = 0; j < column; j++) {
        res->setMatrixValue(i, j, getMatrixValue(i, j) * m.getMatrixValue(i, j));
      }
    }
    //res->print();
    return res;
  } else {
    fprintf(stderr, "Matrix should have the same size\n");
    return new Matrix();
  }
}

double Matrix::sumMat() const {
  double res = 0;
  for (int i = 0; i < nbRow(); ++i) {
    for (int j = 0; j < nbCol(); ++j) {
      res += getMatrixValue(i, j);
    }
  }
  return res;
}

void Matrix::print() const {
  printf("Matrix with %d rows, %d columns\n", row, column);
  for (unsigned int i = 0; i < row; i++) {
    printf("Line %d : (", i);
    for (unsigned int j = 0; j < column; j++) {
      if (j != column - 1) { std::cout << getMatrixValue(i, j) << ", "; }
      else { std::cout << getMatrixValue(i, j) << ")" << std::endl; }
    }
  }
}
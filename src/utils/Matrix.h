#ifndef TP1_ANALYSEIMAGE_MATRIX_H
#define TP1_ANALYSEIMAGE_MATRIX_H

#include <cstdio>
#include <iostream>
#include <opencv2/core/core.hpp>
// Reminder : Matrix[x][y] == Matrix[x*SizeY+y]

class Matrix {
protected:
  double *matrix;
  unsigned int row;
  unsigned int column;
public:
  Matrix() : Matrix(1, 1) {};

  Matrix(unsigned int _row, unsigned int _column);

  Matrix(const cv::Mat_<double> &m);

  ~Matrix();

  cv::Mat_<uchar> convertToOpenCvMat() const;

  bool inMatrixSize(unsigned int _row, unsigned int _column) const {
    return _row >= 0 && _row < row && _column >= 0 && _column < column;
  }

  unsigned int nbRow() const { return row; }

  unsigned int nbCol() const { return column; }

  void setMatrixValue(unsigned int _row, unsigned int _column, double value);

  double getMatrixValue(unsigned int _row, unsigned int _column) const;

  double getValueOfQuantileX(int quantile) const;

  double max() const;

  double min() const;

  Matrix *createSubMatrix(int beginRow, int endRow, int beginColumn,
                          int endColumn) const;

  Matrix rotateClockwise90() const;

  Matrix *addMatrix(const Matrix &m) const;

  Matrix *addFactor(double &x) const;

  Matrix *multMatrix(const Matrix &m) const;

  Matrix *multMatrix(const double &factor) const;

  Matrix *multP2PMatrix(const Matrix &m) const;

  double sumMat() const;

  virtual void print() const;
};


#endif //TP1_ANALYSEIMAGE_MATRIX_H

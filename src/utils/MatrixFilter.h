#ifndef TP1_ANALYSEIMAGE_MATRIXFILTER_H
#define TP1_ANALYSEIMAGE_MATRIXFILTER_H

#include <cstdio>
#include <climits>
#include "Matrix.h"

// Reminder : MatrixFilter[x][y] == MatrixFilter[x*SizeY+y]

class MatrixFilter : public Matrix {
private:
  double matrixFactor;

public:
  MatrixFilter() : Matrix(1, 1), matrixFactor(1) {};

  MatrixFilter(unsigned int _row, unsigned int _column)
      : MatrixFilter(_row, _column, 1) {};

  MatrixFilter(unsigned int row, unsigned int _column, double _matrixFactor);

  MatrixFilter(const Matrix &m);

  double getMatrixFactor() const { return matrixFactor; }

  void setMatrixFactor(double _factor) { matrixFactor = _factor; }

  MatrixFilter rotateClockwise90() const;

  static MatrixFilter moyenneur(unsigned int _row, unsigned int _column);

  static MatrixFilter prewitt(bool rotate45deg);

  static MatrixFilter sobel(bool rotate45deg);

  static MatrixFilter kirsch(bool rotate45deg);

  static MatrixFilter
  gaussian_blur_kernel_2d(unsigned int _row, unsigned int _column, double sigma);

  void print() const;
};


#endif //TP1_ANALYSEIMAGE_MATRIXFILTER_H

#include "MatrixFilter.h"

MatrixFilter::MatrixFilter(unsigned int _row, unsigned int _column,
                           double _matrixFactor)
    : matrixFactor(_matrixFactor) {
  row = _row;
  column = _column;
  if (_row % 2 != 1 || _column % 2 != 1) {
    fprintf(stderr,
            "Warning : You are creating an even filter, result can be unpredictble\n");
  }
  matrix = new double[_row * _column];
}

MatrixFilter::MatrixFilter(const Matrix &m) {
  row = m.nbRow();
  column = m.nbCol();
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; j++) {
      setMatrixValue(i, j, m.getMatrixValue(i, j));
    }
  }
  if (row % 2 != 1 || column % 2 != 1) {
    fprintf(stderr,
            "Warning : You are creating an even filter, result can be unpredictble\n");
  }
}

MatrixFilter MatrixFilter::rotateClockwise90() const {
  MatrixFilter res(column, row, getMatrixFactor());
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < column; ++j) {
      res.setMatrixValue(j, i, getMatrixValue(i, j));
    }
  }
  return res;
}

MatrixFilter MatrixFilter::moyenneur(unsigned _row, unsigned int _column) {
  MatrixFilter res(_row, _column, 1.0 / (_row * _column));
  for (unsigned int i = 0; i < _row; i++) {
    for (unsigned int j = 0; j < _column; j++) {
      res.setMatrixValue(i, j, 1);
    }
  }
  return res;
}

MatrixFilter MatrixFilter::prewitt(bool rotate45deg) {
  MatrixFilter res(3, 3, 1);
  if (!rotate45deg) {
    for (int i = 0; i < 3; ++i) {
      res.setMatrixValue(i, 0, -1);
      res.setMatrixValue(i, 1, 0);
      res.setMatrixValue(i, 2, 1);
    }
  } else {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (j == i) {
          res.setMatrixValue(i, j, 0);
        } else if (j > i) {
          res.setMatrixValue(i, j, 1);
        } else {
          res.setMatrixValue(i, j, -1);
        }
      }
    }
  }
  res.setMatrixFactor(1.0/3.0);
  return res;
}

MatrixFilter MatrixFilter::sobel(bool rotate45deg) {
  MatrixFilter res = MatrixFilter::prewitt(rotate45deg);
  if (!rotate45deg) {
    res.setMatrixValue(1, 0, -2);
    res.setMatrixValue(1, 2, 2);
  } else {
    res.setMatrixValue(2, 0, -2);
    res.setMatrixValue(0, 2, 2);
  }
  res.setMatrixFactor(1.0/3.0);
  return res;
}

MatrixFilter MatrixFilter::kirsch(bool rotate45deg) {
  MatrixFilter res(3, 3, 1);
  if (!rotate45deg) {
    for (int i = 0; i < 3; ++i) {
      res.setMatrixValue(i, 0, -3);
      res.setMatrixValue(i, 2, 5);
      if (i == 1) {
        res.setMatrixValue(i, 1, 0);
      } else {
        res.setMatrixValue(i, 1, -3);
      }
    }
  } else {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        if (j == 1 && i == 1) {
          res.setMatrixValue(i, j, 0);
        } else if (j > i) {
          res.setMatrixValue(i, j, 5);
        } else {
          res.setMatrixValue(i, j, -3);
        }
      }
    }
  }
  res.setMatrixFactor(1.0/15.0);
  return res;
}

MatrixFilter
MatrixFilter::gaussian_blur_kernel_2d(unsigned int _row, unsigned int _column,
                                      double sigma) {
  MatrixFilter res(_row, _column);
  double totSum = 0;
  for (int i = 0; i < _row; ++i) {
    for (int j = 0; j < _column; ++j) {
      int x = i - floor(double(_row - 1) / 2);
      int y = j - floor(double(_column - 1) / 2);
      //std::cout << x << " " << y << std::endl;
      double t =
          (1.0 / 2.0 * M_PI * sigma * sigma) *
          exp(-float(x * x + y * y) / 2 * sigma * sigma);
      res.setMatrixValue(i, j, t);
      totSum += t;
    }
  }
  if (_row % 2 != 1 || _column % 2 != 1) {
    fprintf(stderr,
            "Warning : You are creating an even filter, result can be unpredictble\n");
  }
  res.setMatrixFactor(1.0 / totSum);
  return res;
}

void MatrixFilter::print() const {
  printf("Filter with %d rows, %d columns and matrix factor %f\n", row, column,
         matrixFactor);
  for (unsigned int i = 0; i < row; i++) {
    printf("Line %d : (", i);
    for (unsigned int j = 0; j < column; j++) {
      if (j != column - 1) { std::cout << getMatrixValue(i, j) << ", "; }
      else { std::cout << getMatrixValue(i, j) << ")" << std::endl; }
    }
  }
}
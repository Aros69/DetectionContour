#ifndef TP1_ANALYSEIMAGE_COMPUTATIONS_H
#define TP1_ANALYSEIMAGE_COMPUTATIONS_H

#include <opencv2/core/core.hpp>

#include "utils/MatrixFilter.h"

class Computations {
public:
  static Matrix convolve_2d(const Matrix &matrix, const MatrixFilter &filter);

  static std::vector<Matrix *>
  convolve_2d_bidirectionnal(const Matrix &matrix, const MatrixFilter &filter);

  static std::vector<Matrix *>
  convolve_2d_quadridirectionnal(const Matrix &matrix, const MatrixFilter &filter1,
                                 const MatrixFilter &filter2);

  static Matrix postTGlobalThreshold(const Matrix &matrix, int quantile);

  static Matrix postTLocalThreshold(const Matrix &matrixn, int quantile);

  static Matrix postTHysteresisThreshold(const Matrix &matrix, int quantile);

  static Matrix edgeRefinement(std::vector<Matrix *> matrixes);
};

#endif //TP1_ANALYSEIMAGE_COMPUTATIONS_H

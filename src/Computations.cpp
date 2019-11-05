#include <iostream>
#include "Computations.h"

Matrix
Computations::convolve_2d(const Matrix &image, const MatrixFilter &filter) {
  Matrix res(image.nbRow(), image.nbCol());
  for (int i = 0; i < image.nbRow(); ++i) {
    for (int j = 0; j < image.nbCol(); ++j) {
      res.setMatrixValue(i, j, 0);
      Matrix *subMat = image.createSubMatrix(floor(i - double(filter.nbRow() / 2)),
                                             floor(i + double(filter.nbRow() / 2)) +
                                             1,
                                             floor(j - double(filter.nbCol() / 2)),
                                             floor(j + double(filter.nbCol() / 2)) +
                                             1);
      Matrix *sM = subMat->multP2PMatrix(filter);
      Matrix *t = sM->multMatrix(filter.getMatrixFactor());
      res.setMatrixValue(i, j, t->sumMat());
      delete subMat;
      delete sM;
      delete t;
    }
  }
  //res.print();
  return res;
}

std::vector<Matrix *> Computations::convolve_2d_bidirectionnal(const Matrix &matrix,
                                                               const MatrixFilter &filter) {
  std::vector<Matrix *> res(3);
  res[0] = new Matrix(matrix.nbRow(), matrix.nbCol());
  res[1] = new Matrix(Computations::convolve_2d(matrix, filter));
  res[2] = new Matrix(Computations::convolve_2d(matrix, filter.rotateClockwise90()));
  /* Matrix dirX = Computations::convolve_2d(matrix, filter);
   Matrix dirY = Computations::convolve_2d(matrix, filter.rotateClockwise90());
   Matrix res(matrix.nbRow(), matrix.nbCol());*/
  // Calcul du module/norme du gradient
  for (int i = 0; i < res[0]->nbRow(); ++i) {
    for (int j = 0; j < res[0]->nbCol(); ++j) {
      res[0]->setMatrixValue(i, j, sqrt(
          pow(res[1]->getMatrixValue(i, j), 2) +
          pow(res[2]->getMatrixValue(i, j), 2)));
    }
  }
  return res;
}

std::vector<Matrix *> Computations::convolve_2d_quadridirectionnal(const Matrix &matrix,
                                                                   const MatrixFilter &filter1,
                                                                   const MatrixFilter &filter2) {
  std::vector<Matrix *> res(5);
  res[0] = new Matrix(matrix.nbRow(), matrix.nbCol());
  res[1] = new Matrix(Computations::convolve_2d(matrix, filter1));
  res[2] = new Matrix(Computations::convolve_2d(matrix, filter1.rotateClockwise90()));
  res[3] = new Matrix(Computations::convolve_2d(matrix, filter2));
  res[4] = new Matrix(Computations::convolve_2d(matrix, filter2.rotateClockwise90()));
  // Calcul du module/norme du gradient
  for (int i = 0; i < res[0]->nbRow(); ++i) {
    for (int j = 0; j < res[0]->nbCol(); ++j) {
      res[0]->setMatrixValue(i, j, sqrt(
          pow(res[1]->getMatrixValue(i, j), 2)
          + pow(res[2]->getMatrixValue(i, j), 2)
          + pow(res[3]->getMatrixValue(i, j), 2)
          + pow(res[4]->getMatrixValue(i, j), 2)));
    }
  }
  return res;
}

Matrix Computations::postTGlobalThreshold(const Matrix &matrix, int quantileValue) {
  Matrix res(matrix.nbRow(), matrix.nbCol());
  std::vector<int> values(floor(matrix.max() + 1), 0);
  int resolution = matrix.nbRow() * matrix.nbCol();
  if(quantileValue>=100){
    quantileValue = 85;
  }
  int nbOfValueToSkip = double(resolution * quantileValue) / 100.0;
  double thresholdValue = 0;
  // Define Threshold Value
  for (int i = 0; i < res.nbRow(); ++i) {
    for (int j = 0; j < res.nbCol(); ++j) {
      values[floor(matrix.getMatrixValue(i, j))]++;
    }
  }
  int cpt = 0, i = 0;
  while (cpt < nbOfValueToSkip && i < floor(matrix.max() + 1)) {
    cpt+=values[i];
    ++i;
  }
  thresholdValue = i;
  // Computation of the post treatment
  for (int i = 0; i < res.nbRow(); ++i) {
    for (int j = 0; j < res.nbCol(); ++j) {
      if (matrix.getMatrixValue(i, j) < thresholdValue) {
        res.setMatrixValue(i, j, 0);
      } else {
        res.setMatrixValue(i, j, matrix.getMatrixValue(i, j));
      }
    }
  }
  return res;
}

Matrix
Computations::postTLocalThreshold(const Matrix &matrix, unsigned int neighborhoodSize) {

}

Matrix Computations::postTHysteresisThreshold(const Matrix &matrix) {}
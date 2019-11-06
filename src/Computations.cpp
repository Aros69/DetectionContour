#include <iostream>
#include <values.h>
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

Matrix Computations::postTGlobalThreshold(const Matrix &matrix, int quantile) {
  Matrix res(matrix.nbRow(), matrix.nbCol());
  double thresholdValue = matrix.getValueOfQuantileX(quantile);
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
Computations::postTLocalThreshold(const Matrix &matrix, int quantile) {
  Matrix res(matrix.nbRow(), matrix.nbCol());
  // Computation of the post treatment
  for (int i = 0; i < res.nbRow(); ++i) {
    for (int j = 0; j < res.nbCol(); ++j) {
      Matrix *subMat = matrix.createSubMatrix(i - 1, i + 2, j - 1, j + 2);
      double thresholdValue = subMat->getValueOfQuantileX(quantile);
      if (matrix.getMatrixValue(i, j) < thresholdValue) {
        res.setMatrixValue(i, j, 0);
      } else {
        res.setMatrixValue(i, j, matrix.getMatrixValue(i, j));
      }
      delete (subMat);
    }
  }
  return res;
}

Matrix Computations::postTHysteresisThreshold(const Matrix &matrix, int quantile) {
  Matrix res(matrix.nbRow(), matrix.nbCol());
  double thresholdMin, thresholdMax;
  thresholdMax = matrix.getValueOfQuantileX(quantile);
  thresholdMin = thresholdMax * 0.7;
  // Computation of the post treatment
  for (int i = 0; i < res.nbRow(); ++i) {
    for (int j = 0; j < res.nbCol(); ++j) {
      if (matrix.getMatrixValue(i, j) < thresholdMin) {
        res.setMatrixValue(i, j, 0);
      } else if (matrix.getMatrixValue(i, j) > thresholdMax) {
        res.setMatrixValue(i, j, matrix.getMatrixValue(i, j));
      } else {
        bool hadGoodNeighboor = false;
        for (int k = i - 1; k <= i + 1; ++k) {
          for (int l = j - 1; l <= j + 1; ++l) {
            if (matrix.getMatrixValue(k, l) > thresholdMax) {
              hadGoodNeighboor = true;
            }
          }
        }
        if (hadGoodNeighboor) {
          res.setMatrixValue(i, j, matrix.getMatrixValue(i, j));
        } else {
          res.setMatrixValue(i, j, 0);
        }
      }
    }
  }
  return res;
}

Matrix Computations::edgeRefinement(std::vector<Matrix *> matrixes) {
  Matrix res(matrixes[0]->nbRow(), matrixes[0]->nbCol());
  for (int i = 0; i < res.nbRow(); ++i) {
    for (int j = 0; j < res.nbRow(); ++j) {
      res.setMatrixValue(i, j, 0);
    }
  }
  if (matrixes.size() > 2) {
    // Gradient en x
    for (int i = 0; i < matrixes[1]->nbRow(); ++i) {
      int j = 0;
      while (j < matrixes[1]->nbCol()) {
        if (matrixes[1]->getMatrixValue(i, j) != 0) {
          int indexLocalMax = j;
          while (j < matrixes[1]->nbCol() && matrixes[1]->getMatrixValue(i, j) != 0) {
            if (matrixes[1]->getMatrixValue(i, j) >
                matrixes[1]->getMatrixValue(i, indexLocalMax)) {
              indexLocalMax = j;
            }
            j++;
          }
          res.setMatrixValue(i, indexLocalMax, 254.0);
        }
        j++;
      }
    }
    // Gradient en y
    for (int j = 0; j < matrixes[2]->nbCol(); ++j) {
      int i = 0;
      while (i < matrixes[2]->nbRow()) {
        if (matrixes[2]->getMatrixValue(i, j) != 0) {
          int indexLocalMax = i;
          while (i < matrixes[2]->nbRow() && matrixes[2]->getMatrixValue(i, j) != 0) {
            if (matrixes[2]->getMatrixValue(i, j) >
                matrixes[2]->getMatrixValue(indexLocalMax, j)) {
              indexLocalMax = i;
            }
            i++;
          }
          res.setMatrixValue(indexLocalMax, j, 254.0);
        }
        i++;
      }
    }
  }
  if (matrixes.size() > 4) {
    // Diagonal haut gauche vers bas droite
    for (int i = 0; i < matrixes[3]->nbRow(); ++i) {
      int j = 0;
      int tempI = i;
      while (j < matrixes[3]->nbCol() && tempI < matrixes[3]->nbRow()) {
        if (matrixes[3]->getMatrixValue(tempI, j) != 0) {
          int indexColLocalMax = j;
          int indexRowLocalMax = tempI;
          while (j < matrixes[3]->nbCol() && tempI < matrixes[3]->nbRow()
                 && matrixes[3]->getMatrixValue(tempI, j) != 0) {
            if (matrixes[3]->getMatrixValue(tempI, j) >
                matrixes[3]->getMatrixValue(indexRowLocalMax, indexColLocalMax)) {
              indexColLocalMax = j;
              indexRowLocalMax = tempI;
            }
            j++;
            tempI++;
          }
          res.setMatrixValue(indexRowLocalMax, indexColLocalMax, 254.0);
        }
        j++;
        tempI++;
      }
    }
    for (int j = 0; j < matrixes[3]->nbCol(); ++j) {
      int tempJ = j;
      int i = 0;
      while (tempJ < matrixes[3]->nbCol() && i < matrixes[3]->nbRow()) {
        if (matrixes[3]->getMatrixValue(i, tempJ) != 0) {
          int indexColLocalMax = tempJ;
          int indexRowLocalMax = i;
          while (tempJ < matrixes[3]->nbCol() && i < matrixes[3]->nbRow()
                 && matrixes[3]->getMatrixValue(i, tempJ) != 0) {
            if (matrixes[3]->getMatrixValue(i, tempJ) >
                matrixes[3]->getMatrixValue(indexRowLocalMax, indexColLocalMax)) {
              indexColLocalMax = tempJ;
              indexRowLocalMax = i;
            }
            tempJ++;
            i++;
          }
          res.setMatrixValue(indexRowLocalMax, indexColLocalMax, 254.0);
        }
        tempJ++;
        i++;
      }
    }

    // Diagonal haut droite vers diagonal bas gauche
    for (int i = 0; i < matrixes[4]->nbRow(); ++i) {
      int j = matrixes[4]->nbCol() - 1;
      int tempI = i;
      while (j >= 0 && tempI < matrixes[4]->nbRow()) {
        if (matrixes[4]->getMatrixValue(tempI, j) != 0) {
          int indexColLocalMax = j;
          int indexRowLocalMax = tempI;
          while (j >= 0 && tempI < matrixes[4]->nbRow()
                 && matrixes[4]->getMatrixValue(tempI, j) != 0) {
            if (matrixes[4]->getMatrixValue(tempI, j) >
                matrixes[4]->getMatrixValue(indexRowLocalMax, indexColLocalMax)) {
              indexColLocalMax = j;
              indexRowLocalMax = tempI;
            }
            j--;
            tempI++;
          }
          res.setMatrixValue(indexRowLocalMax, indexColLocalMax, 254.0);
        }
        j--;
        tempI++;
      }
    }
    for (int j = matrixes[4]->nbCol() - 1; j >= 0; --j) {
      int tempJ = j;
      int i = 0;
      while (tempJ >= 0 && i < matrixes[4]->nbRow()) {
        if (matrixes[4]->getMatrixValue(i, tempJ) != 0) {
          int indexColLocalMax = tempJ;
          int indexRowLocalMax = i;
          while (tempJ >= 0 && i < matrixes[4]->nbRow()
                 && matrixes[4]->getMatrixValue(i, tempJ) != 0) {
            if (matrixes[4]->getMatrixValue(i, tempJ) >
                matrixes[4]->getMatrixValue(indexRowLocalMax, indexColLocalMax)) {
              indexColLocalMax = tempJ;
              indexRowLocalMax = i;
            }
            tempJ--;
            i++;
          }
          res.setMatrixValue(indexRowLocalMax, indexColLocalMax, 254.0);
        }
        tempJ--;
        i++;
      }
    }
  }
  return res;
}
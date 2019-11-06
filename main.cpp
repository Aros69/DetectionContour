#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "utils/MatrixFilter.h"
#include "Computations.h"

void meanFilterTest() {
  std::cout<<"Debut du test de filtre moyenneur. Appuyer sur une touche pour continuer."<<std::endl;
  cv::Mat image;
  // Read the file
  image = imread("data/ExempleSimple.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m = MatrixFilter::moyenneur(5, 5);
  Matrix r = Computations::convolve_2d(imTest, m);
  cv::Mat res = r.convertToOpenCvMat();
  // Create a window for display.
  namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  // Show our image inside it.
  imshow("Display window", res);
  // Wait for a keystroke in the window
  cv::waitKey(0);
  std::cout<<"Fin du test de filtre moyenneur "<<std::endl;
}

void sobelFilterBidirectionnalTest() {
  std::cout<<"Debut du test de filtre bidirectionnel. Appuyer sur une touche pour continuer."<<std::endl;
  cv::Mat image;
  // Read the file
  //image = imread("data/SmallImg.png", cv::IMREAD_GRAYSCALE);
  //image = imread("data/ExempleSimple.png", cv::IMREAD_GRAYSCALE);
  //image = imread("data/Pikachu.jpeg", cv::IMREAD_GRAYSCALE);
  image = imread("data/Lenna.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m = MatrixFilter::sobel(false);
  std::vector<Matrix *> r = Computations::convolve_2d_bidirectionnal(imTest, m);
  cv::Mat res = r[0]->convertToOpenCvMat();
  // Create a window for display.
  namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  // Show our image inside it.
  imshow("Display window", res);
  // Wait for a keystroke in the window
  cv::waitKey(0);

  delete (r[0]);
  delete (r[1]);
  delete (r[2]);

  std::cout<<"Fin du test de filtre bidirectionnel"<<std::endl;
}

void prewittFilterQuadridirectionnalTest() {
  std::cout<<"Debut du test de filtre quadri-directionnel. Appuyer sur une touche pour continuer."<<std::endl;
  cv::Mat image;
  // Read the file
  //image = imread("data/SmallImg.png", cv::IMREAD_GRAYSCALE);
  //image = imread("data/ExempleSimple.png", cv::IMREAD_GRAYSCALE);
  //image = imread("data/Pikachu.jpeg", cv::IMREAD_GRAYSCALE);
  image = imread("data/Lenna.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m1 = MatrixFilter::prewitt(false);
  MatrixFilter m2 = MatrixFilter::prewitt(true);
  Matrix orientation(imTest.nbRow(), imTest.nbCol());
  std::vector<Matrix *> r = Computations::convolve_2d_quadridirectionnal(imTest, m1, m2);
  //cv::Mat res = orientation.convertToOpenCvMat();
  cv::Mat res = r[0]->convertToOpenCvMat();
  // Create a window for display.
  namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  // Show our image inside it.
  imshow("Display window", res);
  // Wait for a keystroke in the window
  cv::waitKey(0);
  delete (r[0]);
  delete (r[1]);
  delete (r[2]);
  delete (r[3]);
  delete (r[4]);

  std::cout<<"Fin du test de filtre quadridirectionnel"<<std::endl;
}

void gaussianFilterTest() {
  std::cout<<"Debut du test de filtre gaussien. Appuyer sur une touche pour continuer."<<std::endl;
  cv::Mat image;
  // Read the file
  image = imread("data/ExempleSimple.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m = MatrixFilter::gaussian_blur_kernel_2d(5, 5, 1);
  Matrix r = Computations::convolve_2d(imTest, m);
  cv::Mat res = r.convertToOpenCvMat();
  // Create a window for display.
  namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  // Show our image inside it.
  imshow("Display window", res);
  // Wait for a keystroke in the window
  cv::waitKey(0);
  std::cout<<"Fin du test de filtre gaussien"<<std::endl;
}

void globalThresholdTest() {
  std::cout<<"Debut du test de seuillage global. Appuyer sur une touche pour continuer."<<std::endl;
  cv::Mat image;
  // Read the file
  image = imread("data/Barbara.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m = MatrixFilter::sobel(false);
  MatrixFilter m2 = MatrixFilter::sobel(true);
  std::vector<Matrix *> r = Computations::convolve_2d_quadridirectionnal(imTest, m, m2);
  Matrix postTreatment = Computations::postTGlobalThreshold(*r[0], 60);
  cv::Mat res = postTreatment.convertToOpenCvMat();
  // Create a window for display.
  namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  // Show our image inside it.
  imshow("Display window", res);
  // Wait for a keystroke in the window
  cv::waitKey(0);

  delete (r[0]);
  delete (r[1]);
  delete (r[2]);
  delete (r[3]);
  delete (r[4]);
  std::cout<<"Fin du test de seuillage global"<<std::endl;
}

void localThresholdTest() {
  std::cout<<"Debut du test de seuillage local. Appuyer sur une touche pour continuer."<<std::endl;
  cv::Mat image;
  // Read the file
  image = imread("data/Barbara.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m = MatrixFilter::prewitt(false);
  MatrixFilter m2 = MatrixFilter::prewitt(true);
  std::vector<Matrix *> r = Computations::convolve_2d_quadridirectionnal(imTest, m, m2);
  Matrix postTreatment = Computations::postTLocalThreshold(*r[0], 70);
  cv::Mat res = postTreatment.convertToOpenCvMat();
  // Create a window for display.
  namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  // Show our image inside it.
  imshow("Display window", res);
  // Wait for a keystroke in the window
  cv::waitKey(0);

  delete (r[0]);
  delete (r[1]);
  delete (r[2]);
  delete (r[3]);
  delete (r[4]);

  std::cout<<"Fin du test de seuillage local"<<std::endl;
}

void hysteresisThresholdTest() {
  std::cout<<"Debut du test de seuillage par hystérésis. Appuyer sur une touche pour continuer."<<std::endl;
  cv::Mat image;
  // Read the file
  image = imread("data/Lenna.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m1 = MatrixFilter::kirsch(false);
  MatrixFilter m2 = MatrixFilter::kirsch(true);
  std::vector<Matrix *> r = Computations::convolve_2d_quadridirectionnal(imTest, m1, m2);
  Matrix postTreatment = Computations::postTHysteresisThreshold(*r[0], 90);
  cv::Mat res = postTreatment.convertToOpenCvMat();
  // Create a window for display.
  namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  // Show our image inside it.
  imshow("Display window", res);
  // Wait for a keystroke in the window
  cv::waitKey(0);

  delete (r[0]);
  delete (r[1]);
  delete (r[2]);
  delete (r[3]);
  delete (r[4]);

  std::cout<<"Fin du test de seuillage par hysteresis"<<std::endl;
}

void edgeRefinementTest(){
  std::cout<<"Debut du test de raffinement de contour. Appuyer sur une touche pour continuer."<<std::endl;
  cv::Mat image;
  // Read the file
  image = imread("data/ExempleSimple.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m1 = MatrixFilter::kirsch(false);
  MatrixFilter m2 = MatrixFilter::kirsch(true);
  //std::vector<Matrix *> r = Computations::convolve_2d_quadridirectionnal(imTest, m1, m2);
  std::vector<Matrix *> r = Computations::convolve_2d_bidirectionnal(imTest, m1);
  Matrix postTreatment = Computations::edgeRefinement(r);
  cv::Mat res = postTreatment.convertToOpenCvMat();
  // Create a window for display.
  namedWindow("Display window", cv::WINDOW_AUTOSIZE);
  // Show our image inside it.
  imshow("Display window", res);
  // Wait for a keystroke in the window
  cv::waitKey(0);

  delete (r[0]);
  delete (r[1]);
  delete (r[2]);
  /*delete (r[3]);
  delete (r[4]);*/

  std::cout<<"Fin du test de raffinement de contour"<<std::endl;
}

int main() {
  std::cout << "Hello, World!" << std::endl;

  meanFilterTest();
  sobelFilterBidirectionnalTest();
  prewittFilterQuadridirectionnalTest();
  gaussianFilterTest();
  globalThresholdTest();
  localThresholdTest();
  hysteresisThresholdTest();
  edgeRefinementTest();

  std::cout << "Bye, World!" << std::endl;
  return 0;
}
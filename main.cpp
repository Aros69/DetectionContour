#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "utils/MatrixFilter.h"
#include "Computations.h"

void meanFilterTest() {
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
}

void rotateMatrixTest() {
  Matrix f(3, 1);
  f.setMatrixValue(0, 0, 1);
  f.setMatrixValue(1, 0, 2);
  f.setMatrixValue(2, 0, 3);
  f.print();

  Matrix t = f.rotateClockwise90();
  t.print();
}

void sobelFilterBidirectionnalTest() {
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
}

void prewittFilterQuadridirectionnalTest() {
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
  std::cout << r[0]->max() << " " << r[1]->max() << " " << r[2]->max() << " "
            << r[3]->max() << " " << r[4]->max() << std::endl;
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
}

void gaussianFilterTest() {
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
}

void globalThresholdTest() {
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
}

void localThresholdTest() {
  cv::Mat image;
  // Read the file
  image = imread("data/Lenna.png", cv::IMREAD_GRAYSCALE);
  Matrix imTest(image);
  MatrixFilter m1 = MatrixFilter::kirsch(false);
  MatrixFilter m2 = MatrixFilter::kirsch(true);
  std::vector<Matrix *> r = Computations::convolve_2d_quadridirectionnal(imTest, m1, m2);
  Matrix postTreatment = Computations::postTLocalThreshold(*r[0], 5);
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
}

int main() {
  std::cout << "Hello, World!" << std::endl;

  //meanFilterTest();
  //rotateMatrixTest();
  //sobelFilterBidirectionnalTest();
  //prewittFilterQuadridirectionnalTest();
  //gaussianFilterTest();
  globalThresholdTest();

  std::cout << "Bye, World!" << std::endl;
  return 0;
}
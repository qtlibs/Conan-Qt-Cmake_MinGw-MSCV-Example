#include <QApplication>
#include <opencv2/opencv.hpp>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // Convert the image to grayscale
    cv::Mat gray_image;
    cv::Mat image = cv::imread("22.png", cv::IMREAD_COLOR);
    cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);

    // Display the original image
    cv::imshow("Original Image", image);

    // Display the grayscale image
    cv::imshow("Grayscale Image", gray_image);

    // Wait for a key press and close the windows
    cv::waitKey(0);

    return a.exec();
}

#include <iostream>
#include <opencv/cvaux.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char * argv[])
{
    Mat image, A;
    
    // Read the file
    image = imread("low4.jpg", CV_LOAD_IMAGE_COLOR);
    
    // Check for invalid input
    if(!image.data){
        cout << "Could not open or fing the image" << std::endl;
        return -1;
    }
    
    cvtColor(image, A, CV_RGB2GRAY);
    
    int glev[256] = {0};
    int x = 0;
    
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			x = A.at<uchar>(i,j);

			// low image 4
			if (x < 57)
			{
				A.at<uchar>(i,j) = 0;
			} 
			else if (x < 153)
			{
				A.at<uchar>(i,j) = (x - 57) * 2.2917 + 1;
			}
			else 
			{
				A.at<uchar>(i,j) = (x - 153) * 1.2593 + 221;
			}

			glev[x] = glev[x] + 1;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		cout << i << " = " << glev[i] << "\n";
	}

	// display window
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Contrast Strech Image", CV_WINDOW_AUTOSIZE);
	
	// move the window
	moveWindow("Original Image",100,70);
	moveWindow("Contrast Strech Image",700,70);
    
    // Show our image inside it
    imshow("Contrast Strech Image", A);
	imshow("Original Image", image);
    
    waitKey(0);
    image.release();
    A.release();
    return 0;
}
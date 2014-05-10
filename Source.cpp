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

	// display window names
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	namedWindow("Contrast Strech Image", CV_WINDOW_AUTOSIZE);
	
	// move the window
	moveWindow("Original Image",100,70);
	moveWindow("Contrast Strech Image",700,70);
    
	// Put text on the image
	putText(image, "Original Image", cvPoint(60,50), 1,1,cvScalar(0,0,0),1,1,false);
	putText(A, "Contrast Image", cvPoint(60,50), 1,1,cvScalar(0,0,0),1,1,false);

    // Show our image inside it
    imshow("Contrast Strech Image", A);
	imshow("Original Image", image);
    
    waitKey(0);
    image.release();
    A.release();
    return 0;
}


/*
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void createFilter(double gKernel[][5])
{
    // set standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    // sum is for normalization
    double sum = 0.0;
	double M_PI = 3.14;

    // generate 5x5 kernel
    for (int x = -2; x <= 2; x++)
    {
        for(int y = -2; y <= 2; y++)
        {
            r = sqrt(x*x + y*y);
            gKernel[x + 2][y + 2] = (exp(-(r*r)/s))/(M_PI * s);
            sum += gKernel[x + 2][y + 2];
        }
    }

    // normalize the Kernel
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            gKernel[i][j] /= sum;

}

int main()
{
    double gKernel[5][5];
    createFilter(gKernel);
	
    for(int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
            cout<<gKernel[i][j]<<"\t";
        cout<<endl;
    }
	system("pause");
	return 0;
}

*/

/*
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int main( int argc, char** argv )
{
// Load an image from file
Mat src = imread( "C:/Users/Hashmath/Desktop/Image Processing/noice3.jpg", CV_LOAD_IMAGE_UNCHANGED );

//show the loaded image
imshow( "Original Image", src );

Mat dst,dst1,dst2;
char zBuffer[35];
int i = 9;

//copy the text to the "zBuffer"
_snprintf_s(zBuffer, 35,"%d x %d", i, i);

//smooth the image using Gaussian kernel in the "src" and save it to "dst"
GaussianBlur( src, dst, Size( i, i ), 0, 0 );

//put the text in the "zBuffer" to the "dst" image
putText( dst, zBuffer, Point( src.cols/4, src.rows/8), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2 );


i += 2;
_snprintf_s(zBuffer, 35,"%d x %d", i, i);
GaussianBlur( src, dst1, Size( i, i ), 0, 0 );
putText( dst1, zBuffer, Point( src.cols/4, src.rows/8), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2 );

i += 2;
_snprintf_s(zBuffer, 35,"%d x %d", i, i);
GaussianBlur( src, dst2, Size( i, i ), 0, 0 );
putText( dst2, zBuffer, Point( src.cols/4, src.rows/8), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255), 2 );

//create 2 empty windows
namedWindow( "Original Image" , CV_WINDOW_AUTOSIZE );
namedWindow( "Smoothed Image" , CV_WINDOW_AUTOSIZE );
namedWindow( "Smoothed Image1" , CV_WINDOW_AUTOSIZE );
namedWindow( "Smoothed Image2" , CV_WINDOW_AUTOSIZE );


//show the blurred image with the text
imshow( "Smoothed Image", dst );
imshow( "Smoothed Image1", dst1 );
imshow( "Smoothed Image2", dst2 );

waitKey(0);     
return 0;
}
*/
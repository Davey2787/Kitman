#include "cv.h"
#include "highgui.h"

int main( int argc, char** argv ) { 
    cvNamedWindow( "Example2_9_L", CV_WINDOW_AUTOSIZE );
    cvNamedWindow( "Example2_9_R", CV_WINDOW_AUTOSIZE );	
    CvCapture* capture1;
    CvCapture* capture2;	
    if (argc==1) {
	//right camera	
        capture1 = cvCreateCameraCapture( 1 );
	//left camera
	capture2 = cvCreateCameraCapture( 2 );
    } else {
        capture1 = cvCreateFileCapture( argv[1] );
	capture2 = cvCreateFileCapture( argv[1] );
    }
    assert( capture1 != NULL );
    assert( capture2 != NULL );	

    IplImage* frame1;
    IplImage* frame2;	
    while(1) 
    {
        frame1 = cvQueryFrame( capture1 );
	frame2 = cvQueryFrame( capture2 );
        if( !frame1 || !frame2 ) break;
        cvShowImage( "Example2_9_R", frame1 );
	cvShowImage( "Example2_9_L", frame2 );
        char c = cvWaitKey(10);
        if( c == 27 ) break;
    }
	cvSaveImage("right_05.jpeg", frame1);
	cvSaveImage("left_05.jpeg", frame2);
    cvReleaseCapture( &capture1 );
    cvDestroyWindow( "Example2_9_L" );
    cvReleaseCapture( &capture2 );
    cvDestroyWindow( "Example2_10_R" );
}

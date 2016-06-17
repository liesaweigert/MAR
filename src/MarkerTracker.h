#ifndef MAR_TEST_MARKERTRACKER_H
#define MAR_TEST_MARKERTRACKER_H

#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "PoseEstimation.h"
#include <iomanip>
#include "DrawPrimitives.h"

using namespace std;
using namespace cv;

class MarkerTracker {

    public:
        Eigen::Matrix4f find (Mat& image);

    private:
        int sampleSubPix(const Mat &point_source, const Point2f &p);
        Point2f intersection(Vec4f line1, Vec4f line2);
};


#endif //MAR_TEST_MARKERTRACKER_H

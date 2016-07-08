#ifndef MAR_TEST_MARKERTRACKER_H
#define MAR_TEST_MARKERTRACKER_H

#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include "PoseEstimation.h"
#include <iomanip>
#include "Atom.h"

using namespace std;
using namespace cv;

struct Marker{
    int marker_code;
    Eigen::Matrix4f marker_matrix;
    Atom type;
    int seen;
};


/* initializes an array of 6 Markers with the
 * marker codes given in the lecture
 */
void init_markers(Marker* markers);

class MarkerTracker {

public:
    void find (Mat& image, Marker* markers, int marker_count);

private:
    int sampleSubPix(const Mat &point_source, const Point2f &p);
    Point2f intersection(Vec4f line1, Vec4f line2);
};


#endif //MAR_TEST_MARKERTRACKER_H

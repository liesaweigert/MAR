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
    Atom type;
    int marker_code;
    Eigen::Matrix4f marker_matrix;
    float x;
    float y;
    float z;
    Eigen::Vector3f position;
};


/* initializes an array of 6 Markers with the
 * marker codes given in the lecture
 */
void init_markers(Marker* markers);

class MarkerTracker {

public:
    vector<Marker> find (Mat& image);

private:
    int sampleSubPix(const Mat &point_source, const Point2f &p);
    Point2f intersection(Vec4f line1, Vec4f line2);
};


#endif //MAR_TEST_MARKERTRACKER_H

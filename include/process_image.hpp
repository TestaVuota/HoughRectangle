#ifndef PROCESS_IMAGE_H
#define PROCESS_IMAGE_H
#include <Eigen/Dense>
#include "config.hpp"

/**
 * Function to make sure binary is 0 and 255
 *
 * @param img Eigen float matrix to be normalized
 */
void normalise_img(Eigen::MatrixXf & img);

/*
 * Returns a linearly spaced array
 *
 * @param a starting value
 * @param b end value
 * @param N number of bins
 * @return vector<float> 
 */
vector<float> LinearSpacedArray(float a, float b, std::size_t N);


/*
 * Finds position of all elements superior to threshold
 *
 * @param hough Eigen float matrix
 * @float threshold float
 * @return vector of Eigen::Index of the positions where hough is more than threshold
 */
std::vector<Eigen::Index> find_local_maximum(Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> & img,float threshold);

/**
 *
 * Implementation of rectangle detection via the Hough rectangle transform
 *
 * This class implements the Hough transform, enhanced hough transform, windowed hough transform and utility functions
 * in order to compute the so called Hough Rectangle detection.
 *
 */
class HoughRectangle{
    public:
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> m_img;

        /*
         * Rectangle class constructor
         *
         * @param img Eigen float, Dynamic, RowMajor matrix to process
         */
        HoughRectangle(Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> & img); //declaration

    public:
        /**
         * Applies the classic Hough transform
         *
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[out] acc accumulator (hough transform)
         */
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> hough_transform(Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> & img, int thetaBins, int rhoBins,float  thetaMin,float thetaMax);

        /**
         * Performs the Windowed hough transform on a single patch
         *
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[out] wht hough transformed image
         */
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> windowed_hough(Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> & img,int r_min,int r_max, int thetaBins, int rhoBins,float  thetaMin,float thetaMax);

        /**
         * Applies the Windowed hough transform on the whole image
         *
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[out]
         */
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> apply_windowed_hough(Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> & img,int L_window,int r_min,int r_max, int thetaBins, int rhoBins,float  thetaMin,float thetaMax);

        /**
         * Computes enhanced Hough transform
         *
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[out] 
         */
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> enhance_hough(Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> & hough,int h,int w);
        
        /**
         * Applies a ring on the input matrix by putting to zero all pixels outside the ring
         *
         * @param[in] img Eigen matrix
         * @param[in] r_min radius of inner ring
         * @param[in] r_max radius of outer ring
         * @param[out] result ringed output matrix
         */
        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> ring(Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> & img,int r_min,int r_max);


};

#endif

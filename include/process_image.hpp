#ifndef PROCESS_IMAGE_H
#define PROCESS_IMAGE_H
#include <Eigen/Dense>
#include "config.hpp"
#include <tuple>
#include <array>

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
// TODO(luczeng): this is a perfect use case for a template
std::vector<float> LinearSpacedArray(float a, float b, std::size_t N);


/*
 * Finds position of all elements superior to threshold
 *
 * @param hough Eigen float matrix
 * @float threshold float
 * @return vector of Eigen::Index of the positions where hough is more than threshold
 */
std::vector<std::array<int,2>> find_local_maximum(Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> & img,float threshold);

/**
 *
 * Implementation of rectangle detection via the Hough rectangle transform
 *
 * This class implements the Hough transform, enhanced hough transform, windowed hough transform and utility functions
 * in order to compute the so called Hough Rectangle detection.
 *
 */
class HoughRectangle{
    private:
        int m_thetaBins;
        int m_thetaMin;
        int m_thetaMax;
        int m_rhoBins;
        Eigen::VectorXf m_theta_vec;
        std::vector<float> m_rho_vec;

        Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> m_img;

    public:
        /*
         * Rectangle class constructor
         *
         * @param img Eigen float, Dynamic, RowMajor matrix to process
         */
        typedef Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> fMat;
        HoughRectangle(fMat & img,int thetaBins = 256, int rhoBins = 256,
    float thetaMin = -90, float thetaMax = 90); //declaration

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
        fMat hough_transform(fMat & img);

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
        fMat windowed_hough(fMat & img,int r_min,int r_max);

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
        fMat apply_windowed_hough(fMat & img,int L_window,int r_min,int r_max);

        /**
         * Computes enhanced Hough transform
         *
         * @param[in]
         * @param[in]
         * @param[in]
         * @param[out] 
         */
        fMat enhance_hough(fMat & hough,int h,int w);
        
        /**
         * Applies a ring on the input matrix by putting to zero all pixels outside the ring
         *
         * @param[in] img Eigen matrix
         * @param[in] r_min radius of inner ring
         * @param[in] r_max radius of outer ring
         * @param[out] result ringed output matrix
         */
        fMat ring(fMat & img,int r_min,int r_max);
        
        
        /**
         * Returns vectors of theta and rho positions corresponding to the input indexes
         *
         *
         */
        std::tuple<std::vector<float>,std::vector<float>> index_rho_theta(std::vector<std::array<int,2>> indexes);

        /**
         * Matches detected peaks into rectangle
         *
         * @param[in] rho_maxs vector specifying rho positions of detected peaks
         * @param[in] theta_maxs vector specifying theta positions of detected peaks
         * @param[out] 
         */
         std::vector<std::array<float,3>> match_maximums(std::vector<float> &rho_maxs,std::vector<float> & theta_maxs,float T_t,float T_rho,float T_L,float T_alpha);

};

#endif

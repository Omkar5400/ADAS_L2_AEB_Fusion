#ifndef KALMAN_FILTER_HPP
#define KALMAN_FILTER_HPP

#include <Eigen/Dense>

class KalmanFilter {
public:
    KalmanFilter();
    ~KalmanFilter();

    // Initialize the filter with starting position
    void init(double initial_x);

    // Step 1: Predict where the car will be based on physics
    void predict(double dt);

    // Step 2: Update the guess using new sensor data
    void update(double measurement, double variance);

    // Get the current "Best Guess"
    double get_state() const { return x_(0); }

private:
    Eigen::VectorXd x_; // State vector [position, velocity]
    Eigen::MatrixXd P_; // Uncertainty Covariance
    Eigen::MatrixXd F_; // State Transition Matrix
    Eigen::MatrixXd Q_; // Process Noise
    Eigen::MatrixXd H_; // Measurement Matrix
    Eigen::MatrixXd I_; // Identity Matrix
};

#endif

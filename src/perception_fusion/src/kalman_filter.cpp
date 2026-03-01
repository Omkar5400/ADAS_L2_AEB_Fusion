#include "perception_fusion/kalman_filter.hpp"

KalmanFilter::KalmanFilter() {
    x_ = Eigen::VectorXd(2); // [pos, vel]
    P_ = Eigen::MatrixXd(2, 2);
    F_ = Eigen::MatrixXd(2, 2);
    Q_ = Eigen::MatrixXd(2, 2);
    H_ = Eigen::MatrixXd(1, 2);
    I_ = Eigen::MatrixXd::Identity(2, 2);

    H_ << 1, 0; // We only measure position
}

void KalmanFilter::init(double initial_x) {
    x_ << initial_x, -5.0; // Start at pos, assume -5m/s velocity
    P_ << 1, 0, 0, 1;      // Initial uncertainty
}

void KalmanFilter::predict(double dt) {
    F_ << 1, dt, 0, 1;
    Q_ << 0.1, 0, 0, 0.1;
    
    x_ = F_ * x_; // Predict new state
    P_ = F_ * P_ * F_.transpose() + Q_; // Predict new uncertainty
}

void KalmanFilter::update(double z, double R_variance) {
    Eigen::MatrixXd R = Eigen::MatrixXd(1, 1);
    R << R_variance;

    // Kalman Gain calculation
    Eigen::MatrixXd S = H_ * P_ * H_.transpose() + R;
    Eigen::MatrixXd K = P_ * H_.transpose() * S.inverse();

    // Update the state with the measurement z
    Eigen::VectorXd y = Eigen::VectorXd(1);
    y << z;
    x_ = x_ + (K * (y - H_ * x_));
    P_ = (I_ - K * H_) * P_;
}

KalmanFilter::~KalmanFilter() {}

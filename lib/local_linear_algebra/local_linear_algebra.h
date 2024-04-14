#pragma once
#include <ArduinoEigen.h>   // KAN MULIGENS BYTTES OM DET TAR FOR MYE PLASS
#include <SparkFun_GridEYE_Arduino_Library.h>


void elimState(Eigen::MatrixXf A, Eigen::VectorXf b, Eigen::VectorXf &dTilde, Eigen::VectorXf &bTilde);


void backSub(Eigen::MatrixXf A, Eigen::VectorXf dTilde, Eigen::VectorXf bTilde, Eigen::VectorXf &x);


void thomas_algorithm(Eigen::MatrixXf A, Eigen::VectorXf b, Eigen::VectorXf &x);
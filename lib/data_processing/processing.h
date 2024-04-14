#pragma once
#include <ArduinoEigen.h>   // KAN MULIGENS BYTTES OM DET TAR FOR MYE PLASS
#include <SparkFun_GridEYE_Arduino_Library.h>


void ReadFromGridEye(GridEYE grideye, Eigen::MatrixXf &Data);

void preProcessX(Eigen::MatrixXf Data, Eigen::MatrixXf &ProcessedDataX);

void preProcessY(Eigen::MatrixXf Data, Eigen::MatrixXf &ProcessedDataY,int newRes);

void cubicSpline(Eigen::VectorXf z, Eigen::VectorXf y, Eigen::VectorXf &sol, int res);
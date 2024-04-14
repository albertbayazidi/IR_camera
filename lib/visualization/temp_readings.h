#pragma once
#include <TFT_eSPI.h>
#include <SPI.h>
#include <ArduinoEigen.h>

#include "screen_constants.h"

void screen_setup(TFT_eSPI tft);

void test_dyn_obj(TFT_eSPI tft, int testNum);

void printMat(Eigen::MatrixXf Mat);

void printVec(Eigen::VectorXf Vec);


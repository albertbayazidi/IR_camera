#include <Arduino.h>
#include <temp_readings.h>
#include "processing.h"
#include "local_linear_algebra.h"

// External libraries
#include <ArduinoEigenDense.h>   
#include <SparkFun_GridEYE_Arduino_Library.h>

// Constants
int n = 8;
int resFac = 25;
int new_res = (n-1)*resFac-(n-2);
// testing purposes
float startMillis = 0;
float currentMillis = 0;

// temp storage
Eigen::VectorXf temp_array_small(n-2);
Eigen::VectorXf temp_array_large(new_res);

Eigen::MatrixXf ProcessedDataX(n,n-2);
Eigen::MatrixXf intermidiateData(n,new_res);
Eigen::MatrixXf ProcessedDataY(n-2,resFac); 

// new Data
Eigen::MatrixXf interpData(new_res,new_res);

// spline weights
Eigen::MatrixXf zMatrix(n,n);
Eigen::MatrixXf zMatrixY(n,new_res);  

// GridEye Storage
Eigen::MatrixXf Data(n,n);

// Tri-diagonal matrix
Eigen::MatrixXf A(n-2,n-2);

GridEYE grideye;

TFT_eSPI tft = TFT_eSPI();               
int testNum = 30;

void setup()
{   
    A.setZero();
    zMatrixY.setZero(); //had impact
    zMatrix.setZero(); //had impact 
    
    A.diagonal().setConstant(4);
    A.diagonal(1).setConstant(1);
    A.diagonal(-1).setConstant(1);

    // General setup 
    Serial.begin(115200);
    Wire.begin();
    
    // Setup the LCD
    //screen_setup(tft);

    // setup the GridEYE
    grideye.begin();
}

void loop(){
    size_t freeHeap = esp_get_free_heap_size();
    Serial.print("Free heap: ");
    Serial.println(freeHeap);

    startMillis = millis();
    ReadFromGridEye(grideye, Data);

	preProcessX(Data, ProcessedDataX);  

    for (int i = 0; i < n; i++){
        thomas_algorithm(A,ProcessedDataX.row(i),temp_array_small);  
        zMatrix.block<1,6>(i,1) = temp_array_small;

        cubicSpline(zMatrix.row(i), Data.row(i), temp_array_large, resFac);
        intermidiateData.row(i) = temp_array_large;
    }   

    preProcessY(intermidiateData,ProcessedDataY,new_res);

    for (int i = 0; i < new_res; i++){
        thomas_algorithm(A,ProcessedDataY.col(i),temp_array_small); 
        zMatrixY.block(1,i,n-2,1) = temp_array_small;  

        cubicSpline(zMatrixY.col(i), intermidiateData.col(i), temp_array_large, resFac);
        interpData.col(i) = temp_array_large;
    }   

    currentMillis = millis();
    Serial.print("Time taken: ");
    Serial.println(currentMillis - startMillis);
    
    //printMat(interpData);
    //delay(2000);
}
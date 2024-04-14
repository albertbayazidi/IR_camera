#include <temp_readings.h>

void printMat(Eigen::MatrixXf Mat){
    int nrCols = Mat.cols();
    int nrRows = Mat.rows();

    for (int i = 0; i < nrRows; i++)
    {
        for (int j = 0; j < nrCols; j++)
        {
            Serial.print(Mat(i, j));
            Serial.print(", ");
        }
        Serial.println();
    }
}

void printVec(Eigen::VectorXf Vec){
    int nrRows = Vec.rows();
    int nrCols = Vec.cols();
    
    char buffer[100];
    for (int i = 0; i < nrRows; i++)
    {
        Serial.print(Vec(i));
        Serial.print(", ");   
    }
    Serial.println();
}
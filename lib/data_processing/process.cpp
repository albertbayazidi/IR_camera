#include <processing.h>
#include <temp_readings.h>

float Array[64] = {
    25.50, 24.00, 21.75, 21.75, 21.00, 20.25, 20.00, 19.00, 
    25.50, 24.50, 20.25, 19.75, 20.00, 19.75, 19.25, 18.75, 
    25.00, 23.50, 19.75, 20.00, 20.25, 20.00, 19.75, 18.50, 
    23.75, 21.75, 19.50, 19.50, 20.00, 19.75, 19.50, 19.00, 
    23.25, 20.50, 19.25, 19.00, 19.00, 19.50, 18.50, 18.50, 
    19.50, 19.50, 18.75, 19.00, 18.50, 19.25, 18.75, 18.25, 
    19.25, 19.00, 19.00, 18.75, 19.00, 18.25, 18.25, 18.25, 
    19.75, 19.00, 19.75, 19.50, 19.75, 19.25, 19.00, 18.75};

float t[8] = {0.0,1.0,2.0,3.0,4.0,5.0,6.0,7.0};

void ReadFromGridEye(GridEYE grideye, Eigen::MatrixXf &Data){
    for (int i=0; i<8; i++){
        for (int j=0; j<8; j++){
            //Data(i,j) = grideye.getPixelTemperature(i+j*8);
            Data(i,j) = Array[j+i*8];
        }
    }
}

void preProcessX(Eigen::MatrixXf Data, Eigen::MatrixXf &ProcessedDataX){
    Eigen::MatrixXf b(8,7);
    b = Data.block<8,7>(0,1) - Data.block<8,7>(0,0);
    ProcessedDataX = 6*(b.block<8,6>(0,1) - b.block<8,6>(0,0));
}

void preProcessY(Eigen::MatrixXf Data, Eigen::MatrixXf &ProcessedDataY,int newRes){
    Eigen::MatrixXf b(8,newRes);
    b = Data.block(1,0,7,newRes) - Data.block(0,0,7,newRes);
    ProcessedDataY = 6*(b.block(1,0,6,newRes) - b.block(0,0,6,newRes));
}

void cubicSpline(Eigen::VectorXf z, Eigen::VectorXf y, Eigen::VectorXf &sol, int res){
    Eigen::VectorXf x;
    Eigen::VectorXf sum(res);
    sum.setZero();

    for (int i = 0; i < 7; i++){
        x.setLinSpaced(res,i,i+1);
        Eigen::VectorXf xti = x - t[i] * Eigen::VectorXf::Ones(res);
        Eigen::VectorXf tpix = t[i+1] * Eigen::VectorXf::Ones(res) - x;

        sum = (z[i+1]/6 * xti.array().pow(3)).matrix(); 
        sum += (z[i]/6 * tpix.array().pow(3)).matrix(); 

        sum += (y[i+1] - z[i+1]/6) * xti;
        sum += (y[i] - z[i]/6) * tpix;
        if (i == 0){
            sol.segment(0,res) = sum;
        }
        else{
            sol.segment((res-1)*i,res) = sum;
        }
    }
}


#include <local_linear_algebra.h>
#include <temp_readings.h>

void elimState(Eigen::MatrixXf A, Eigen::VectorXf b, Eigen::VectorXf &dTilde, Eigen::VectorXf &bTilde){
    int n = A.rows();       

    // REMOVED dTILDE SINCE A HAS A CONSTANT SUB/SUPER-DIAGONAL
    bTilde(0) = b(0);
    bTilde(1) = b(1) - A(1,0)/A(0,0)*b(0);
    float m;

    for (int i = 2; i < n; i++){
        m = A(i-1,i)/A(i-1,i-1);
        bTilde(i) = b(i) - m*bTilde(i-1);
    }
}
    
void backSub(Eigen::MatrixXf A, Eigen::VectorXf dTilde, Eigen::VectorXf bTilde, Eigen::VectorXf &x){
    int n = A.rows();

    x(n-1) = bTilde(n-1)/A(n-1,n-1);

    for (int i = n-2; i >=0; i--){    
        x(i) = (bTilde(i) - A(i+1,i)*x(i+1))/dTilde(i);
    }
}

void thomas_algorithm(Eigen::MatrixXf A, Eigen::VectorXf b, Eigen::VectorXf &x){
    int n = A.rows();      
    Eigen::VectorXf dTilde(n);
    Eigen::VectorXf bTilde(n);
    dTilde.setConstant(3.75);
    dTilde(0) = 4;               
    bTilde.setZero();                   

    elimState(A, b, dTilde, bTilde);
    backSub(A, dTilde, bTilde, x);
}

#include <cmath>
#include <chrono>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <omp.h>

typedef std::vector<std::vector<double>> mat;
void matmul(mat& A, mat& B, mat& C){
    int n = A.size();
    #pragma omp parallel for schedule(auto)
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                C[i][j] += A[i][k]*B[j][k];
            }
        }
    }

}

void read_file(std::ifstream& infile, mat& vec, int n, bool trans){
    std::string line;
    for (int i=0; i<n; i++){
        getline(infile, line);
        std::istringstream iss(line);
        for (int j=0; j<n; j++){
            if (trans) {
                iss >> vec[j][i];
            }
            else{
                iss >> vec[i][j];
            }
        }
    }
}

void write_file(std::ofstream& outfile, mat& vec, int n){
    for (int i=0; i<n; i++){
        for (int j=0; j<n-1; j++){
            outfile << vec[i][j] << " ";
        }
        outfile << vec[i][n-1] << std::endl;
    }
}

int main(){
    for (int i=1; i <= 3; i++){
        int n = pow(10, i);
        mat A(n, std::vector<double>(n, 0.0));
        mat B(n, std::vector<double>(n, 0.0));
        mat C(n, std::vector<double>(n, 0.0));
        std::cout << "Processing matrices of size " << n << "x" << n << std::endl;
        std::string a_f("A_"+std::to_string(n)+".dat");
        std::ifstream a_file(a_f);
        std::string b_f("B_"+std::to_string(n)+".dat");
        std::ifstream b_file(b_f);
        read_file(a_file, A, n, false);
        read_file(b_file, B, n, true);
        a_file.close();
        b_file.close();
        auto start = std::chrono::steady_clock::now();
        matmul(A, B, C);
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>
                            (std::chrono::steady_clock::now() - start);
        auto time_elapsed = duration.count();
        std::cout << "Took " << time_elapsed << " us to process, or " << time_elapsed/1e6 << " s" << std::endl;;
        std::string c_f("C_calc_"+std::to_string(n)+".dat");
        std::ofstream out_file(c_f);
        write_file(out_file, C, n);
        out_file.close();
    }
}

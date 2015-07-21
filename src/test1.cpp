#include <iostream>
#include <vector>
#include "matrix.h"

#include <chrono>
#include <fstream>

#include <Eigen/Dense>

using namespace std;
using namespace optimization;
using namespace Eigen;

int main(int argc, char **argv)
{
   try {

      if( argc != 2) {
          cerr<<"Wrong number of arguments!"<<endl;
          return 1;
      }

      cmatrix *c1 = new cmatrix(1000, 1000);
      rmatrix *r1 = new rmatrix(1000, 1000);

      fill(c1->begin(), c1->end(), 200.0);
      fill(r1->begin(), r1->end(), 200.0);

      ofstream file(argv[1], ios::out | ios::trunc);
      if(!file.is_open()) {
          cerr<<"Cannot open file \""<<argv[1]<<"\"!"<<endl;
          delete c1;
          delete r1;
          return 1;
      }
      
      // For measuring the operations time
      chrono::time_point<chrono::system_clock> start, end;
      chrono::seconds elapsed;
      //
      
      // BEGIN EIGEN TEST
      cout<<"*** BEGIN EIGEN TEST *** "<<endl;
      cout<<"Threads: "<<Eigen::nbThreads()<<endl;
      file<<"m3 = m1 * m2";
      MatrixXd *m1 = new MatrixXd(1000, 1000);
      MatrixXd *m2 = new MatrixXd(1000, 1000);
      cout<<"Filling matrices... ";
      for(int i=0; i<1000; ++i) {
         for(int j=0; j<1000; ++j) {
            (*m1)(i, j) = (i+j)*(i+2)*(j+7);
            (*m2)(i, j) = (i+1)*(j+5)*(i+j+10);
         }
      }
      cout<<"Done!"<<endl;
      start = chrono::system_clock::now();
      MatrixXd m3 = (*m1) * (*m2);
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::seconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" seconds"<<endl;
      delete m1;
      delete m2;
      m3 = m3;
      cout<<"*** END EIGEN TEST ***"<<endl;
      // END EIGEN TEST
      
      // BEGIN SMOR TEST
      cout<<"*** BEGIN SMOR TEST ***"<<endl;
      file<<"rmatrix = rmatrix*cmatrix";
      cout<<"rmatrix tm1 = r1*c1"<<endl;
      start = chrono::system_clock::now();
      rmatrix tm1 = (*r1) * (*c1);
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::seconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" seconds"<<endl;
      delete c1;
      delete r1;
      cout<<"*** END SMOR TEST ***"<<endl;
      // END SMOR TEST
      
   } catch(exception& e) {
      cerr<<"Exception caught: "<<e.what()<<endl;
   }
   return 0;
}


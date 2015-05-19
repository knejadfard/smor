#include <iostream>
#include <vector>
#include "matrix.h"

#include <chrono>
#include <fstream>


using namespace std;
using namespace optimization;

int main()
{
   try {

      cmatrix c1(1000, 1000), c2(1000, 1000);
      rmatrix r1(1000, 1000), r2(1000, 1000);

      ofstream file("test.txt");

      fill(c1.begin(), c1.end(), 150.0);
      fill(r1.begin(), r1.end(), 200.0);
      //fill(r2.begin(), r2.end(), 250.0);
      //fill(c2.begin(), c2.end(), 100.0);

      chrono::time_point<chrono::system_clock> start, end;
      chrono::microseconds elapsed;

      file<<"Test 1: rmatrix = rmatrix*cmatrix ";
      start = chrono::system_clock::now();
      cout<<"rmatrix tm1 = r1*c1"<<endl;
      rmatrix tm1 = r1*c1;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;

      file<<"Test 2: eigen multiplication ";
      start = chrono::system_clock::now();

      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;

      /*file<<"Test 2: cmatrix = rmatrix*cmatrix ";
      start = chrono::system_clock::now();
      cout<<"cmatrix tm2 = r1*c1"<<endl;
      cmatrix tm2 = r1*c1;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;

      file<<"Test 3: rmatrix = rmatrix*rmatrix ";
      start = chrono::system_clock::now();
      cout<<"rmatrix tm3 = r1*r2"<<endl;
      rmatrix tm3 = r1*r2;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;

      file<<"Test 4: cmatrix = cmatrix*cmatrix ";
      start = chrono::system_clock::now();
      cout<<"cmatrix tm4 = c1*c2"<<endl;
      cmatrix tm4 = c1*c2;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;

      file<<"Test 5: rmatrix = cmatrix*rmatrix ";
      start = chrono::system_clock::now();
      cout<<"rmatrix tm5 = c1*r1"<<endl;
      rmatrix tm5 = c1*r1;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;

      file<<"Test 6: cmatrix = cmatrix*rmatrix ";
      start = chrono::system_clock::now();
      cout<<"cmatrix tm6 = c1*r1"<<endl;
      cmatrix tm6 = c1*r1;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;*/


   } catch(exception& e) {
      cerr<<"Exception caught: "<<e.what()<<endl;
   }
   return 0;
}


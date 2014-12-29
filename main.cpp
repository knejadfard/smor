#include <iostream>
#include <vector>
#include <fstream>
#include "matrix.h"

#include <chrono>
#include <fstream>


using namespace std;
using namespace optimization;

int main()
{
   try {

      /*cmatrix c1(2, 2), c2(2, 2);
      rmatrix r1(2, 2), r2(2, 2);*/
      cmatrix c1(1000, 1000);
      rmatrix r1(1000, 1000);
      #define r2 r1;
      #define c2 c1;

      ofstream file("test.txt");

      /*c1.assign({1, 2, 3, 4});
      r1.assign({11, 12, 13, 14}); //the same matrix as above, but with a different storage scheme
      c2.assign({6, 7, 8, 9});
      r2.assign({21, 22, 23, 24});*/
      fill(c1.begin(), c1.end(), 150.0);
      fill(r1.begin(), r1.end(), 200.0);
      /*fill(r2.begin(), r2.end(), 250.0);
      fill(c2.begin(), c2.end(), 100.0);*/

      chrono::time_point<chrono::system_clock> start, end;
      chrono::microseconds elapsed;

      file<<"Test 1: rmatrix = rmatrix*cmatrix ";
      start = chrono::system_clock::now();
      cout<<"rmatrix tm1 = r1*c1"<<endl;
      rmatrix tm1 = r1*c1;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;
      //file<<"Result:\n"<<tm1<<endl;

      file<<"Test 2: cmatrix = rmatrix*cmatrix ";
      start = chrono::system_clock::now();
      cout<<"cmatrix tm2 = r1*c1"<<endl;
      cmatrix tm2 = r1*c1;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;
      //file<<"Result:\n"<<tm2<<endl;

      file<<"Test 3: rmatrix = rmatrix*rmatrix ";
      start = chrono::system_clock::now();
      cout<<"rmatrix tm3 = r1*r2"<<endl;
      rmatrix tm3 = r1*r2;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;
      //file<<"Result:\n"<<tm3<<endl;

      file<<"Test 4: cmatrix = cmatrix*cmatrix ";
      start = chrono::system_clock::now();
      cout<<"cmatrix tm4 = c1*c2"<<endl;
      cmatrix tm4 = c1*c2;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;
      //file<<"Result:\n"<<tm4<<endl;

      file<<"Test 5: rmatrix = cmatrix*rmatrix ";
      start = chrono::system_clock::now();
      cout<<"rmatrix tm5 = c1*r1"<<endl;
      rmatrix tm5 = c1*r1;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;
      //file<<"Result:\n"<<tm5<<endl;

      file<<"Test 6: cmatrix = cmatrix*rmatrix ";
      start = chrono::system_clock::now();
      cout<<"cmatrix tm6 = c1*r1"<<endl;
      cmatrix tm6 = c1*r1;
      end = chrono::system_clock::now();
      elapsed = chrono::duration_cast<chrono::microseconds>(end-start);
      file<<" -> Duration: "<<elapsed.count()<<" microseconds"<<endl;
      //file<<"Result:\n"<<tm6<<endl;


   } catch(exception& e) {
      cerr<<"Exception caught: "<<e.what()<<endl;
   }
   return 0;
}


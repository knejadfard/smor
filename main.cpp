#include <iostream>
#include <vector>
#include <fstream>
#include "matrix.h"


using namespace std;
using namespace optimization;

int main()
{
   try {
      cmatrix c1(100, 100);

      for(miterator i=c1.cbegin(2); !i.ended(); ++i) {
         *i += 44;
      }
      for(miterator i=c1.rbegin(1); !i.ended(); ++i) {
         *i += 20;
      }

      rmatrix r1{rmatrix(c1+c1)};
      cmatrix c2{cmatrix(r1+c1)};

      ofstream file("output.txt");
      file<<"Behold! Here are the results:\n";
      file<<c2<<endl;

      file.close();

   } catch(exception& e) {
      cerr<<"Exception caught: "<<e.what()<<endl;
   }
   return 0;
}

#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
    try {
        matrix a(2, 2), b(2, 2);
        a.assign({1,2,3,4});
        b.assign({2,2,2,2});
        matrix c{a+b};
        cout<<c<<endl;
        for(auto i=c.column_begin(1); i!=c.column_end(1); ++i) {
            cout<<*i<<" ";
        }
    } catch(exception& e) {
        cerr<<"Exception caught: "<<e.what()<<endl;
    }
    return 0;
}

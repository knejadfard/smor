#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include <vector>
#include <initializer_list>
#include <ostream>

#include "iterator.h"

/*
* A specialized 2d matrix class for use in linear programming
*/
class matrix
{

public:

    typedef std::vector<double> vector_type;

    matrix()=delete; //disable default constructor to force the use of the following constructors
    matrix(const std::size_t&, const std::size_t&);
    matrix(std::initializer_list<double>)=delete;
    matrix(const matrix&);
    matrix(const matrix&&);

    matrix& operator=(const matrix&);
    matrix& operator=(matrix&&);

    double& operator()(const std::size_t&, const std::size_t&);
    const double& operator()(const std::size_t&, const std::size_t&) const;

    column_iterator column_begin(const std::size_t&);
    row_iterator row_begin(const std::size_t&);
    column_iterator column_end(const std::size_t&);
    row_iterator row_end(const std::size_t&);

    void assign(std::initializer_list<double>);

    friend class row_iterator;
    friend class column_iterator;

    friend matrix operator+(const matrix&, const matrix&);
    friend matrix operator-(const matrix&, const matrix&);
    friend matrix operator*(const matrix&, const matrix&);
    friend matrix operator/(const matrix&, const matrix&);
    //friend matrix& operator<<(matrix&, const double&);
    friend std::ostream& operator<<(std::ostream&, const matrix&);

    //matrix_column& column(const size_t&); //access a matrix column
    //matrix_row& row(const size_t&); //access a matrix row

    size_t row_count() const; //return the number of rows
    size_t col_count() const; //return the number of columns
    size_t size() const;

private:

    vector_type _v; //a contiguous vector to hold the doubles
    std::size_t _n; //number of rows
    std::size_t _m; //number of columns

    //convert between 2-index method and 1-index method
    std::size_t convert_index(const std::size_t&, const std::size_t&) const;

};

/*matrix operator+(const matrix&, const matrix&);
matrix operator-(const matrix&, const matrix&);
matrix operator*(const matrix&, const matrix&);
matrix operator/(const matrix&, const matrix&);
matrix& operator<<(matrix&, const double&); */

/*******************************************
*    DEFINITIONS
* usually must be in a separate file, but
* this is a compact library. So... :D
********************************************/
//#include "matrix.cpp"

#endif // MATRIX_H_INCLUDED

#include "matrix.h"
#include <algorithm>
#include <utility>
#include <exception>

matrix::matrix(const size_t& rows, const size_t& cols/*, const matrix_attr& t*/)
            : _v(rows*cols),
              _n{rows},
              _m{cols}/*,
              attribute{t}*/
{
    //nothing to do here
}

matrix::matrix(const matrix& rh): matrix(rh._n, rh._m/*, matrix_attr::ordinary*/)
{
    _v = rh._v;
}

matrix::matrix(const matrix&& rval)
            : _v{std::move(rval._v)},
              _n{rval._n},
              _m{rval._m}/*,
              attribute{rval.attribute}*/
{
    //no need to do anything special here
}

matrix& matrix::operator=(const matrix& rh)
{
    if(_n == rh._n || _m == rh._m) {
        _v = rh._v;
    } else {
        throw std::runtime_error("assignment of matrices with non-equal size");
    }
    return *this;
}

matrix& matrix::operator=(matrix&& rh)
{
    if(_n == rh._n || _m == rh._m) {
        _v = std::move(rh._v);
    } else {
        throw std::runtime_error("assignment of matrices with non-equal size");
    }
    return *this;
}

size_t matrix::row_count() const
{
    return _n;
}

size_t matrix::col_count() const
{
    return _m;
}

size_t matrix::size() const
{
    return _v.size();
}

size_t matrix::convert_index(const size_t& i, const size_t& j) const {
    return i*_m + j;
}

double& matrix::operator()(const size_t& i, const size_t& j)
{
    return _v.at(convert_index(i, j));
}

const double& matrix::operator()(const size_t& i, const size_t& j) const
{
    return _v.at(convert_index(i, j));
}

/*matrix& operator<<(matrix& m, const double& d)
{
    if(m.size() < m.row_count()*m.col_count()) {
        m._v.push_back(d);
    } else {
        throw std::runtime_error("inserting data to an already-full matrix");
    }
    return m;
}*/

std::ostream& operator<<(std::ostream& o, const matrix& m)
{
    for(size_t i=0; i<m._n; ++i) {
        for(size_t j=0; j<m._m; ++j) {
            o<<m(i, j)<<" ";
        }
        o<<std::endl;
    }
    return o;
}

void matrix::assign(std::initializer_list<double> ilist)
{
    if(ilist.size() != this->size()) {
        throw std::runtime_error("inserting wrong count of data into matrix");
    }
    _v.assign(ilist.begin(), ilist.end());
}

matrix operator+(const matrix& a, const matrix& b)
{
    if(a.row_count() != b.row_count() || a.col_count() != b.col_count()) {
        throw std::runtime_error("addition of matrices with non-equal size");
    }
    matrix tmp(a.row_count(), a.col_count());
    for(size_t i=0; i != b.size(); ++i) {
        tmp._v[i] = a._v[i] + b._v[i];
    }
    return tmp;
}

column_iterator matrix::column_begin(const size_t& j)
{
    return column_iterator(&_v[j], _m);
}

row_iterator matrix::row_begin(const size_t& i)
{
    return row_iterator(&_v[i*_m]);
}

column_iterator matrix::column_end(const size_t& j)
{
    return column_iterator(&_v[_n*_m+j]);
}

row_iterator matrix::row_end(const size_t& i)
{
    return row_iterator(&_v[i*_m+_m]);
}

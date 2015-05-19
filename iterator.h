#ifndef ITERATOR_H_INCLUDED
#define ITERATOR_H_INCLUDED

#include <cstddef> //for std::size_t

/*
* row_iterator declaration
*/
class iterator_base
{

public:

    iterator_base(double *begin, double *end, const std::size_t& jump_size=1)
            : _p{begin}, _end{end}, _diff{jump_size} {}
    iterator_base(const iterator_base& rh): _p{rh._p} {}
    bool operator==(const iterator_base& rh) {return _p == rh._p;}
    bool operator!=(const iterator_base& rh) {return _p != rh._p;}
    double& operator*() {return *_p;}
    virtual iterator_base& operator++()=0;

protected:

    double *_p;
    double *_end;
    std::size_t _diff; //the difference between two elements

};

class column: public iterator_base
{

public:

    column(double *p, const std::size_t& jump_size=1)
                : iterator_base(p, jump_size) {}
    column(const column& rh)
                : iterator_base(rh._p) {}

    column& operator++() {_p+=_diff; return *this;}

};

class row: public iterator_base
{

public:

    row(double *p, const std::size_t& jump_size=1)
                : iterator_base(p, jump_size) {}
    row(const row& rh)
                : iterator_base(rh._p) {}

    row& operator++() {++_p; return *this;}

};

#endif // ITERATOR_H_INCLUDED

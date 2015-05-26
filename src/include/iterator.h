#ifndef ITERATOR_H_INCLUDED
#define ITERATOR_H_INCLUDED

#include <cstddef> //for std::size_t
#include <iterator>

namespace optimization
{


   template <typename Value>
   class iterator
   {

   public:

      using iterator_type = iterator<Value>;
      using value_type = Value;
      using reference = Value&;
      using pointer = Value*;

      iterator(pointer begin, const std::size_t& jump_size=1)
            : _p {begin}/*, _end {end}*/, _diff {jump_size}
      {}
      iterator(const iterator& rh)
            : _p {rh._p}, _diff {rh._diff}
      {}

      //implicit conversion from a const iterator
      template <typename OtherType>
      iterator(iterator<OtherType>& other)
            : iterator(other._p, other._diff)
      {}

      iterator(): _p{nullptr}, _diff{1}
      {}

      bool operator==(const iterator<Value>& rh) const {return _p == rh._p;}
      bool operator!=(const iterator<Value>& rh) const {return _p != rh._p;}

      iterator_type operator=(const iterator_type& rh) {_p=rh._p; _diff=rh._diff;}

      reference operator*() const {return *_p;}

      iterator_type operator++() const {_p+=_diff; return *this;}

   protected:

      mutable pointer _p;
      std::size_t _diff; //the difference between two elements

   };

   using miterator = iterator<double>; //matrix iterator
   using miterator_const = iterator<double const>;

}

#endif // ITERATOR_H_INCLUDED

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

      iterator(pointer p, pointer end, const std::size_t& jump_size=1)
            : _p {p}, _end {end}, _diff {jump_size}
      {}
      iterator(const iterator& rh)
            : _p {rh._p}, _end{rh._end}, _diff {rh._diff}
      {}

      //implicit conversion from a const iterator
      template <typename OtherType>
      iterator(iterator<OtherType>& other)
            : iterator(other._p, other._end, other._diff)
      {}

      bool operator==(reference rh) const {return _p == rh._p;}
      bool operator!=(reference rh) const {return _p != rh._p;}

      bool ended() const {return _p == _end;}

      reference operator*() const {return *_p;}

      iterator_type operator++() {_p+=_diff; return *this;}

   protected:

      pointer _p;
      pointer _end;
      std::size_t _diff; //the difference between two elements

   };

   typedef iterator<double> miterator; //matrix iterator
   typedef iterator<double const> miterator_const;

}

#endif // ITERATOR_H_INCLUDED

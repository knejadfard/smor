#ifndef MATRIX_BASE_H_INCLUDED
#define MATRIX_BASE_H_INCLUDED

#include <vector>
#include <initializer_list>
#include <ostream>
#include <stdexcept>
#include "iterator.h"
#include "matrix_policy.h"

namespace optimization
{

   /*
   * A specialized 2d matrix class for use in optimization purposes
   */
   template <class StoragePolicy>
   class matrix
   {

   public:

      matrix()=delete; //disable default constructor, force the use of the following
      explicit matrix(const std::size_t&, const std::size_t&); //ordinary constructor
      //explicit matrix(const matrix&); //copy constructor
      template <class OtherStoragePolicy> matrix(OtherStoragePolicy const&);
      //matrix(matrix&&); //move constructor
      template <class OtherStoragePolicy> matrix(matrix<OtherStoragePolicy>&&);

      template <class OtherStoragePolicy> matrix& operator=(matrix<OtherStoragePolicy> const&); //copy assignment only for matrix types
      template <class OtherStoragePolicy> matrix& operator=(matrix<OtherStoragePolicy>&&); //move assignment

      double& operator()(const std::size_t&, const std::size_t&);
      const double& operator()(const std::size_t&, const std::size_t&) const;

      miterator cbegin(const std::size_t&);
      miterator_const cbegin(const std::size_t&) const;
      miterator rbegin(const std::size_t&);
      miterator_const rbegin(const std::size_t&) const;
      //virtual iterator begin(); //used for whole-matrix iteration

      void assign(std::initializer_list<double>);

      std::vector<double>& data(); //return a reference to the internal vector
      const std::vector<double>& data() const; //the const corrected version

      size_t row_count() const; //return the number of rows
      size_t col_count() const; //return the number of columns
      size_t size() const;

   protected:

      std::vector<double> _v; //a contiguous vector to hold the doubles
      std::size_t _n; //number of rows
      std::size_t _m; //number of columns
      StoragePolicy _sp; //provides proper indexing functionality

   };

   //There are only two valid types
   //so the template parameters should be bound
   template class matrix<rw_storage>;
   template class matrix<cw_storage>;
   //Convenient names to be used
   using rmatrix = matrix<rw_storage>;
   using cmatrix = matrix<cw_storage>;


   /******************
      Definitions
   ******************/
   template <class StoragePolicy>
   matrix<StoragePolicy>::matrix(const size_t& rows, const size_t& cols)
      : _v(rows*cols),
        _n {rows},
        _m {cols},
        _sp{rows, cols} {
      //nothing to do here
   }

   /*template <class StoragePolicy>
   matrix<StoragePolicy>::matrix(const matrix<StoragePolicy>& rh): matrix(rh._n, rh._m)
   {
      _v = rh._v;
   }*/

   template <class StoragePolicy>
   template <class OtherStoragePolicy>
   matrix<StoragePolicy>::matrix(OtherStoragePolicy const& rh): matrix(rh.row_count(), rh.col_count())
   {
      for(std::size_t j=0; j<rh.row_count(); ++j) {
         miterator it1 = rbegin(j);
         for(miterator_const it2=rh.rbegin(j); !it1.ended() && !it2.ended(); ++it1, ++it2) {
            *it1 = *it2;
         }
      }
   }

   /*template <class StoragePolicy>
   matrix<StoragePolicy>::matrix(matrix<StoragePolicy>&& rval)
      : _v {std::move(rval._v)},
        _n {rval._n},
        _m {rval._m},
        _sp{rval._n, rval._m} {
      //no need to do anything special here
   }*/

   template <class StoragePolicy>
   template <class OtherStoragePolicy>
   matrix<StoragePolicy>::matrix(matrix<OtherStoragePolicy>&& rval)
      : _v {std::move(rval.data())},
        _n {rval.row_count()},
        _m {rval.col_count()},
        _sp{rval.row_count(), rval.col_count()} {
      //no need to do anything special here
   }

   template <class StoragePolicy>
   template <class OtherStoragePolicy>
   matrix<StoragePolicy>& matrix<StoragePolicy>::operator=(matrix<OtherStoragePolicy> const& rh)
   {
      if(_n == rh._n || _m == rh._m) {
         _v = rh._v;
      } else {
         throw std::runtime_error("assignment of matrices with non-equal size");
      }
      return *this;
   }

   template <class StoragePolicy>
   template <class OtherStoragePolicy>
   matrix<StoragePolicy>& matrix<StoragePolicy>::operator=(matrix<OtherStoragePolicy>&& rh)
   {
      if(_n == rh._n || _m == rh._m) {
         _v = std::move(rh._v);
      } else {
         throw std::runtime_error("assignment of matrices with non-equal size");
      }
      return *this;
   }

   template <class StoragePolicy>
   size_t matrix<StoragePolicy>::row_count() const
   {
      return _n;
   }

   template <class StoragePolicy>
   size_t matrix<StoragePolicy>::col_count() const
   {
      return _m;
   }

   template <class StoragePolicy>
   size_t matrix<StoragePolicy>::size() const
   {
      return _v.size();
   }

   template <class StoragePolicy>
   double& matrix<StoragePolicy>::operator()(const size_t& i, const size_t& j)
   {
      return _v.at(_sp.linear_index(i, j));
   }

   template <class StoragePolicy>
   const double& matrix<StoragePolicy>::operator()(const size_t& i, const size_t& j) const
   {
      return _v.at(_sp.linear_index(i, j));
   }

   template <class StoragePolicy>
   void matrix<StoragePolicy>::assign(std::initializer_list<double> ilist)
   {
      if(ilist.size() != this->size()) {
         throw std::runtime_error("inserting wrong count of data into matrix");
      }
      _v.assign(ilist.begin(), ilist.end());
   }

   template <class StoragePolicy>
   miterator matrix<StoragePolicy>::cbegin(const size_t& j)
   {
      return miterator(&_v[_sp.column_begin(j)], &_v[_sp.column_end(j)], _sp.column_diff());
   }

   template <class StoragePolicy>
   miterator matrix<StoragePolicy>::rbegin(const size_t& i)
   {
      return miterator(&_v[_sp.row_begin(i)], &_v[_sp.row_end(i)], _sp.row_diff());
   }

   template <class StoragePolicy>
   miterator_const matrix<StoragePolicy>::cbegin(const size_t& j) const
   {
      return miterator_const(&_v[_sp.column_begin(j)], &_v[_sp.column_end(j)], _sp.column_diff());
   }

   template <class StoragePolicy>
   miterator_const matrix<StoragePolicy>::rbegin(const size_t& i) const
   {
      return miterator_const(&_v[_sp.row_begin(i)], &_v[_sp.row_end(i)], _sp.row_diff());
   }

   template <class StoragePolicy>
   std::vector<double>& matrix<StoragePolicy>::data()
   {
      return _v;
   }

   template <class StoragePolicy>
   const std::vector<double>& matrix<StoragePolicy>::data() const
   {
      return _v;
   }


   /************************************************
      Helper functions which are not class members
   ************************************************/

   template <class T>
   std::ostream& operator<<(std::ostream& o, matrix<T> const& m)
   {
      for(std::size_t r=0; r<m.row_count(); ++r) {
         for(miterator_const i=m.rbegin(r); !i.ended(); ++i) {
            o<<*i<<" ";
         }
         o<<"\n";
      }
      o<<"\n";
      return o;
   }

   template <typename T1, typename T2>
   matrix<T1> operator+(matrix<T1> const& lh, matrix<T2> const& rh)
   {
      if(lh.row_count() != rh.row_count() || lh.col_count() != rh.col_count()) {
         throw std::runtime_error("addition of matrices with non-equal size");
      }
      matrix<T1> tmp(lh);
      for(std::size_t r=0; r<lh.row_count(); ++r) {
         miterator i = tmp.rbegin(r);
         miterator_const j = rh.rbegin(r);
         for(; !i.ended() && !j.ended(); ++i, ++j) {
            *i += *j;
         }
      }
      return tmp;
   }

   template <typename T1, typename T2>
   matrix<T1> operator-(matrix<T1> const& lh, matrix<T2> const& rh)
   {
      if(lh.row_count() != rh.row_count() || lh.col_count() != rh.col_count()) {
         throw std::runtime_error("addition of matrices with non-equal size");
      }
      matrix<T1> tmp(lh);
      for(std::size_t r=0; r<lh.row_count(); ++r) {
         miterator i = tmp.rbegin(r);
         miterator_const j = rh.rbegin(r);
         for(; !i.ended() && !j.ended(); ++i, ++j) {
            *i -= *j;
         }
      }
      return tmp;
   }


}

#endif // MATRIX_H_INCLUDED

#ifndef MATRIX_POLICY_H_INCLUDED
#define MATRIX_POLICY_H_INCLUDED

#include <cstddef>

namespace optimization
{

   class rw_storage
   {
   public:
      rw_storage(std::size_t const& row_count, std::size_t const& column_count): _n{row_count}, _m{column_count}
      {}
      std::size_t linear_index(std::size_t const& i, std::size_t const& j) const
      {
         return i*_m + j;
      }
      std::size_t column_begin(std::size_t const& j) const
      {
         return j;
      }
      std::size_t column_end(std::size_t const& j) const
      {
         return _n*_m + j;
      }
      std::size_t column_diff() const
      {
         return _m;
      }
      std::size_t row_begin(std::size_t const& i) const
      {
         return i*_m;
      }
      std::size_t row_end(std::size_t const& i) const
      {
         return i*_m + _m;
      }
      std::size_t row_diff() const
      {
         return 1;
      }
   private:
      std::size_t _n; //number of rows
      std::size_t _m; //number of columns

   };

   class cw_storage
   {
   public:
      cw_storage(std::size_t const& row_count, std::size_t const& column_count): _n{row_count}, _m{column_count}
      {}
      std::size_t linear_index(std::size_t const& i, std::size_t const& j) const
      {
         return j*_n + i;
      }
      std::size_t column_begin(std::size_t const& j) const
      {
         return j*_n;
      }
      std::size_t column_end(std::size_t const& j) const
      {
         return j*_n + _n;
      }
      std::size_t column_diff() const
      {
         return 1;
      }
      std::size_t row_begin(std::size_t const& i) const
      {
         return i;
      }
      std::size_t row_end(std::size_t const& i) const
      {
         return i + _n*_m;
      }
      std::size_t row_diff() const
      {
         return _n;
      }
   private:
      std::size_t _n; //number of rows
      std::size_t _m; //number of columns

   };

}

#endif // MATRIX_POLICY_H_INCLUDED

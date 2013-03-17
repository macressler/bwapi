#pragma once
#include <functional>

namespace BWAPI
{
  template<typename _PARAM>
  class UnaryFilter
  {
  private:
    std::function<bool(_PARAM)> pred;
  public:
    // Constructor
    template <typename _T>
    UnaryFilter(const _T& predicate) : pred(predicate)
    {};

    // Copy ctor
    UnaryFilter(const UnaryFilter &other)
      : pred(other.pred)
    {};

    // Move ctor
    UnaryFilter(UnaryFilter &&other)
      : pred( std::move(other.pred) )
    {};

    // Assignment
    template <typename _T>
    UnaryFilter &operator =(const _T& other)
    {
      this->pred = other;
      return *this;
    };

    // Copy assignment
    UnaryFilter &operator =(UnaryFilter other)
    {
      swap(*this, other);
      return *this;
    };
    // Move assignment
    UnaryFilter &operator =(UnaryFilter &&other)
    {
      swap(*this, other);
      return *this;
    };
    
    // logical operators    
    template <typename _T>
    inline UnaryFilter operator &&(const _T& other) const
    {
      return [&](_PARAM u){ return (*this)(u) && other(u); };
    };
    template <typename _T>
    inline UnaryFilter operator ||(const _T& other) const
    {
      return [&](_PARAM u){ return (*this)(u) || other(u); };
    };
    inline UnaryFilter operator !() const
    {
      if ( !this->pred )
        return nullptr;
      return std::not1(this->pred);
    };

    // call
    inline bool operator()(_PARAM u) const
    {
      return pred(u);
    };

    // operator bool
    inline bool isValid() const
    {
      return (bool)pred;
    };

    friend void swap(UnaryFilter<_PARAM> &a, UnaryFilter<_PARAM> &b);
  };

  template <typename P>
  inline void swap(UnaryFilter<P> &a, UnaryFilter<P> &b)
  {
    std::swap(a.pred, b.pred);
  }
}

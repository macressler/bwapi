#pragma once
#include <functional>

namespace BWAPI
{
  template <typename PARAM>
  class UnaryFilter_AndCombiner
  {
  public:
    template <typename T, typename T2>
    UnaryFilter_AndCombiner(const T& p1, const T2& p2) 
      : pred1(p1), pred2(p2)
    {}
    
    bool operator()(PARAM u)
    {
      return pred1(u) && pred2(u);
    }
  private:
    std::function<bool(PARAM)> pred1;
    std::function<bool(PARAM)> pred2;
  };

  template <typename PARAM>
  class UnaryFilter_OrCombiner
  {
  public:
    template <typename T, typename T2>
    UnaryFilter_OrCombiner(const T& p1, const T2& p2) 
      : pred1(p1), pred2(p2)
    {}
    
    bool operator()(PARAM u)
    {
      return pred1(u) || pred2(u);
    }
  private:
    std::function<bool(PARAM)> pred1;
    std::function<bool(PARAM)> pred2;
  };

  template<typename PARAM>
  class UnaryFilter
  {
  private:
    std::function<bool(PARAM)> pred;
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
      //return [=](PARAM u){ return (*this)(u) && other(u); };
      return UnaryFilter_AndCombiner<PARAM>(pred, other);
    };
    template <typename _T>
    inline UnaryFilter operator ||(const _T& other) const
    {
      //return [=](PARAM u){ return (*this)(u) || other(u); };
      return UnaryFilter_OrCombiner<PARAM>(pred,other);
    };
    inline UnaryFilter operator !() const
    {
      if ( !this->pred )
        return nullptr;
      return std::not1(this->pred);
    };

    // call
    inline bool operator()(PARAM u) const
    {
      return pred(u);
    };

    // operator bool
    inline bool isValid() const
    {
      return (bool)pred;
    };

    friend void swap(UnaryFilter<PARAM> &a, UnaryFilter<PARAM> &b);
  };

  template <typename P>
  inline void swap(UnaryFilter<P> &a, UnaryFilter<P> &b)
  {
    std::swap(a.pred, b.pred);
  }
}

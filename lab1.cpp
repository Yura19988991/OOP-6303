#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>

template<typename T>
class Array
{
public:
  // (default) constructor
  Array(const size_t size = 0)
    : m_size(size)
    , m_array(m_size ? new T[m_size]() : nullptr)
  {
  }

  const size_t size() const
  {
    return m_size;
  }

  T& operator [](const size_t index)
  {
    assert(index < m_size);

    return m_array[index];
  }
    Array (const Array & object) : m_size(object.size()) , m_array(m_size ? new T[m_size]() : nullptr)
   {
     std::copy(object.m_array.get(), object.m_array.get() + object.size(), m_array.get());
   }

   Array (Array && object)
   {
     m_array.reset(object.m_array.release());
     m_size = object.m_size;
     object.m_size = 0;
   }

   Array & operator = (Array object)
   {
     std::swap(m_size, object.m_size);
     std::swap(m_array, object.m_array);
     return *this;
   }

 private:
   size_t m_size;
   std::unique_ptr<T[]> m_array;
 };

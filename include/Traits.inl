#ifdef __INTELLISENSE__
#include "Traits.hpp"
#endif

namespace fridayc {

  template<class T>
  constexpr auto Container<T>::add(T arg) noexcept -> void {
    values.push_back(std::move(arg));
  }

  template<class T>
  constexpr auto Container<T>::begin() noexcept -> iterator {
    return values.begin();
  }

  template<class T>
  constexpr auto Container<T>::begin() const noexcept -> const_iterator {
    return values.cbegin();
  }

  template<class T>
  constexpr auto Container<T>::end() noexcept -> iterator {
    return values.end();
  }

  template<class T>
  constexpr auto Container<T>::end() const noexcept -> const_iterator {
    return values.cend();
  }

  template<class T>
  constexpr auto Container<T>::size() const noexcept -> u64 {
    return values.size();
  }

  template<class T>
  constexpr auto Container<T>::empty() const noexcept -> bool {
    return values.empty();
  }

  template<class T>
  constexpr auto Container<T>::at(u64 index) -> value_type& {
    return values.at(index);
  }

  template<class T>
  constexpr auto Container<T>::at(u64 index) const -> value_type const& {
    return values.at(index);
  }

  template<class T>
  constexpr auto Container<T>::operator[](u64 index) noexcept -> value_type& {
    return values[index];
  }

  template<class T>
  constexpr auto Container<T>::operator[](u64 index) const noexcept -> value_type const& {
    return values[index];
  }  
}
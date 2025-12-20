#ifndef FRIDAYC_FUNCTORS_HPP
#define FRIDAYC_FUNCTORS_HPP

template<class T>
struct Constructor {
  template<class... Args>
  requires std::constructible_from<T, Args...>
  constexpr auto operator()(Args&& ...args) const -> T {
    return T(std::forward<Args>(args)...);
  }
};

#endif
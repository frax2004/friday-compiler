#pragma once

namespace fridayc {

  inline namespace math {
    using std::cos;
    using std::sin;
    using std::tan;
    using std::acos;
    using std::asin;
    using std::atan;
    using std::atan2;
    using std::pow;
    using std::sqrt;
    using std::cbrt;
    using std::exp;
    using std::log;
    using std::log2;
    using std::log10;
    using std::lerp;
    using std::clamp;
    using std::max;
    using std::min;
    using std::abs;
    using std::hypot;
    using std::ceil;
    using std::floor;
    using std::round;
    using std::trunc;
    using std::copysign;
    using std::isfinite;
    using std::isinf;
    using std::isnan;
  
    using std::numbers::e;
    using std::numbers::log2e;
    using std::numbers::log10e;
    using std::numbers::pi;
    using std::numbers::inv_pi;
    using std::numbers::inv_sqrtpi;
    using std::numbers::ln2;
    using std::numbers::ln10;
    using std::numbers::sqrt2;
    using std::numbers::sqrt3;
    using std::numbers::inv_sqrt3;
    using std::numbers::egamma;
    using std::numbers::phi;
  }

  inline namespace traits {
    template<class T>
    concept Stringable = requires (T object) {
      { object.toString() } -> std::convertible_to<std::string>;
    };
  }

  inline namespace utility {
    template<class... Overloads>
    constexpr auto overload(Overloads&& ...overloads) {
      struct overload_result_t : public Overloads... {
        using Overloads::operator()...;
      };
      return overload_result_t{};
    }
  }

  inline namespace containers {
    template<class T>
    struct SequenceContainer {
      using value_type = T;
      using iterator = typename std::vector<value_type>::iterator;
      using const_iterator = typename std::vector<value_type>::const_iterator;
    
      constexpr auto add(T arg) noexcept -> void {
        this->values.push_back(std::move(arg));
      }
      
      constexpr auto begin() noexcept -> iterator {
        return this->values.begin();
      }
      
      constexpr auto begin() const noexcept -> const_iterator {
        return this->values.begin();
      }
      
      constexpr auto end() noexcept -> iterator {
        return this->values.end();
      }
      
      constexpr auto end() const noexcept -> const_iterator {
        return this->values.end();
      }
      
      constexpr auto size() const noexcept -> u64 {
        return this->values.size();
      }
      
      constexpr auto empty() const noexcept -> bool {
        return this->values.empty();
      }
      
      constexpr auto at(u64 index) -> value_type& {
        return this->values.at(index);
      }
      
      constexpr auto at(u64 index) const -> value_type const& {
        return this->values.at(index);
      }
      
      constexpr auto operator[](u64 index) noexcept -> value_type& {
        return this->values[index];
      }
      
      constexpr auto operator[](u64 index) const noexcept -> value_type const& {
        return this->values[index];
      }
    
      private:
      std::vector<T> values;
    };
  }

}

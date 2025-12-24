#pragma once


namespace fridayc {
  struct Error {
    std::string message;
    u32 row;
    u32 col;
    u32 length;

    constexpr Error(std::string error, u32 row, u32 col, u32 length) noexcept;
  };

  struct RuntimeError : public Error {
    
  };

  struct SyntaxError : public Error {
    
  };

  struct SemanticError : public Error {
    
  };

  struct AllocationError : public RuntimeError {
    
  };

  struct IndexError : public RuntimeError {
    
  };

  struct TypeCastError : public RuntimeError {
    
  };

}

#include "Error.inl"
/**
  ********************************************************************************
  * @file           : macro.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/29
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef MACRO_H
#define MACRO_H


#if defined(__cplusplus) && __cplusplus >= 201703L
#define NODISCARD [[nodiscard]]
#define MAYBE_UNUSED [[maybe_unused]]
#else
#define NODISCARD
#define MAYBE_UNUSED
#endif

#endif //MACRO_H

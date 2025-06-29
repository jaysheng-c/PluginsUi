/**
  ********************************************************************************
  * @file           : global.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/06/28
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef CORE_GLOBAL_H
#define CORE_GLOBAL_H

#include "../macro.h"

#if defined(CORE_LIBRARY)
#define CORE_EXPORT Q_DECL_EXPORT
#else
#define CORE_EXPORT Q_DECL_IMPORT
#endif




#endif //CORE_GLOBAL_H

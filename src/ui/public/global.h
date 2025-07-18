/**
  ********************************************************************************
  * @file           : global.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/14
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef GLOBAL_H
#define GLOBAL_H

#ifdef UI_LIBRARY
#define UI_EXPORT Q_DECL_EXPORT
#else
#define UI_EXPORT Q_DECL_IMPORT
#endif

#endif //GLOBAL_H

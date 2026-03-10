/*
 * Log.hpp
 *
 *  Created on: 15 sty 2026
 *      Author: User
 */

#ifndef LIB_LOG_LOG_HPP_
#define LIB_LOG_LOG_HPP_

#include "Logger.hpp"

extern Logger GlobalLogger;

#ifndef GLOBAL_LOGGER_LEVEL
#define GLOBAL_LOGGER_LEVEL LOGGER_LEVEL_DEBUG
#endif

#if GLOBAL_LOGGER_LEVEL >= LOGGER_LEVEL_ERROR
#define LOGE(TAG, FORMAT, ...) GlobalLogger.log(Logger::Level::ERROR_, TAG, FORMAT , ##__VA_ARGS__)
#define LOGE_BUFFER_HEX(TAG, BUFFER, LEN) GlobalLogger.bufferHex(Logger::Level::ERROR_, TAG, BUFFER, LEN)
#else
#define LOGE(TAG, FORMAT, ...)
#define LOGE_BUFFER_HEX(TAG, BUFFER, LEN)
#endif

#if GLOBAL_LOGGER_LEVEL >= LOGGER_LEVEL_WARNING
#define LOGW(TAG, FORMAT, ...) GlobalLogger.log(Logger::Level::WARNING_, TAG, FORMAT , ##__VA_ARGS__)
#define LOGW_BUFFER_HEX(TAG, BUFFER, LEN) GlobalLogger.bufferHex(Logger::Level::WARNING_, TAG, BUFFER, LEN)
#else
#define LOGW(TAG, FORMAT, ...)
#define LOGW_BUFFER_HEX(TAG, BUFFER, LEN)
#endif

#if GLOBAL_LOGGER_LEVEL >= LOGGER_LEVEL_INFO
#define LOGI(TAG, FORMAT, ...) GlobalLogger.log(Logger::Level::INFO_, TAG, FORMAT , ##__VA_ARGS__)
#define LOGI_BUFFER_HEX(TAG, BUFFER, LEN) GlobalLogger.bufferHex(Logger::Level::INFO_, TAG, BUFFER, LEN)
#else
#define LOGI(TAG, FORMAT, ...)
#define LOGI_BUFFER_HEX(TAG, BUFFER, LEN)
#endif

#if GLOBAL_LOGGER_LEVEL >= LOGGER_LEVEL_DEBUG
#define LOGD(TAG, FORMAT, ...) GlobalLogger.log(Logger::Level::DEBUG_, TAG, FORMAT , ##__VA_ARGS__)
#define LOGD_BUFFER_HEX(TAG, BUFFER, LEN) GlobalLogger.bufferHex(Logger::Level::DEBUG_, TAG, BUFFER, LEN)
#else
#define LOGD(TAG, FORMAT, ...)
#define LOGD_BUFFER_HEX(TAG, BUFFER, LEN)
#endif

#if GLOBAL_LOGGER_LEVEL >= LOGGER_LEVEL_VERBOSE
#define LOGV(TAG, FORMAT, ...) GlobalLogger.log(Logger::Level::VERBOSE_, TAG, FORMAT , ##__VA_ARGS__)
#define LOGV_BUFFER_HEX(TAG, BUFFER, LEN) GlobalLogger.bufferHex(Logger::Level::VERBOSE_, TAG, BUFFER, LEN)
#else
#define LOGV(TAG, FORMAT, ...)
#define LOGV_BUFFER_HEX(TAG, BUFFER, LEN)
#endif

#endif /* LIB_LOG_LOG_HPP_ */

/*
 * Log.hpp
 *
 *  Created on: 15 sty 2026
 *      Author: User
 */

#ifndef LIB_LOG_LOGGER_HPP_
#define LIB_LOG_LOGGER_HPP_

#include <functional>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define LOGGER_LEVEL_ERROR 0
#define LOGGER_LEVEL_WARNING 1
#define LOGGER_LEVEL_INFO 2
#define LOGGER_LEVEL_DEBUG 3
#define LOGGER_LEVEL_VERBOSE 4

class Logger {
public:
    enum class Level { ERROR_ = LOGGER_LEVEL_ERROR, WARNING_ = LOGGER_LEVEL_WARNING, INFO_ = LOGGER_LEVEL_INFO, DEBUG_ = LOGGER_LEVEL_DEBUG, VERBOSE_ = LOGGER_LEVEL_VERBOSE };
    typedef std::function<void(char*, size_t)> PrintFun;
    typedef std::function<uint32_t()> TickFun;

    Logger(PrintFun printFun, TickFun tickFun, size_t bigBufferSize = 256)
        : printFun(printFun)
        , tickFun(tickFun)
        , bigBufferSize(bigBufferSize) {

        bigBuffer = new char[bigBufferSize];
    }
    ~Logger() { delete[] bigBuffer; }


    void log(Level lvl, const char* TAG, const char* format, ...) {
        va_list args;
        va_start(args, format);
        log(lvl, TAG, format, args);
        va_end(args);
    }

    void log(Level lvl, const char* TAG, const char* format, va_list args) {

        size_t writted = vsnprintf(bigBuffer, bigBufferSize, format, args);
        write(lvl, TAG, bigBuffer, writted);
    }

    void bufferHex(Level lvl, const char* TAG, void* buffer, size_t len) {
        size_t buflen = (len * 4);
        char buf[buflen];
        size_t pos = 0;

        for (size_t q = 1; q <= len; q++) {
            pos += snprintf(buf + pos, buflen - pos, "%02X ", ((uint8_t*)buffer)[q - 1]);

            if (q % 16 == 0) {
                write(lvl, TAG, buf, pos);
                pos = 0;
            }
        }

        if (pos)
            write(lvl, TAG, buf, pos);
    }

    void error(const char* TAG, const char* format, va_list args) { log(Level::ERROR_, TAG, format, args); }
    void error(const char* TAG, const char* format, ...) {
        va_list args;
        va_start(args, format);
        log(Level::ERROR_, TAG, format, args);
        va_end(args);
    }

    void warning(const char* TAG, const char* format, va_list args) { log(Level::WARNING_, TAG, format, args); }
    void warning(const char* TAG, const char* format, ...) {
        va_list args;
        va_start(args, format);
        log(Level::WARNING_, TAG, format, args);
        va_end(args);
    }

    void info(const char* TAG, const char* format, va_list args) { log(Level::INFO_, TAG, format, args); }
    void info(const char* TAG, const char* format, ...) {
        va_list args;
        va_start(args, format);
        log(Level::INFO_, TAG, format, args);
        va_end(args);
    }

    void debug(const char* TAG, const char* format, va_list args) { log(Level::DEBUG_, TAG, format, args); }
    void debug(const char* TAG, const char* format, ...) {
        va_list args;
        va_start(args, format);
        log(Level::DEBUG_, TAG, format, args);
        va_end(args);
    }

    void verbose(const char* TAG, const char* format, va_list args) { log(Level::VERBOSE_, TAG, format, args); }
    void verbose(const char* TAG, const char* format, ...) {
        va_list args;
        va_start(args, format);
        log(Level::VERBOSE_, TAG, format, args);
        va_end(args);
    }

private:
    constexpr static const char* LOG_LEVEL_COLORS[6] = { "\e[0;31m", "\e[0;33m", "\e[0;32m", "\e[0;36m", "\e[0;35m", "" };

    PrintFun printFun;
    TickFun tickFun;

    char* bigBuffer;
    size_t bigBufferSize;


    void write(Level lvl, const char* TAG, char* data, size_t dataLen) {

        size_t buflen = 64;
        char buffer[buflen];

        uint32_t m = tickFun();

        size_t s = snprintf(buffer, buflen, "%s(%04lu.%03lu) %9s -> ", LOG_LEVEL_COLORS[(uint8_t)lvl], m / 1000, m % 1000, TAG);
        printFun(buffer, s);

        printFun(data, dataLen);

        s = snprintf(buffer, buflen, "\e[0m\r\n");
        printFun(buffer, s);
    }
};

#endif /* LIB_LOG_LOGGER_HPP_ */

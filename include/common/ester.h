#pragma once

#ifndef ORCA_LOGGING_H
#define ORCA_LOGGING_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

typedef enum
{
    ORCA_ERROR = -1,
    ORCA_INFO,
    ORCA_WARN,
    ORCA_DEBUG
} orca_log_level_t;

typedef struct
{
    const char* ctx;
    const char* filename;
} orca_logger_t;

typedef enum
{
    ORCA_STDOUT,
    ORCA_FILE,
    ORCA_ALL
}orca_stream_t;

void orca_log(const orca_logger_t*,
               const orca_log_level_t,
               const orca_stream_t,
               const char*,
               const char*,
               const int,
               const char*,
               ...);

void orca_printer(FILE* log_stream,
                   const char* ctx,
                   const char* logtag,
                   const char* filename,
                   const char* function,
                   const int line,
                   const char* format,
                   va_list args);

#define ORCA_LOG(logger,level,stream,format,...) \
        orca_log(&logger, \
                  level, \
                  stream, \
                  (const char*)__FILE_NAME__, \
                  (const char*)__FUNCTION__, \
                  (const int)__LINE__, \
                  (const char*)format, \
                  ##__VA_ARGS__)

#define ORCA_LOG_WARN(logger,format,...) \
        ORCA_LOG(logger,ORCA_WARN,ORCA_STDOUT,format, ##__VA_ARGS__)

#define ORCA_LOG_INFO(logger,format,...) \
        ORCA_LOG(logger,ORCA_INFO,ORCA_STDOUT,format, ##__VA_ARGS__)

#define ORCA_LOG_ERR(logger,format,...) \
        ORCA_LOG(logger,ORCA_ERROR,ORCA_STDOUT,format, ##__VA_ARGS__)

#define ORCA_LOGF_WARN(logger,format,...) \
        ORCA_LOG(logger,ORCA_WARN,ORCA_FILE,format, ##__VA_ARGS__)

#define ORCA_LOGF_INFO(logger,format,...) \
        ORCA_LOG(logger,ORCA_INFO,ORCA_FILE,format, ##__VA_ARGS__)

#define ORCA_LOGF_ERR(logger,format,...) \
        ORCA_LOG(logger,ORCA_ERROR,ORCA_FILE,format, ##__VA_ARGS__)

#define ORCA_LOGM_WARN(logger,format,...) \
        ORCA_LOG(logger,ORCA_WARN,ORCA_ALL,format, ##__VA_ARGS__)

#define ORCA_LOGM_INFO(logger,format,...) \
        ORCA_LOG(logger,ORCA_INFO,ORCA_ALL,format, ##__VA_ARGS__)

#define ORCA_LOGM_ERR(logger,format,...) \
        ORCA_LOG(logger,ORCA_ERROR,ORCA_ALL,format, ##__VA_ARGS__)

#define ORCA_ABORT(logger,format,...) \
     do \
     { \
        ORCA_LOGM_ERR(logger,format,##__VA_ARGS__); \
        abort(); \
     }while(0)

#endif

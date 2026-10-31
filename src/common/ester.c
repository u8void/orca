#include <common/ester.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void orca_log (const orca_logger_t* logger,
                const orca_log_level_t level,
                const orca_stream_t stream,
                const char* filename,
                const char* function,
                const int line,
                const char* format,
                ...)
{


    va_list args_for_file;
    va_list args;
    va_start(args, format);
    va_copy(args_for_file, args);
    const char* logtag = NULL;

    switch (level)
    {
        case ORCA_INFO: logtag = "INFO";
        break;

        case ORCA_WARN: logtag = "WARN";
        break;

        case ORCA_ERROR: logtag = "ERROR";
        break;

        case ORCA_DEBUG: logtag = "DEBUG";
        break;

        default: NULL;
    }

    if (logtag == NULL)
    {
        va_end(args_for_file);
        va_end(args);
        return;
    }

    FILE *log_stream = NULL;

    switch (stream)
    {
        case ORCA_STDOUT:
        {
            orca_printer(stdout,
                         logger->ctx,
                         logtag,
                         filename,
                         function,
                         line,
                         format,
                         args);
        }



        break;

        case ORCA_FILE:
        {
            log_stream = fopen(logger->filename,"a+");
            orca_printer(log_stream,
                         logger->ctx,
                         logtag,
                         filename,
                         function,
                         line,
                         format,
                         args);
        }
        break;

        case ORCA_ALL:
        {
            orca_printer(stdout,
                          logger->ctx,
                          logtag,
                          filename,
                          function,
                          line,
                          format,
                          args);

            log_stream = fopen(logger->filename,"a+");
            orca_printer(log_stream,
                         logger->ctx,
                         logtag,
                         filename,
                         function,
                         line,
                         format,
                         args);
        }

        break;

        default: orca_printer(stdout,
            logger->ctx,
            logtag,
            filename,
            function,
            line,
            format,
            args);
    }

    va_end(args_for_file);
    va_end(args);

    if (log_stream == NULL)
    {
        return;
    }
    fclose(log_stream);

}

__attribute__((format(printf, 7, 0)))
void orca_printer(FILE* log_stream,
                   const char* ctx,
                   const char* logtag,
                   const char* filename,
                   const char* function,
                   const int line,
                   const char* format,
                   va_list args)
{

    if (log_stream == NULL)
    {
        return;
    }

    fprintf(log_stream,"{%s} [%s] %s->%s:%d ",ctx,logtag,filename,function,line);
    vfprintf(log_stream,format, args);
    fprintf(log_stream,"\n");
    fflush(log_stream);
}

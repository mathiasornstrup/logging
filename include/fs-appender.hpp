#pragma once

#include <FS.h>

#include "logging.hpp"

namespace esp32m
{

    /**
     * Sends output file system (SD, SPIFFS or other)
     */
    class FSAppender : public FormattingAppender
    {
    public:
        FSAppender(FS &fs, const char *name, uint8_t maxFiles = 1, uint32_t maxFileLen = 100000) : _fs(fs), _name(name), _maxFiles(maxFiles), _maxFileLen(maxFiles), _lock(xSemaphoreCreateRecursiveMutex()) {}
        FSAppender(const FSAppender &) = delete;

    protected:
        virtual bool append(const char *message);
        virtual bool shouldRotate(File &f) { return f.size() > 8192; }
        virtual void close() { return _file.close(); }

    private:
        FS &_fs;
        File _file;
        const char *_name;
        uint8_t _maxFiles;
        uint32_t _maxFileLen;
        SemaphoreHandle_t _lock;
    };

} // namespace esp32m

#ifndef _MP4_COMMON_H
#define _MP4_COMMON_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>

#include <ts/ts.h>
#include <ts/experimental.h>
#include <ts/remap.h>
#include "mp4_meta.h"


class IOHandle
{
public:
    IOHandle(): vio(NULL), buffer(NULL), reader(NULL)
    {
    }

    ~IOHandle()
    {
        if (reader) {
            TSIOBufferReaderFree(reader);
            reader = NULL;
        }

        if (buffer) {
            TSIOBufferDestroy(buffer);
            buffer = NULL;
        }
    }

public:
    TSVIO               vio;
    TSIOBuffer          buffer;
    TSIOBufferReader    reader;
};

class Mp4TransformContext
{
public:
    Mp4TransformContext(int64_t offset, int64_t cl):
                total(0), tail(0), pos(0), content_length(0),
                parse_over(false), raw_transform(false)
    {
        res_buffer = TSIOBufferCreate();
        res_reader = TSIOBufferReaderAlloc(res_buffer);
        dup_reader = TSIOBufferReaderAlloc(res_buffer);

        mm.start = offset * 1000;      // 将跳转时间赋值给Mp4Context, 用于解析
        mm.cl = cl;                    // 将文件长度也设置好
    }

    ~Mp4TransformContext()
    {
        if (res_reader) {
            TSIOBufferReaderFree(res_reader);
        }

        if (dup_reader) {
            TSIOBufferReaderFree(dup_reader);
        }

        if (res_buffer) {
            TSIOBufferDestroy(res_buffer);
        }
    }

public:
    IOHandle            output;
    Mp4Meta             mm;
    int64_t             total;          // 向下游输出总量
    int64_t             tail;           // MP4剩余部分从哪里开始
    int64_t             pos;            // 数据已经走到的位置
    int64_t             content_length; // 重新生成的mp4的长度值
    int64_t             meta_length;    // 重新生成的mp4的meta长度

    TSIOBuffer          res_buffer;
    TSIOBufferReader    res_reader;
    TSIOBufferReader    dup_reader;     // 用于解析meta

    bool                parse_over;     // MP4的meta是否已经解析完毕
    bool                raw_transform;  // 是否原样输出(因为解析有问题)
};

class Mp4Context
{
public:
    Mp4Context(int s): start(s), cl(0), mtc(NULL), transform_added(false)
    {
    }

    ~Mp4Context() {}

public:
    int         start;
    int64_t     cl;

    Mp4TransformContext *mtc;

    bool        transform_added;
};

#endif


#ifndef __FILE_READER_H__
#define __FILE_READER_H__


#include <stdio.h>
//ver si se podia copiar tal cual
typedef struct {
  FILE* fp;
} file_reader_t;

int file_reader_init(file_reader_t* self, const char* file_name);
int file_reader_uninit(file_reader_t* self);
int file_reader_iterate(file_reader_t* self,file_reader_callback_t callback,void* callback_ctx);

#endif

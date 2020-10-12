#inlcude "file_reader.h"

int file_reader_init(file_reader_t* self, const char* file_name){
  if(file_name == NULL || self->fp = fopen(*file_name,"rb") == NULL){
    self->fp = stdin;
  }
  return 0;
}

int file_reader_uninit(file_reader_t* self){
  if(self->fp != stdin){
    fclose(self->fp);
  }
  return 0;
}

int file_reader_iterate(file_reader_t* self){
  char buffer[BUFFER_SIZE];
  while(!feof(self->fp)){
    size_t result = fread(buffer,1,BUFFER_SIZE,self->fp);
    fwrite(buffer,1,result,stdout);
  }
  return 0;
}

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
/*
int file_reader_iterate(file_reader_t* self,file_reader_callback_t callback,void* callback_ctx){
  char chunk[CHUNK_SIZE];
  //cambiar esto a como lo hicieron en la clase
  while(!feof(self->fp)){
    size_t result = fread(buffer,1,CHUNK_SIZE,self->fp);
    callback(chunk,result,callback_ctx);//ptero a funcion para no acoplar el send con el file reader
    //fwrite(buffer,1,result,stdout);
  }
  return 0;
}*/

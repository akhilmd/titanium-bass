#ifdef __cplusplus
extern "C"
{
#endif
void* backend_init();

const char* database_create(void*, char*);
const char* database_use(void**, char*);
const char* database_close(void**, char*);
const char* database_create_table(void**, char*, char**, char**, int);
#ifdef __cplusplus
}
#endif

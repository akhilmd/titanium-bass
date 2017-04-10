#ifdef __cplusplus
extern "C"
{
#endif
void* backend_init();

const char* database_create(void*, char*);
const char* database_use(void**, char*);
const char* database_close(void**, char*);
const char* database_create_table(void**, char*, char**, char**, int);
const char* database_select(void**, char*);
const char* database_select1(void**, char*, char**, int);
const char* database_select2(void**, char*, char*, char*);
const char* database_insert(void**, char*, char**, int);
const char* database_update(void**, char*, char*, char*, char*, char*);
#ifdef __cplusplus
}
#endif

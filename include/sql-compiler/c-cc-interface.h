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
const char* database_select3(void** db, char* table_name, char** col_names, int noc, char* where_column, char* where_item);
const char* database_insert(void**, char*, char**, int);
const char* database_update(void**, char*, char*, char*, char*, char*);
const char* database_delete(void**, char*);
const char* database_delete1(void**, char*, char*, char*);
const char* database_table_drop(void**, char*);
const char* database_drop(void**, char*);
const char* database_start_transaction(void** db);
const char* database_commit_transaction(void** db);
const char* database_rollback_transaction(void** db);
#ifdef __cplusplus
}
#endif

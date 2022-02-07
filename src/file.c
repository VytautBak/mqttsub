#include "file.h"


int write_to_file(char *message, char *topic) {
    char time[100];
    get_formatted_time(time);

    sqlite3 *db;
    char *err_msg = 0;
    
    int rc = sqlite3_open(LOG_FILE, &db);
    
    if (rc != SQLITE_OK) {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        
        return 1;
    }
    char sql[512];
    sprintf(sql, "CREATE TABLE IF NOT EXISTS Messages(Time TEXT, Topic TEXT, Message TEXT);" 
                "INSERT INTO Messages VALUES('%s', '%s', '%s');", time, topic, message);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "ERROR: %s\n", err_msg);
        
        sqlite3_free(err_msg);        
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    
    return 0;
}

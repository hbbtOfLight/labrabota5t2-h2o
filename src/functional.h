#pragma once
#include <sqlite3.h>

sqlite3* open_data_base();
void select_data(sqlite3* db, char* sql);
void select_by_each_driver(sqlite3* db, char* driver);
void select_by_car(sqlite3* db, char* car, char* driver);
void select_by_driver(sqlite3* db, char* driver);
void select_by_min_driver(sqlite3* db);
void select_by_max_car(sqlite3* db, char* driver);
void update_data(sqlite3* db);
void delete_data(sqlite3* db);

void insert_to_driver(sqlite3* db);
void insert_to_orders(sqlite3* db);
void insert_to_cars(sqlite3* db);
int check_order(sqlite3* db, int gruz, char* num_machine);

void money(sqlite3* db, char* begin_date, char* end_date);
void money_by_driver(sqlite3* db, char* begin_date, char* end_date, char* driver_name);
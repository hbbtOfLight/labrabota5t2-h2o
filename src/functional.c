#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include <string.h>
#include "functional.h"

static int callback(void *data, int argc, char **argv, char **azColName) {
   int i;
   if(data!=0)
      fprintf(stderr, "%s: ", (const char*)data);

   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

void Error_Message(int rc, char* zErrMsg, char* Msg)
{
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "%s\n", Msg);
   }
}

sqlite3* open_data_base() {
   sqlite3 *f;
   ///////////////////////////
   int rc = sqlite3_open("park.db", &f);

   if(rc) {
      fprintf(stderr, "Can't open database\n");
   } else {
      fprintf(stderr, "Opened database successfully\n");
   };
   return f;
}

void select_by_driver(sqlite3* db, char* driver)
{
   char* sql1 = "SELECT * FROM PARK_ORDERS where last_name = '";
   char sql[100];
   snprintf(sql, sizeof sql, "%s%s%s", sql1, driver, "';");
   select_data(db, sql);
}

void select_by_car(sqlite3* db, char* car, char* driver)
{
   ////////////////////
   char* sql1 = "SELECT sum(distance), sum(weight) FROM PARK_ORDERS where car_number = ";
   char sql[200];
   snprintf(sql, sizeof sql, "%s%s", sql1, car);
   if(driver != NULL) {
      snprintf(sql, sizeof sql, "%s%s%s%s", sql, " and last_name = '", driver, "';");
      printf("%s", sql);
   }
   select_data(db, sql);
}

void select_by_each_driver(sqlite3* db, char* driver)
{
   ////////////////////
   char sql1[500] = "SELECT last_name, count(*), sum(weight), sum(price*0.2) FROM PARK_ORDERS";
   char sql[200];
   
   if(driver != NULL) {
      snprintf(sql1, sizeof sql1, "%s%s%s%s", sql1,  " where last_name = '", driver, "'");
      printf("%s", sql1);
      //select_data(db, sql);
      //return;
   }
   snprintf(sql, sizeof sql, "%s%s", sql1, " group by last_name;");
   select_data(db, sql);
}

void select_by_min_driver(sqlite3* db)
{
   char* sql = "select PARK_DRIVERS.*, min(mycount), sum_ from ("\
   "select  last_name,  count(last_name) mycount, sum(price * 0.2) sum_ "\
   "from PARK_ORDERS group by last_name), PARK_DRIVERS;";
 
   select_data(db, sql);
}

void select_by_max_car(sqlite3* db, char* driver)
{
   ////////////////////
   char sql1[500] = "SELECT PARK_CARS.*, max(distance_ ) from ("\
   "select PARK_ORDERS.car_number, sum(PARK_ORDERS.distance) distance_ from PARK_ORDERS ";
   char sql[500];
   //snprintf(sql, sizeof sql, "%s%s%s", sql1);
   if(driver != NULL) {
      printf("YES!");
      snprintf(sql1, sizeof sql1, "%s%s%s", " where driver_name = '", driver, "'");
      //select_data(db, sql);
      //return;
   }
   snprintf(sql, sizeof sql, "%s%s", sql1, " GROUP by car_number), PARK_CARS;");
   select_data(db, sql);
}

void select_data(sqlite3* db, char* sql)
{
   const char* data = "Callback function called: ";

   char *zErrMsg = 0;

   int rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   char* Msg = "SELECT finished successfully";
   Error_Message(rc, zErrMsg, Msg);
}

void insert_data(sqlite3 *db, char* sql){
   //char sql[500];
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   char* Msg = "INSERT finished successfully";
   Error_Message(rc, zErrMsg, Msg);
}

//typedef char (* drivers_)[6];
void insert_to_driver(sqlite3* db)
{
   char sql1[500] = "INSERT INTO PARK_DRIVERS VALUES (";
   char mas[90];
   int c;
   printf("Driver number:");
   scanf("%d", &c);
   sprintf(sql1, "%s%d",sql1, c);
   printf("Last name:");
   scanf("%s", mas);
   sprintf(sql1, "%s%s%s%s",sql1, ",'", mas, "'");
   printf("Category:");
   scanf("%s", mas);
   sprintf(sql1, "%s%s%s%s",sql1, ",'", mas, "',");
   printf("Experience:");
   scanf("%d", &c);
   sprintf(sql1, "%s%d",sql1, c);
   printf("Address:");
   scanf("%s", mas);
   sprintf(sql1, "%s%s%s%s",sql1, ",'", mas, "',");
   printf("Birthday year:");
   scanf("%d", &c);
   sprintf(sql1, "%s%d%s",sql1, c, ");");

   insert_data(db, sql1);
}

void insert_to_cars(sqlite3* db)
{
   char sql1[500] = "INSERT INTO PARK_CARS VALUES (";
   char mas[90];
   int c;
   printf("Car number:");
   scanf("%s", mas);
   sprintf(sql1, "%s%s%s%s",sql1, "'", mas, "'");
   printf("Brand:");
   scanf("%s", mas);
   sprintf(sql1, "%s%s%s%s",sql1, ",'", mas, "',");
   printf("Mileage:");
   scanf("%d", &c);
   sprintf(sql1, "%s%d%s",sql1, c, ",");
   printf("Load capacity:");
   scanf("%d", &c);
   sprintf(sql1, "%s%d%s",sql1, c, ");");

   insert_data(db, sql1);
}

void insert_to_orders(sqlite3* db)
{
   char sql1[500] = "INSERT INTO PARK_ORDERS VALUES (";
   char mas[90];
   int c;
   float price;
   printf("Date:");
   scanf("%s", mas);
   sprintf(sql1, "%s%s%s%s",sql1, "'", mas, "'");
   printf("Last name:");
   scanf("%s", mas);
   sprintf(sql1, "%s%s%s%s",sql1, ",'", mas, "'");
   printf("Car number:");
   scanf("%s", mas);
   sprintf(sql1, "%s%s%s%s",sql1, ",'", mas, "',");
   printf("Distance:");
   scanf("%d", &c);
   sprintf(sql1, "%s%d%s",sql1, c, ",");
   printf("Weight:");
   scanf("%d", &c);
   sprintf(sql1, "%s%d%s",sql1, c, ",");
   printf("Price:");
   scanf("%f", &price);
   sprintf(sql1, "%s%f%s",sql1, price, ");");

   int f = check_order(db, c, mas);
   if(f==1)
      return;
   insert_data(db, sql1);
}

void delete_data(sqlite3 *db)
{
   const char* data = "Callback function called: ";
   char* Msg = "DELETE finished successfully";
   char* zErrMsg = 0;

   char table_name[50];
   char value_[50];
   printf("Name of table:");
   scanf("%s", table_name);
   printf("Enter what delete without spaces(column_name = 'value')");
   //fgets(value_, sizeof(value_), stdin);
   scanf("%s", value_);

   char sql[100];
   sprintf(sql, "%s%s%s%s%s", "DELETE from ", table_name, " where ", value_, ";");
   //char* sql = "DELETE from Customer where ID=10; ";
    //     "SELECT * from Customer";

   int rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   Error_Message(rc, zErrMsg, Msg);
}

void update_data(sqlite3 *db)
{
   char table_name[30];
   char where_[50];
   char value_[50];
   printf("Name of table:");
   scanf("%s", table_name);
   printf("Enter where(whom) update without spaces(example, id=4): ");
   //fgets(where_, sizeof(where_), stdin);
   scanf("%s", where_);
   printf("Enter what update without spaces(column_name=value): ");
   //fgets(value_, sizeof(value_), stdin);
   scanf("%s", value_);

   char* data;
   char* zErrMsg = 0;

   char sql[200];
   sprintf(sql, "%s%s%s%s%s%s", "UPDATE ", table_name, " set ", value_, " where ", where_);
   //char* sql = "UPDATE Customer set weight = 70 where ID=3; " \
   //      "SELECT * from Customer";

   int rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   char* Msg = "UPDATE finished successfully";
   Error_Message(rc, zErrMsg, Msg);
}


/////////////////////////////////
static int callback_return(void *data, int argc, char **argv, char **azColName) {
   if(atoi(argv[0]) < atoi(data))
      return 1;

   return 0;
}

int check_order(sqlite3 * db, int gruz, char* num_machine)
{
   char* sql1 = "SELECT load_capacity from PARK_CARS where car_number = "; 
   char sql[100];
   snprintf(sql, sizeof(sql), "%s%s%s", sql1, num_machine, ";");

   const char* data = gruz;

   char *zErrMsg = 0;

   int rc = sqlite3_exec(db, sql, callback_return, (void*)data, &zErrMsg);
   
   if(rc != SQLITE_OK) 
      return 1;
   return 0;
}

void money(sqlite3* db, char* begin_date, char* end_date)
{
   char* sql1 = "SELECT last_name, sum(price * 0.2) from PARK_ORDERS where date >= '";
   char sql[250];
   snprintf(sql, sizeof(sql), "%s%s%s%s%s", sql1, begin_date, "' and date<= '", end_date, "' group by last_name;");

   select_data(db, sql);
}

void money_by_driver(sqlite3* db, char* begin_date, char* end_date, char* driver_name)
{
   char* sql1 = "SELECT last_name, sum(price * 0.2) from PARK_ORDERS where date >= '";
   char sql[250];
   snprintf(sql, sizeof(sql), "%s%s%s%s%s%s%s", sql1, begin_date, "' and date<= '", 
      end_date, "' and last_name = '", driver_name, "' group by last_name;");

   select_data(db, sql);
}
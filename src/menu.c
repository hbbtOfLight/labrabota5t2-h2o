#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "functional.h"
#include "menu.h"


sqlite3* db;

void get_info_menu()
{
	printf("\t1: completed orders\n");
	printf("\t2: total mileage and weight of hte car\n");
	printf("\t3: about driver\n");
	printf("\t4: about machine\n");
}

void admin_menu()
{
	int f=1;
	while(f) {
		char begin_date[15];
		char end_date[15];
		char name[20];
		int choise, sub_choise;
		printf("Choose action:\n1: get information\n2: insert\n3: get money for each driver\n4: get money by driver\n5: update\n6: delete\n7:exit\n");
		scanf("%d", &choise);
		switch(choise) {
			case 1:
				get_info_menu();
				printf("5: driver with fewer trips\n");
				scanf("%d", &sub_choise);
				if(sub_choise == 1){
					printf("Enter name of driver: ");
					scanf("%s", name);
					select_by_driver(db, name);
				}
				else if(sub_choise == 2) {
					char car[20];
					printf("Enter car number: ");
					scanf("%s", car);
					select_by_car(db, car, NULL);
				}
				else if(sub_choise == 3){
					select_by_each_driver(db, NULL);
				}	
				else if(sub_choise == 4){
					select_by_max_car(db, NULL);
				}	
				else if(sub_choise == 5) {
					select_by_min_driver(db);
				}
				break;
				
			case 2:
				printf("\t1:insert order\n");
				printf("\t2:insert car\n");
				printf("\t3:insert driver\n");
				scanf("%d", &sub_choise);
				if(sub_choise == 1)
					insert_to_orders(db);
				else if(sub_choise == 2)
					insert_to_cars(db);
				else if(sub_choise == 3)
					insert_to_driver(db);
				break;
			case 3: 
				printf("Enter begin date: ");
				
				
				scanf("%s", begin_date);
				printf("Enter end date: ");
				scanf("%s", end_date);
				money(db, begin_date, end_date);
				break;
			case 4: 
				printf("Enter begin date: ");
				
				scanf("%s", begin_date);
				printf("Enter end date: ");
				scanf("%s", end_date);
				printf("Enter name of driver: ");
				scanf("%s", name);
				money_by_driver(db, begin_date, end_date, name);
				break;
			case 5:
				update_data(db);
				break;
			case 6:
			  	delete_data(db);
			  	break;
			case 7:
				return;
				break;
		}
	}
}

void driver_menu(char* name)
{
	int f =1;
	while(f) {
		int choise, sub_choise;
		printf("Choose action:\n1: get information\n2: insert order\n3: get money\n4:exit\n");
		scanf("%d", &choise);
		switch(choise) {
			case 1:
				get_info_menu();
				scanf("%d", &sub_choise);
				if(sub_choise == 1)
					select_by_driver(db, name);
				else if(sub_choise == 2) {
					char car[10];
					printf("Enter car number: ");
					scanf("%s", car);
					select_by_car(db, car, name);
				}
				else if(sub_choise == 3){
					select_by_each_driver(db, name);
				}	
				else if(sub_choise == 4){
					select_by_max_car(db, name);
				}	
				break;
				
			case 2:
				insert_to_orders(db);
				break;
			case 3: 
				printf("Enter begin date: ");
				char begin_date[15];
				char end_date[15];
				
				scanf("%s", begin_date);
				printf("Enter end date: ");
				scanf("%s", end_date);
				money_by_driver(db, begin_date, end_date, name);
				break;
			case 4:
				return;
				break;
		}
	}
}

void get_start()
{
	db = open_data_base();

	int pers;
	printf("Choose\n1: Login as user\n2:Login as admin\n");
	scanf("%d", &pers);

	if(pers == 1) {
		char name[20];
		printf("Enter your last name: ");
		scanf("%s", name);
		driver_menu(name);
	}
	else if(pers == 2) {
		admin_menu();
	}

	sqlite3_close(db);
}


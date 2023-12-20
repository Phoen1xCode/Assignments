#pragma once
#include<mysql.h>

void account_reclaim(MYSQL* conn);
void account_storage(MYSQL* conn);
void ledger_reclaim(MYSQL* conn);
void ledger_storage(MYSQL* conn);
void plan_reclaim(MYSQL* conn);
void plan_storage(MYSQL* conn);
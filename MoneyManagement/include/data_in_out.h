#pragma once
#include<mysql.h>
//这一部分的函数是用于在主函数开头和结尾对数据库进行数据的读取与存储（序列化与·反序列化）
//并且处理之前动态分配的内存（主要是释放的操作）
namespace finance {
	void account_reclaim(MYSQL* conn);
	void account_storage(MYSQL* conn);
	void ledger_reclaim(MYSQL* conn);
	void ledger_storage(MYSQL* conn);
	void plan_reclaim(MYSQL* conn);
	void plan_storage(MYSQL* conn);
}
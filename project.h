#ifndef MYPROJECT_H
#define MYPROJECT_H
#include<iostream>
#include<string>
#include<fstream>


using namespace std;

#define DEL_NUM 0xffffffff
#define GOODS_FILE "data\\库存.txt"
#define SHOPPING_LIST_FILE "已售清单.txt"
#define USER_LIST_FILE "用户.txt"
#define GOODS_ID_LENGTH 6
#define GOODS_ID_FIRST F
typedef string Name;
typedef unsigned int Number;
typedef double Price;
typedef string Goods_id;
typedef string User_name;
typedef string User_password;


class goods;
class sell_list;
class shopping_cart;
class Admin;
class user;
class ID;

class ID{
	char buf[GOODS_ID_LENGTH];
public:
	operator char*(){
		return buf;
	}
	ID();
	ID(int);
	operator int();
	char* get(){
		return buf;
	}
	friend ifstream& operator >>(ifstream&, ID&);
};

class goods{
	ID id;
	Name name;
	Name brand;
	Price price;
	Number num;

public:
	void admin_search();
};

#endif
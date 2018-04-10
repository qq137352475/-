#ifndef MYPROJECT_H
#define MYPROJECT_H
#include<iostream>
#include<string>
#include<fstream>
#include<map>


using namespace std;

#define DEL_NUM 0xffffffff
#define MAX_ADD_GODDS_NUM 0xfffffff
#define GOODS_FILE "data\\库存.txt"
#define SHOPPING_LIST_FILE "data\\已售清单.txt"
#define USER_LIST_FILE "data\\用户.txt"
#define GOODS_ID_LENGTH 6
#define GOODS_ID_FIRST 'F'
#define ADMIN_NAME "admin"
#define ADMIN_PASSWORD "admin"
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
class file;

struct goods_info{
	Name name;
	Name brand;
	Price price;
	Number num;
	goods_info * next = NULL;
};

struct user_info{
	User_name name;
	User_password password;
	user_info* next = NULL;
};

typedef map<int, goods_info> database;

class ID{
	char buf[GOODS_ID_LENGTH];
public:
	ID();
	ID(int);
	operator int();
	char* get(){
		return buf;
	}
	void set(char *);
	friend ifstream& operator >>(ifstream&, ID&);
	friend ofstream& operator <<(ofstream&, ID&);
};

class file{
	char* filename;
public:
	file(){ return; }
	file(char*);
	bool read(database&);
	bool write(database&,char* username = NULL);
	//以下用来管理用户登录
	user_info* open_user_list();
	bool write_back_user_list(user_info *);
	
};

class goods{
	ID id;
	goods_info info;
	file f;
	database data;//所有的商品信息


public:
	goods();
	ID* get_id();
	goods_info* get_info();
	void admin_search(database&);
	bool admin_delete(ID);
	bool admin_insert(goods_info*);
	bool admin_change_number(ID,Number);
};
class sell_list{
	ID id;
	goods_info info;
	file f;
	database data;//售货清单

public:
	sell_list();

};
class shopping_cart{
	ID id;
	goods_info info;
	file f;
	User_name username;
	database data;

public:
	shopping_cart();
	shopping_cart(User_name);
	void chang_user(User_name);
};
class Admin{
	goods m_goods;
	sell_list m_sell_list;
	shopping_cart m_shopping_cart;
public:
	database data;
	ID id;
	goods_info info;
	Number num;
	void search_goods();
	bool delete_goods();
	bool insert_goods();
	bool change_goods_number();

public:

};
#endif
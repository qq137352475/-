#include"project.h"

user::user(User_name temp){
	username = temp;
	m_shopping_cart = username;
}
user::user(){
	username = '\0';
}
void user::overview_goods(){
	m_goods.user_overview(data);
	
}
bool user::search_goods(){
	return m_goods.user_search(name, data);
}
bool user::add_goods_to_shopping_cart()
{
	if (username == "\0")
	{
		return false;
	}
	//m_shopping_cart = username;
	m_goods.user_overview(data);
	if (id == 0)
	{
		if (0 != strcmp("F0000", id.get()))
			return false;
	}
	if (num == 0)
	{
		//增加0个商品 不允许
		return false;
	}
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++)
	{
		if (itr->first == id)
		{
			info.brand = itr->second.brand;
			info.name = itr->second.name;
			info.num = itr->second.num;
			info.price = itr->second.price;
			break;
		}
	}
	if (itr == data.end())
	{
		//库存中找不到符合条件的商品
		return false;
	}
	return m_shopping_cart.user_add_goods(id, num, &info);
}
void user::overview_shopping_cart()
{
	data.clear();
	if (username == "\0")
		return;
	database shpping_cart_data;
	m_shopping_cart.overview_shopping_cart(shpping_cart_data);
	database goods_data;
	m_goods.user_overview(goods_data);
	//更新价格
	//
	database::iterator iter;
	for (iter = shpping_cart_data.begin(); iter != shpping_cart_data.end(); iter++)
	{
		if (goods_data.count(iter->first) == 1)
		{
			//库存中存在这个商品
			if (goods_data[iter->first].num != DEL_NUM && goods_data[iter->first].num != 0)
			{
				//购物车中商品没有被删除 并且 不为0
				iter->second.price = goods_data[iter->first].price;
				data.insert(pair<int,goods_info>(iter->first,iter->second));
			}
		}
	}
	
}

bool user::sub_num_of_shopping_cart()
{
	if (username == "\0")
	{
		return false;
	}
	//m_shopping_cart = username;
	m_goods.user_overview(data);
	if (id == 0)
	{
		if (0 != strcmp("F0000", id.get()))
			return false;
	}
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++)
	{
		if (itr->first == id)
		{
			info.brand = itr->second.brand;
			info.name = itr->second.name;
			info.num = itr->second.num;
			info.price = itr->second.price;
			break;
		}
	}
	if (itr == data.end())
	{
		//库存中找不到符合条件的商品
		return false;
	}
	return m_shopping_cart.user_sub_num(id, num);
}
bool user::checkout()
{
	price = 0;
	//读取购物车文件
	//database shpping_cart_data;
	//m_shopping_cart.overview_shopping_cart(shpping_cart_data);
	this->overview_shopping_cart();
	if (data.size() == 0)
	{
		//购物车为空
		return false;
	}
	database goods_data;
	m_goods.user_overview(goods_data);
	if (goods_data.size() == 0)
	{
		//找不到库存
		return false;
	}
	database::iterator iter;
	/*for (iter = shpping_cart_data.begin(); iter != shpping_cart_data.end(); iter++)
	{
		if (goods_data.count(iter->first) == 1)
		{
			//库存中存在这个商品
			if (goods_data[iter->first].num >= iter->second.num&&goods_data[iter->first].num != DEL_NUM)
			{
				//购买的商品没有被删除并且库存足够
				price += goods_data[iter->first].price * iter->second.num;
			}
			else
				return false;
		}
		else
			return false;
	}*/
	for (iter = data.begin(); iter != data.end(); iter++)
	{
		if (iter->second.num <= goods_data[iter->first].num)
		{
			//库存足够
			price += goods_data[iter->first].price * iter->second.num;
		}
	}
	return true;
}
bool user::payment()
{
	//从购物车文件中读取购物车数据
	//m_shopping_cart.overview_shopping_cart(data);
	this->overview_shopping_cart();
	if (data.size() ==  0)
	{
		return false;
	}
	//讲购物车记录写回 售货清单
	m_sell_list.user_insert(data, username);
	//更改库存数目
	database::iterator iter;
	for (iter = data.begin(); iter != data.end(); iter++)
	{
		m_goods.user_change_number(iter->first, iter->second.num);
	}
	//清空购物车
	m_shopping_cart.clear();
	return true;
}
bool user::clear_shopping_cart()
{
	return m_shopping_cart.clear();
}
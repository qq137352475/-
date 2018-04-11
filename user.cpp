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
	if (username == "\0")
		return;
	m_shopping_cart.overview_shopping_cart(data);
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
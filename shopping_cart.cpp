#include"project.h"

shopping_cart::shopping_cart(){
	username = ' ';
	return;
}

shopping_cart::shopping_cart(User_name temp){
	username = temp;
	string str;
	str ="data\\" + temp + ".txt";
	f = (char*)str.data();
	data.clear();
	f.read(data,temp);

}
/*void shopping_cart::chang_user(User_name temp){
	username = temp;
	string str;
	str = temp + ".txt";
	f = (char*)str.data();
	data.clear();
	f.read(data);
}*/
bool shopping_cart::user_add_goods(ID id, Number num,goods_info * info)
{
	//给购物车添加商品
	//没有对商品数量进行检查（是否超过库存等）已解决
	if (num > MAX_ADD_GODDS_NUM)
	{
		//数字太大了
		return false;
	}
	f.read(data, username);
	database::iterator itr;
	//if (data.size() == 0)
	//{
	//	return false;
	//}
	for (itr = data.begin(); itr != data.end(); itr++)
	{
		//该商品是否已经存在于购物车
		if (itr->first == id)
		{
			//存在
			if (itr->second.num + num > info->num)
			{
				//数量超过库存
				return false;
			}
			itr->second.num += num;
			break;
		}
	}
	if (itr == data.end())
	{
		//不存在
		if (info->num <= num)
		{
			//数量超过库存
			return false;
		}
		info->num = num;
		data.insert(pair<int, goods_info>(id, *info));
	}
	f.write(data, username);
	return true;
}
void shopping_cart::overview_shopping_cart(database& temp)
{
	//查看购物车
	f.read(temp, username);
}


bool shopping_cart::user_sub_num(ID id, Number num)
{
	//给已经存在于购物车的商品减少数量
	if (num >= MAX_ADD_GODDS_NUM)
	{
		//数字太大了
		return false;
	}
	f.read(data, username);
	database::iterator itr;
	if (data.size() == 0)
	{
		return false;
	}
	for (itr = data.begin(); itr != data.end(); itr++)
	{
		//该商品是否已经存在于购物车
		if (itr->first == id)
		{
			//存在
			if (itr->second.num < num)
			{
				//数量超过购物车里面的数量
				return false;
			}
			if (itr->second.num == num)
			{
				//删除之后数量等于0
				data.erase(itr->first);
				f.write(data, username);
				return true;
			}
			itr->second.num -= num;
			break;
		}
	}
	if (itr == data.end())
	{
		//不存在
		return false;
	}
	f.write(data, username);
	return true;
}
bool shopping_cart::clear()
{
	return f.clear_shopping_cart(username);
}
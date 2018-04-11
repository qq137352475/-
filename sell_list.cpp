#include"project.h"

sell_list::sell_list(){
	f = SHOPPING_LIST_FILE;
	data.clear();
	f.read(data);
	return;
}

void sell_list::admin_overview(database& temp_data){
	data.clear();
	temp_data.clear();
	f.read(data);
	goods_info* p_sell_list_temp;
	goods_info* p_temp_data;
	goods_info* p_new_data;
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++)
	{
		info.brand = itr->second.brand;
		info.name = itr->second.name;
		info.num = itr->second.num;
		info.price = itr->second.price;
		temp_data.insert(pair<int, goods_info>(itr->first, info));
		
		for (p_sell_list_temp = itr->second.next; p_sell_list_temp != NULL; p_sell_list_temp = p_sell_list_temp->next)
		{
			//同一个id的商品的多条记录
			//如果价格一样则合并
			//不一样则新增一条
			for (p_temp_data = &temp_data[itr->first]; p_temp_data != NULL; p_temp_data = p_temp_data->next)
			{
				//在结果中找到相同的id
				//比较价格是否一样
				//如果价格一样则讲数量相加
				//如果价格不一样则会循环到最后
				if (p_temp_data->price == p_sell_list_temp->price)
				{
					p_temp_data->num += p_sell_list_temp->num;
					break;
				}
			}
			if (p_temp_data == NULL)
			{
				//价格不一样，新增条目
				p_new_data = new goods_info;
				p_new_data->brand = p_sell_list_temp->brand;
				p_new_data->name = p_sell_list_temp->name;
				p_new_data->num = p_sell_list_temp->num;
				p_new_data->price = p_sell_list_temp->price;
				p_temp_data = &temp_data[itr->first];
				while (p_temp_data->next != NULL)
				{
					p_temp_data = p_temp_data->next;
				}

				p_temp_data->next = p_new_data;
			}
		}
	}
}

void sell_list::user_insert(database & data, User_name username)
{
	f.write(data, username);
}
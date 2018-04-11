#include"project.h"

goods::goods(){
	f = GOODS_FILE;
	data.clear();
	f.read(data);
	return;
}
void goods::admin_search(database& temp){
	//管理员查询商品
	//找出所有没有被删除的商品
	temp.clear();
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++){
		if (itr->second.num != DEL_NUM){
			//商品没有被删除
			temp.insert(pair<int, goods_info>(itr->first, itr->second));
		}
	}

}
void goods::user_overview(database & temp)
{
	//用户查看商品
	//找出所有数量大于0并且没有被删除的商品
	temp.clear();
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++){
		if (itr->second.num != DEL_NUM && itr->second.num > 0){
			//符合条件的商品
			temp.insert(pair<int, goods_info>(itr->first, itr->second));
		}
	}
}
ID* goods::get_id(){
	return &id;
}
goods_info* goods::get_info(){
	return & info;
}

bool goods::admin_delete(ID id){
	//管理员删除商品
	//将要被删除的商品的数量置 DEL_NUM
	//写回文件
	int temp = id;
	if (temp == 0){
		if(0 != strcmp("F0000", id.get()))
			return false;
	}
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++){
		//temp = itr->first;
		if (itr->first == temp){
			itr->second.num = DEL_NUM;
			break;
		}
	}
	if (itr == data.end()){
		//删除失败
		return false;
	}
	f.write(data);
	return true;
}

bool goods::admin_change_number(ID id,Number num){
	//修改商品数量
	int temp = id;
	if (temp == 0){
		if (0 != strcmp("F0000", id.get()))
			return false;
	}
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++){
		//temp = itr->first;
		if (itr->first == temp){
			if (itr->second.num == DEL_NUM)
				//修改已经被删除商品的数量
				return false;
			itr->second.num = num;
			break;
		}
	}
	if (itr == data.end()){
		//错误的ID
		return false;
	}
	f.write(data);
	return true;
}

bool goods::admin_insert(goods_info* gd_info){
	//增加商品
	//品牌 名称 均相同则视为同一种商品
	//对 已经存在的 商品 进行 增加 操作，价格覆盖，数量与以前的数量相加
	if (gd_info->num >= MAX_ADD_GODDS_NUM){
		//增加的数量太大了
		return false;
	}
	info.brand = gd_info->brand;
	info.name = gd_info->name;
	info.num = gd_info->num;
	info.price = gd_info->price;
	int temp = 0;
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++){
		//temp = itr->first;
		temp = temp + 1;
		if (itr->second.name == info.name&&itr->second.brand == info.brand){
			//插入已在库存中的商品
			//若商品已经被删除，则直接将num改为想要增加的值
			//否则加上 增加的 数量，
			//如果 增加后的数量 刚好 == DEL_NUM  则增加失败（应该没有这种情况）
			if (itr->second.num != DEL_NUM){
				info.num += itr->second.num;
				if (info.num == DEL_NUM){
					return false;
				}
			}
			itr->second.num = info.num;
			itr->second.price = info.price;
			break;
		}
	}
	if (itr == data.end()){
		//增加全新的商品
		data.insert(pair<int, goods_info>(temp, info));
	}
	f.write(data);
	return true;
}
bool goods::user_search(Name name, database &temp_data)
{
	//通过商品名称查找商品
	//找出所有数量大于0并且没有删除的 商品名字等于给定名字 的商品
	temp_data.clear();
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++)
	{
		if (itr->second.name == name&&itr->second.num != 0 && itr->second.num != DEL_NUM){
			temp_data.insert(pair < int, goods_info>(itr->first,itr->second));
		}
	}
	if (temp_data.size() == 0)
		return false;
	return true;
}
bool goods::user_change_number(ID id, Number num){
	//购物车结账
	//减少 ID 为 id 的 商品 num 个
	int temp = id;
	if (temp == 0){
		if (0 != strcmp("F0000", id.get() ))
			return false;
	}
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++){
		//temp = itr->first;
		if (itr->first == temp){
			if (itr->second.num == DEL_NUM||itr->second.num < num)
				//修改已经被删除商品的数量 或者 减少的数量大于原来的数量
				return false;
			itr->second.num -= num;
			break;
		}
	}
	if (itr == data.end()){
		//错误的ID
		return false;
	}
	f.write(data);
	return true;
}
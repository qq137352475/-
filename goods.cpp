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
ID* goods::get_id(){
	return &id;
}
goods_info* goods::get_info(){
	return & info;
}
#include"project.h"

void Admin::search_goods()
{
	m_goods.admin_search(data);
}
bool Admin::delete_goods(){
	return m_goods.admin_delete(id);
}
bool Admin::insert_goods(){
	return m_goods.admin_insert(&info);
}
bool Admin::change_goods_number(goods_change_flag flag){
	return m_goods.admin_change_number(id, num,flag);
}
void Admin::sell_list_overview(){
	m_sell_list.admin_overview(data);
	return;
}
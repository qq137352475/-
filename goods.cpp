#include"project.h"

goods::goods(){
	f = GOODS_FILE;
	data.clear();
	f.read(data);
	return;
}
void goods::admin_search(database& temp){
	//����Ա��ѯ��Ʒ
	//�ҳ�����û�б�ɾ������Ʒ
	temp.clear();
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++){
		if (itr->second.num != DEL_NUM){
			//��Ʒû�б�ɾ��
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
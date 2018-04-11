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
void goods::user_overview(database & temp)
{
	//�û��鿴��Ʒ
	//�ҳ�������������0����û�б�ɾ������Ʒ
	temp.clear();
	database::iterator itr;
	for (itr = data.begin(); itr != data.end(); itr++){
		if (itr->second.num != DEL_NUM && itr->second.num > 0){
			//������������Ʒ
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
	//����Աɾ����Ʒ
	//��Ҫ��ɾ������Ʒ�������� DEL_NUM
	//д���ļ�
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
		//ɾ��ʧ��
		return false;
	}
	f.write(data);
	return true;
}

bool goods::admin_change_number(ID id,Number num){
	//�޸���Ʒ����
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
				//�޸��Ѿ���ɾ����Ʒ������
				return false;
			itr->second.num = num;
			break;
		}
	}
	if (itr == data.end()){
		//�����ID
		return false;
	}
	f.write(data);
	return true;
}

bool goods::admin_insert(goods_info* gd_info){
	//������Ʒ
	//Ʒ�� ���� ����ͬ����Ϊͬһ����Ʒ
	//�� �Ѿ����ڵ� ��Ʒ ���� ���� �������۸񸲸ǣ���������ǰ���������
	if (gd_info->num >= MAX_ADD_GODDS_NUM){
		//���ӵ�����̫����
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
			//�������ڿ���е���Ʒ
			//����Ʒ�Ѿ���ɾ������ֱ�ӽ�num��Ϊ��Ҫ���ӵ�ֵ
			//������� ���ӵ� ������
			//��� ���Ӻ������ �պ� == DEL_NUM  ������ʧ�ܣ�Ӧ��û�����������
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
		//����ȫ�µ���Ʒ
		data.insert(pair<int, goods_info>(temp, info));
	}
	f.write(data);
	return true;
}
bool goods::user_search(Name name, database &temp_data)
{
	//ͨ����Ʒ���Ʋ�����Ʒ
	//�ҳ�������������0����û��ɾ���� ��Ʒ���ֵ��ڸ������� ����Ʒ
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
	//���ﳵ����
	//���� ID Ϊ id �� ��Ʒ num ��
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
				//�޸��Ѿ���ɾ����Ʒ������ ���� ���ٵ���������ԭ��������
				return false;
			itr->second.num -= num;
			break;
		}
	}
	if (itr == data.end()){
		//�����ID
		return false;
	}
	f.write(data);
	return true;
}
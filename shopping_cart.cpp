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
	//�����ﳵ�����Ʒ
	//û�ж���Ʒ�������м�飨�Ƿ񳬹����ȣ��ѽ��
	if (num > MAX_ADD_GODDS_NUM)
	{
		//����̫����
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
		//����Ʒ�Ƿ��Ѿ������ڹ��ﳵ
		if (itr->first == id)
		{
			//����
			if (itr->second.num + num > info->num)
			{
				//�����������
				return false;
			}
			itr->second.num += num;
			break;
		}
	}
	if (itr == data.end())
	{
		//������
		if (info->num <= num)
		{
			//�����������
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
	//�鿴���ﳵ
	f.read(temp, username);
}


bool shopping_cart::user_sub_num(ID id, Number num)
{
	//���Ѿ������ڹ��ﳵ����Ʒ��������
	if (num >= MAX_ADD_GODDS_NUM)
	{
		//����̫����
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
		//����Ʒ�Ƿ��Ѿ������ڹ��ﳵ
		if (itr->first == id)
		{
			//����
			if (itr->second.num < num)
			{
				//�����������ﳵ���������
				return false;
			}
			if (itr->second.num == num)
			{
				//ɾ��֮����������0
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
		//������
		return false;
	}
	f.write(data, username);
	return true;
}
bool shopping_cart::clear()
{
	return f.clear_shopping_cart(username);
}
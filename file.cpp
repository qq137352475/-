#include"project.h"

file::file(char *temp){
	filename = temp;
}

bool file::read(database& data){
	ID key;
	goods_info vaule;
	char buf[50];
	//char temp[GOODS_ID_LENGTH];
	ifstream in(filename, ios::in);
	if (!in){
		return false;
	}

	if (filename == GOODS_FILE){
		//���.txt
		in.getline(buf, 50);
		while (!in.eof()){
			//��ȡ���ݣ�����map
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num;
			data.insert(pair<int, goods_info>(key, vaule));
		}
	}
	else if (filename == SHOPPING_LIST_FILE){
		//�����嵥.txt
		in.getline(buf, 50);
		while (!in.eof()){
			//��ȡ��ͬһ��ID����Ʒʱ������������ݵļ۸���ͬ����ϲ�
			//�����һ��������nextָ��ָ���������
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num >> buf;
			if (!(data.insert(pair<int, goods_info>(key, vaule))).second){
				//���벻�ɹ���˵������IDһ������Ʒ
				goods_info* p, *temp = new goods_info;
				temp->brand = vaule.brand;
				temp->name = vaule.name;
				temp->num = vaule.num;
				temp->name = vaule.name;
				p = &data[key];
				while (p->next != NULL){
					p = p->next;
				}
				p->next = temp;
			}
		}
	}
	else if (filename == USER_LIST_FILE){
		//�û�.txt
		//�ļ��ṹ��ͬ������һ������ʵ��
	}
	else
	{
		//���û��������Ĺ��ﳵ�ļ�
		in.getline(buf, 50);
		while (!in.eof()){
			//��ȡ���ݣ�����map
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num;
			data.insert(pair<int, goods_info>(key, vaule));
		}
	}
	return true;
}

bool file::write(database& data,char* username){
	ID key;
	database::iterator itr;

	
	if (filename == GOODS_FILE){
		//���.txt
		ofstream of(filename, ios::out);
		if (!of){
			return false;
		}
		of << "ID\t����\tƷ��\t�۸�\t����\n";
		for (itr = data.begin(); itr != data.end(); itr++){
			key = itr->first;
			of << key << '\t' << itr->second.name << "\t" << itr->second.brand << "\t" << itr->second.price << '\t' << itr->second.num << endl;
		}
	}
	else if (filename == SHOPPING_LIST_FILE){
		//�����嵥
		//��׷�ӵķ�ʽ���ļ�
		ofstream of(filename, ios::out|ios::app);
		if (!of || username == NULL){
			return false;
		}
		//of << "ID\t����\tƷ��\t�۸�\t����\n";
		//of << endl;
		for (itr = data.begin(); itr != data.end(); itr++){
			key = itr->first;
			of << key << '\t' << itr->second.name << "\t" << itr->second.brand << "\t" << itr->second.price << '\t' << itr->second.num << '\t' << username << endl;
		}
	}
	else if (filename == USER_LIST_FILE){
		//������һ��������ʵ��
		return false;
	}
	else{
		//���û��������Ĺ��ﳵ�ļ�
		ofstream of(filename, ios::out);
		if (!of){
			return false;
		}
		/*of << "ID,����,Ʒ��,�۸�,����\n";
		for (itr = data.begin(); itr != data.end(); itr++){
		key = itr->first;
		of << key.get() << "," << itr->second.name << "," << itr->second.brand << "," << itr->second.price << ',' << itr->second.num << endl;
		}*/
		of << "ID\t����\tƷ��\t�۸�\t����\n";
		for (itr = data.begin(); itr != data.end(); itr++){
			key = itr->first;
			of << key << '\t' << itr->second.name << "\t" << itr->second.brand << "\t" << itr->second.price << '\t' << itr->second.num << endl;
		}
	}

	return true;
}
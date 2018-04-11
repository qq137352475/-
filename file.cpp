#include"project.h"

ifstream& operator >>(ifstream &in, ID &id){
	in >> id.buf;
	return in;
}
ofstream& operator <<(ofstream&of, ID&id){
	of << id.buf;
	return of;
}
file::file(char *temp){
	strncpy_s(filename, temp, FILENAME_MAX);
}

bool file::read(database& data, User_name username){
	if (&data == false){
		return false;
	}
	ID key;
	goods_info vaule;
	char buf[50];
	//char temp[GOODS_ID_LENGTH];
	ifstream in(filename, ios::in);
	if (!in){
		return false;
	}

	if (0 == strcmp(filename, GOODS_FILE)){
		//���.txt
		in.getline(buf, 50);
		while (!in.eof()){
			//��ȡ���ݣ�����map
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num;
			data.insert(pair<int, goods_info>(key, vaule));
		}
	}
	else if (0 == strcmp(filename, SHOPPING_LIST_FILE)){
		//�����嵥.txt
		in.getline(buf, 50);
		while (!in.eof()){
			//��ȡ��ͬһ��ID����Ʒʱ������������ݵļ۸���ͬ����ϲ�
			//�����һ��������nextָ��ָ���������
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num >> buf;
			if (key == 0){
				if (0 != strcmp("F0000", key.get()) ){
					//�����ID
					continue;
				}
			}
			if (!(data.insert(pair<int, goods_info>(key, vaule))).second){
				//���벻�ɹ���˵������IDһ������Ʒ
				goods_info* p, *temp = new goods_info;
				temp->brand = vaule.brand;
				temp->name = vaule.name;
				temp->num = vaule.num;
				temp->price = vaule.price;
				int fff = key;
				p = &data[key];
				while (p->next != NULL){
					p = p->next;
				}
				p->next = temp;
			}
		}
	}
	else if (0 == strcmp(filename, USER_LIST_FILE)){
		//�û�.txt
		//�ļ��ṹ��ͬ������һ������ʵ��
	}
	else
	{
		//���û��������Ĺ��ﳵ�ļ�
		username = "data\\" + username + ".txt";
		if (0 != strcmp(filename, username.data()))
		{
			return false;
		}
		in.getline(buf, 50);
		while (!in.eof()){
			//��ȡ���ݣ�����map
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num;
			data.insert(pair<int, goods_info>(key, vaule));
		}
	}
	return true;
}

bool file::write(database& data,User_name username){
	ID key;
	database::iterator itr;

	if (&data == NULL)
		return false;
	
	if (0 == strcmp(filename, GOODS_FILE)){
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
	else if (0 ==strcmp(filename, SHOPPING_LIST_FILE)){
		//�����嵥
		//��׷�ӵķ�ʽ���ļ�
		ofstream of(filename, ios::out|ios::app);
		if (!of || username == " "){
			return false;
		}
		//of << "ID\t����\tƷ��\t�۸�\t����\n";
		//of << endl;
		for (itr = data.begin(); itr != data.end(); itr++){
			key = itr->first;
			of << key << '\t' << itr->second.name << "\t" << itr->second.brand << "\t" << itr->second.price << '\t' << itr->second.num << '\t' << username << endl;
		}
	}
	else if(0 ==strcmp(filename, USER_LIST_FILE)){
		//������һ��������ʵ��
		return false;
	}
	else{
		//���û��������Ĺ��ﳵ�ļ�
		username = "data\\" + username + ".txt";
		if (0 != strcmp(filename, username.data())){
			return false;
		}
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

user_info * file::open_user_list(){
	if (0 != strcmp(filename,USER_LIST_FILE)){
		//����ȷ���ļ���
		return NULL;
	}
	ifstream in;
	in.open(filename, ios::in | ios::_Nocreate);
	if (!in){
		//��ʧ��
		return NULL;
	}
	char buf[50];
	in.getline(buf, 50);
	if (in.eof()){
		return NULL;
	}
	user_info * head = new user_info;
	in >> head->name >> head->password;
	user_info *temp = head;
	while (!in.eof()){
		temp->next = new user_info;
		temp = temp->next;
		in >> temp->name >> temp->password;

	}
	return head;
}

bool file::write_back_user_list(user_info *temp){
	//�����û���ӵ��ļ�ĩβ
	if (0 != strcmp(filename, USER_LIST_FILE)){
		//����ȷ���ļ���
		return false;
	}
	ofstream of;
	of.open(filename, ios::out | ios::app);
	if (!of){
		//��ʧ��
		return false;
	}
	if (temp == NULL){
		//��ָ��
		return false;
	}
	of << temp->name << '\t' << temp->password << endl;
	return true;
}
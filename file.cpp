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
		//库存.txt
		in.getline(buf, 50);
		while (!in.eof()){
			//读取数据，存入map
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num;
			data.insert(pair<int, goods_info>(key, vaule));
		}
	}
	else if (0 == strcmp(filename, SHOPPING_LIST_FILE)){
		//已售清单.txt
		in.getline(buf, 50);
		while (!in.eof()){
			//读取到同一个ID的商品时，如果两个数据的价格相同，则合并
			//如果不一样，则用next指针指向这个数据
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num >> buf;
			if (key == 0){
				if (0 != strcmp("F0000", key.get()) ){
					//错误的ID
					continue;
				}
			}
			if (!(data.insert(pair<int, goods_info>(key, vaule))).second){
				//插入不成功，说明存在ID一样的商品
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
		//用户.txt
		//文件结构不同，在另一个函数实现
	}
	else
	{
		//以用户名命名的购物车文件
		username = "data\\" + username + ".txt";
		if (0 != strcmp(filename, username.data()))
		{
			return false;
		}
		in.getline(buf, 50);
		while (!in.eof()){
			//读取数据，存入map
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
		//库存.txt
		ofstream of(filename, ios::out);
		if (!of){
			return false;
		}
		of << "ID\t名称\t品牌\t价格\t数量\n";
		for (itr = data.begin(); itr != data.end(); itr++){
			key = itr->first;
			of << key << '\t' << itr->second.name << "\t" << itr->second.brand << "\t" << itr->second.price << '\t' << itr->second.num << endl;
		}
	}
	else if (0 ==strcmp(filename, SHOPPING_LIST_FILE)){
		//已售清单
		//已追加的方式打开文件
		ofstream of(filename, ios::out|ios::app);
		if (!of || username == " "){
			return false;
		}
		//of << "ID\t名称\t品牌\t价格\t数量\n";
		//of << endl;
		for (itr = data.begin(); itr != data.end(); itr++){
			key = itr->first;
			of << key << '\t' << itr->second.name << "\t" << itr->second.brand << "\t" << itr->second.price << '\t' << itr->second.num << '\t' << username << endl;
		}
	}
	else if(0 ==strcmp(filename, USER_LIST_FILE)){
		//将在另一个函数中实现
		return false;
	}
	else{
		//已用户名命名的购物车文件
		username = "data\\" + username + ".txt";
		if (0 != strcmp(filename, username.data())){
			return false;
		}
		ofstream of(filename, ios::out);
		if (!of){
			return false;
		}
		/*of << "ID,名称,品牌,价格,数量\n";
		for (itr = data.begin(); itr != data.end(); itr++){
		key = itr->first;
		of << key.get() << "," << itr->second.name << "," << itr->second.brand << "," << itr->second.price << ',' << itr->second.num << endl;
		}*/
		of << "ID\t名称\t品牌\t价格\t数量\n";
		for (itr = data.begin(); itr != data.end(); itr++){
			key = itr->first;
			of << key << '\t' << itr->second.name << "\t" << itr->second.brand << "\t" << itr->second.price << '\t' << itr->second.num << endl;
		}
	}

	return true;
}

user_info * file::open_user_list(){
	if (0 != strcmp(filename,USER_LIST_FILE)){
		//不正确的文件名
		return NULL;
	}
	ifstream in;
	in.open(filename, ios::in | ios::_Nocreate);
	if (!in){
		//打开失败
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
	//将新用户添加到文件末尾
	if (0 != strcmp(filename, USER_LIST_FILE)){
		//不正确的文件名
		return false;
	}
	ofstream of;
	of.open(filename, ios::out | ios::app);
	if (!of){
		//打开失败
		return false;
	}
	if (temp == NULL){
		//空指针
		return false;
	}
	of << temp->name << '\t' << temp->password << endl;
	return true;
}
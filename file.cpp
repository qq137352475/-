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
		//库存.txt
		in.getline(buf, 50);
		while (!in.eof()){
			//读取数据，存入map
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num;
			data.insert(pair<int, goods_info>(key, vaule));
		}
	}
	else if (filename == SHOPPING_LIST_FILE){
		//已售清单.txt
		in.getline(buf, 50);
		while (!in.eof()){
			//读取到同一个ID的商品时，如果两个数据的价格相同，则合并
			//如果不一样，则用next指针指向这个数据
			in >> key >> vaule.name >> vaule.brand >> vaule.price >> vaule.num >> buf;
			if (!(data.insert(pair<int, goods_info>(key, vaule))).second){
				//插入不成功，说明存在ID一样的商品
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
		//用户.txt
		//文件结构不同，在另一个函数实现
	}
	else
	{
		//以用户名命名的购物车文件
		in.getline(buf, 50);
		while (!in.eof()){
			//读取数据，存入map
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
	else if (filename == SHOPPING_LIST_FILE){
		//已售清单
		//已追加的方式打开文件
		ofstream of(filename, ios::out|ios::app);
		if (!of || username == NULL){
			return false;
		}
		//of << "ID\t名称\t品牌\t价格\t数量\n";
		//of << endl;
		for (itr = data.begin(); itr != data.end(); itr++){
			key = itr->first;
			of << key << '\t' << itr->second.name << "\t" << itr->second.brand << "\t" << itr->second.price << '\t' << itr->second.num << '\t' << username << endl;
		}
	}
	else if (filename == USER_LIST_FILE){
		//将在另一个函数中实现
		return false;
	}
	else{
		//已用户名命名的购物车文件
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
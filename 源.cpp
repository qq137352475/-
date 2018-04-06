#include"project.h"

/*
以实现功能：
将 库存 已售清单 中的数据读取并存入 database 中。
将 购物车中的数据 存入指定的文件中
将修改过的 database 存入 库存.txt
追加 已售清单 中的条目
*/

ifstream& operator >>(ifstream &in, ID &id){
	in >> id.buf;
	return in;
}
ofstream& operator <<(ofstream&of, ID&id){
	of << id.buf;
	return of;
}

int main(){
	database data;
	//file f(GOODS_FILE);
	file f(SHOPPING_LIST_FILE);
	//f.read(data);

	//file f("data\\user5.txt");
	goods_info gf;
	gf.brand = "测试品牌2";
	gf.name = "测试名字2";
	gf.num = 10;
	gf.price = 51.1;

	data.insert(pair<int, goods_info>(16, gf));

	if (f.write(data,"user_test")){
		cout << "成功" << endl;
	}
	else
		cout << "失败" << endl;

	database::iterator itr;

	/*for (itr = data.begin(); itr != data.end(); itr++){
		cout << itr->first << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
	}*/


	system("pause");
	return 0;
}
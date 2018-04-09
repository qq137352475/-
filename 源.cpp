#include"project.h"

/*
以实现功能：
将 库存 已售清单 中的数据读取并存入 database 中。
将 购物车中的数据 存入指定的文件中
将修改过的 database 存入 库存.txt
追加 已售清单 中的条目
用户的登录与注册
下一步实现 用户与管理员对数据的操作
*/



int main(){
	cout << "====================================================================\n";
	cout << "1，用户登录 2，用户注册 3，管理员登录\n";
	cout << "====================================================================\n";
	char c;
	cin >> c;
	file uifo(USER_LIST_FILE);//已经存在的用户的用户名，密码等信息
	user_info *head = uifo.open_user_list();
	if (head == NULL){
		cout << "找不到用户列表信息！\n";
	}
	user_info *temp = head;
	user_info new_user;//假如需要创建新用户，信息保存在这个里
	User_name name;
	User_password password;
	switch (c){
	case '1':
		if (head == NULL)
			break;
		//用户登录
		cout << "输入用户名\n";
		cin >> name;
		cout << "输入密码\n";
		cin >> password;
		for (temp = head; temp != NULL; temp = temp->next){
			if (temp->name == name){
				if (temp->password == password){
					//用户名密码匹配
					//登录成功
					//创建 user 对象，与用户进行交互，暂未实现
					cout << "登录成功！\n";
					break;
				}
				else{
					//用户名 密码不匹配
					cout << "密码输入错误！\n";
					break;
				}
			}
		}
		if (temp == NULL){
			//找不到用户名
			cout << "找不到该用户，请重新输入或者注册新用户！\n";
		}
		break;
	case'2':
		if (head == NULL)
			break;
		//用户注册
		cout << "输入用户名\n";
		cin >> name;
		for (temp = head; temp != NULL; temp = temp->next){
			if (temp->name == name){
				//已存在的用户名
				cout << "已存在的用户名，请重新输入或者直接登录\n";
				break;
			}
		}
		if (temp == NULL){
			//不存在的用户名
			cout << "输入密码\n";
			cin >> password;
			new_user.name = name;
			new_user.password = password;
			uifo.write_back_user_list(&new_user);//将新用户写回文件
			//创建成功
			//创建 user 对象，与用户进行交互，暂未实现
			cout << "注册成功！\n";
		}
		break;
	case'3':
		//管理员登录
		break;
	default:
		//
		break;
	}


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
	/*
	if (f.write(data,"user_test")){
		cout << "成功" << endl;
	}
	else
		cout << "失败" << endl;
		*/
	database::iterator itr;

	/*for (itr = data.begin(); itr != data.end(); itr++){
		cout << itr->first << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
	}*/


	system("pause");
	return 0;
}

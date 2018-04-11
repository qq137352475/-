#include"project.h"

/*
以实现功能：
将 库存 已售清单 中的数据读取并存入 database 中。
将 购物车中的数据 存入指定的文件中
将修改过的 database 存入 库存.txt
追加 已售清单 中的条目
用户的登录与注册
管理员对数据的操作
管理员对售货清单的查询暂未实现
管理员修改商品信息之后对用户购物车的更新暂未实现
用户结算 购物车暂未 实现
注册新用户功能暂未实现
tip: 删除已经删除的商品无影响
修改已删除商品的数量无法操作
*/

//enum goods_change_flag{ ADD, SUB, COVER };

int main(){
	bool loop = true;

	user_info *temp;
	user_info new_user;//假如需要创建新用户，信息保存在这个里
	User_name name;
	User_password password;

	string str;
	ID out_id;
	database::iterator itr;
	goods_info* p_sell_list_temp;
	bool b_new_user = false;
	goods_change_flag myflag;
	while (loop){
		char c;
		if (!b_new_user){
			cout << "====================================================================\n";
			cout << "1，用户登录 2，用户注册 3，管理员登录 #安全退出\n";
			cout << "====================================================================\n";
			cin >> c;
		}
		else
			c = '1';//新注册的用户直接登录
		file uifo(USER_LIST_FILE);//已经存在的用户的用户名，密码等信息
		user_info *head = uifo.open_user_list();
		if (head == NULL){
			cout << "找不到用户列表信息！\n";
		}
		switch (c){
		case '1':
			if (head == NULL)
				break;
			//用户登录
			if (!b_new_user)
			{
				cout << "输入用户名\n";
				cin >> name;
				cout << "输入密码\n";
				cin >> password;
			}

			for (temp = head; temp != NULL; temp = temp->next){
				if (temp->name == name){
					if (b_new_user || temp->password == password){
						//用户名密码匹配
						//登录成功
						//创建 user 对象，与用户进行交互，暂未实现
						cout << "登录成功！\n";
						bool user_loop = true;
						user me(name);
						if (b_new_user)
						{
							//新用户
							//创建购物车文件
							me.clear_shopping_cart();
							b_new_user = false;
						}
						while (user_loop){
							cout << "===============================================================================================\n";
							cout << "0，注销登录 1，查看商品 2，商品搜索 3，添加商品至购物车 4，删除购物车商品 5，查看购物车 6，结账\n";
							cout << "===============================================================================================\n";
							cout << "输入操作：\n";
							cin >> c;
							switch (c){
							case'0':
								user_loop = false;
								break;
							case'1':
								me.overview_goods();
								for (itr = me.data.begin(); itr != me.data.end(); itr++){
									out_id = itr->first;
									cout << out_id.get() << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
								}
								break;
							case'2':
								cout << "输入需要搜索的商品的名称：\n";
								cin >> me.name;
								if (!me.search_goods()){
									//找不到这在商品
									cout << "输入了错误的商品名称！\n";
									break;
								}
								for (itr = me.data.begin(); itr != me.data.end(); itr++){
									out_id = itr->first;
									cout << out_id.get() << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
								}
								break;
							case'3':
								cout << "输入商品ID：\n";
								cin >> str;
								cout << "输入数量：\n";
								cin >> me.num;
								if (str.length() != 5){
									cout << "ID 长度不正确，请输入正确的长度\n";
									break;
								}
								if (str.at(0) != GOODS_ID_FIRST){
									cout << "添加失败！，输入了错误的ID\n";
									break;
								}
								me.id.set((char*)str.data());
								if (me.add_goods_to_shopping_cart())
								{
									cout << "添加成功！\n";
								}
								else
								{
									cout << "添加失败！，商品ID不存在或者输入的数量超过了库存数目！\n";
								}
								break;
							case'4':
								cout << "输入商品ID：\n";
								cin >> str;
								cout << "输入数量：\n";
								cin >> me.num;
								if (str.length() != 5){
									cout << "ID 长度不正确，请输入正确的长度\n";
									break;
								}
								if (str.at(0) != GOODS_ID_FIRST){
									cout << "删除失败！，输入了错误的ID\n";
									break;
								}
								me.id.set((char*)str.data());
								if (me.sub_num_of_shopping_cart())
								{
									cout << "删除成功！\n";
								}
								else
								{
									cout << "删除失败！，商品ID不存在或者输入的数量超过了购物车物品数目！\n";
								}
								break;
							case'5':
								me.overview_shopping_cart();
								if (me.data.size() == 0)
								{
									cout << "购物车为空！\n";
									break;
								}
								for (itr = me.data.begin(); itr != me.data.end(); itr++){
									out_id = itr->first;
									cout << out_id.get() << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
								}
								break;
							case'6':
								if (!me.checkout())
								{
									if (me.data.size() == 0)
									{
										cout << "购物车为空！\n";
										break;
									}
									cout << "结账失败，购物车中存在被删除的商品或者商品数量大于库存！\n";
									break;
								}
								for (itr = me.data.begin(); itr != me.data.end(); itr++){
									out_id = itr->first;
									cout << out_id.get() << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
								}
								cout << "总价格为：" << me.price << "\n是否结账(Y/N)：";
								cin >> c;
								switch(c){
								case'Y':
									if (me.payment())
										cout << "结账成功！\n";
									else
										cout << "结账失败！\n";
									break;
								case'N':
									cout << "取消结账！\n";
									break;
								default:
									cout << "输入错误！\n";
								}
								break;
							default:
								cout << "输入错误！\n";
								break;
							}
						}
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
				b_new_user = true;
			}
			break;
		case'3':
			//管理员登录
			cout << "输入管理员账号\n";
			//cin >> name;
			cout << "请输入管理员密码\n";
			//cin >> password;
			if (1||name == ADMIN_NAME && password == ADMIN_PASSWORD){
				//管理员登录成功
				cout << "登录成功\n";
				Admin admin;
				bool admin_loop = true;
				while (admin_loop){
					cout << "===========================================================================\n";
					cout << "0，注销登录 1，查询商品 2，增加商品 3，删除商品 4，修改商品数量 5，售货清单\n";
					cout << "===========================================================================\n";
					cout << "输入操作：\n";
					cin >> c;
					switch (c){
					case'0':
						admin_loop = false;
						break;
					case'1':
						admin.search_goods();
						for (itr = admin.data.begin(); itr != admin.data.end(); itr++){
							out_id = itr->first;
							cout << out_id.get() << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
						}
						break;
					case'2':
						cout << "输入增加商品的名称 品牌 价格 数量：";
						cin >> admin.info.name >> admin.info.brand >> admin.info.price >> admin.info.num;
						if (admin.insert_goods()){
							cout << "增加成功！\n";
						}
						else
							cout << "增加失败！\n";
						break;
					case'3':
						cout << "输入删除商品的ID：";
						cin >> str;
						if (str.length() != 5){
							cout << "ID 长度不正确，请输入正确的长度\n";
							break;
						}
						if (str.at(0) != GOODS_ID_FIRST){
							cout << "删除失败！，输入了错误的ID\n";
							break;
						}
						admin.id.set((char*)str.data());
						if (admin.delete_goods())
							cout << "删除成功！\n";
						else
							cout << "删除失败！，输入了错误的ID\n";
						break;
					case'4':
						cout << "===================================================\n";
						cout << "0，增加商品数量 1，减少商品数量 2，直接修改商品数量\n";
						cout << "===================================================\n";
						cin >> c;
						if (c == '0')
							myflag = ADD;
						else if (c == '1')
							myflag = SUB;
						else if (c == '2')
							myflag = COVER;
						else
						{
							cout << "错误的输入！\n";
							break;
						}
						cout << "输入修改商品的ID：";
						cin >> str;
						cout << "输入修改的数量：";
						cin >> admin.num;
						if (str.length() != 5){
							cout << "ID 长度不正确，请输入正确的长度\n";
							break;
						}
						if (str.at(0) != GOODS_ID_FIRST){
							cout << "修改失败！，输入了错误的数量或ID\n";
							break;
						}
						admin.id.set((char*)str.data());
						if (admin.change_goods_number(myflag))
							cout << "修改成功！\n";
						else
							cout << "修改失败！，输入了错误的数量或ID\n";
						break;
					case'5':
						admin.sell_list_overview();
						for (itr = admin.data.begin(); itr != admin.data.end(); itr++){
							out_id = itr->first;
							cout << out_id.get() << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
							for (p_sell_list_temp = itr->second.next; p_sell_list_temp != NULL; p_sell_list_temp = p_sell_list_temp->next){
								cout << out_id.get() << " " << p_sell_list_temp->name << " " << p_sell_list_temp->brand << " " << p_sell_list_temp->price << ' ' << p_sell_list_temp->num << endl;
							}
						}
						break;
					default:
						cout << "输入错误！\n";
						break;
					}
				}
				
			}
			else{
				cout << "账号或者密码输入错误，登录失败！\n";
			}
			break;
		case'#':
			cout << "成功安全退出\n";
			loop = false;
			break;
		default:
			//
			cout << "输入错误！\n";
			break;
		}

	}
	/*database data;
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

	for (itr = data.begin(); itr != data.end(); itr++){
	cout << itr->first << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
	}*/


	system("pause");
	return 0;
}

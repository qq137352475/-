#include"project.h"

/*
��ʵ�ֹ��ܣ�
�� ��� �����嵥 �е����ݶ�ȡ������ database �С�
�� ���ﳵ�е����� ����ָ�����ļ���
���޸Ĺ��� database ���� ���.txt
׷�� �����嵥 �е���Ŀ
�û��ĵ�¼��ע��
����Ա�����ݵĲ���
����Ա���ۻ��嵥�Ĳ�ѯ��δʵ��
����Ա�޸���Ʒ��Ϣ֮����û����ﳵ�ĸ�����δʵ��
�û����� ���ﳵ��δ ʵ��
ע�����û�������δʵ��
tip: ɾ���Ѿ�ɾ������Ʒ��Ӱ��
�޸���ɾ����Ʒ�������޷�����
*/

//enum goods_change_flag{ ADD, SUB, COVER };

int main(){
	bool loop = true;

	user_info *temp;
	user_info new_user;//������Ҫ�������û�����Ϣ�����������
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
			cout << "1���û���¼ 2���û�ע�� 3������Ա��¼ #��ȫ�˳�\n";
			cout << "====================================================================\n";
			cin >> c;
		}
		else
			c = '1';//��ע����û�ֱ�ӵ�¼
		file uifo(USER_LIST_FILE);//�Ѿ����ڵ��û����û������������Ϣ
		user_info *head = uifo.open_user_list();
		if (head == NULL){
			cout << "�Ҳ����û��б���Ϣ��\n";
		}
		switch (c){
		case '1':
			if (head == NULL)
				break;
			//�û���¼
			if (!b_new_user)
			{
				cout << "�����û���\n";
				cin >> name;
				cout << "��������\n";
				cin >> password;
			}

			for (temp = head; temp != NULL; temp = temp->next){
				if (temp->name == name){
					if (b_new_user || temp->password == password){
						//�û�������ƥ��
						//��¼�ɹ�
						//���� user �������û����н�������δʵ��
						cout << "��¼�ɹ���\n";
						bool user_loop = true;
						user me(name);
						if (b_new_user)
						{
							//���û�
							//�������ﳵ�ļ�
							me.clear_shopping_cart();
							b_new_user = false;
						}
						while (user_loop){
							cout << "===============================================================================================\n";
							cout << "0��ע����¼ 1���鿴��Ʒ 2����Ʒ���� 3�������Ʒ�����ﳵ 4��ɾ�����ﳵ��Ʒ 5���鿴���ﳵ 6������\n";
							cout << "===============================================================================================\n";
							cout << "���������\n";
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
								cout << "������Ҫ��������Ʒ�����ƣ�\n";
								cin >> me.name;
								if (!me.search_goods()){
									//�Ҳ���������Ʒ
									cout << "�����˴������Ʒ���ƣ�\n";
									break;
								}
								for (itr = me.data.begin(); itr != me.data.end(); itr++){
									out_id = itr->first;
									cout << out_id.get() << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
								}
								break;
							case'3':
								cout << "������ƷID��\n";
								cin >> str;
								cout << "����������\n";
								cin >> me.num;
								if (str.length() != 5){
									cout << "ID ���Ȳ���ȷ����������ȷ�ĳ���\n";
									break;
								}
								if (str.at(0) != GOODS_ID_FIRST){
									cout << "���ʧ�ܣ��������˴����ID\n";
									break;
								}
								me.id.set((char*)str.data());
								if (me.add_goods_to_shopping_cart())
								{
									cout << "��ӳɹ���\n";
								}
								else
								{
									cout << "���ʧ�ܣ�����ƷID�����ڻ�����������������˿����Ŀ��\n";
								}
								break;
							case'4':
								cout << "������ƷID��\n";
								cin >> str;
								cout << "����������\n";
								cin >> me.num;
								if (str.length() != 5){
									cout << "ID ���Ȳ���ȷ����������ȷ�ĳ���\n";
									break;
								}
								if (str.at(0) != GOODS_ID_FIRST){
									cout << "ɾ��ʧ�ܣ��������˴����ID\n";
									break;
								}
								me.id.set((char*)str.data());
								if (me.sub_num_of_shopping_cart())
								{
									cout << "ɾ���ɹ���\n";
								}
								else
								{
									cout << "ɾ��ʧ�ܣ�����ƷID�����ڻ�����������������˹��ﳵ��Ʒ��Ŀ��\n";
								}
								break;
							case'5':
								me.overview_shopping_cart();
								if (me.data.size() == 0)
								{
									cout << "���ﳵΪ�գ�\n";
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
										cout << "���ﳵΪ�գ�\n";
										break;
									}
									cout << "����ʧ�ܣ����ﳵ�д��ڱ�ɾ������Ʒ������Ʒ�������ڿ�棡\n";
									break;
								}
								for (itr = me.data.begin(); itr != me.data.end(); itr++){
									out_id = itr->first;
									cout << out_id.get() << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
								}
								cout << "�ܼ۸�Ϊ��" << me.price << "\n�Ƿ����(Y/N)��";
								cin >> c;
								switch(c){
								case'Y':
									if (me.payment())
										cout << "���˳ɹ���\n";
									else
										cout << "����ʧ�ܣ�\n";
									break;
								case'N':
									cout << "ȡ�����ˣ�\n";
									break;
								default:
									cout << "�������\n";
								}
								break;
							default:
								cout << "�������\n";
								break;
							}
						}
						break;
					}
					else{
						//�û��� ���벻ƥ��
						cout << "�����������\n";
						break;
					}
				}
			}
			if (temp == NULL){
				//�Ҳ����û���
				cout << "�Ҳ������û����������������ע�����û���\n";
			}
			break;
		case'2':
			if (head == NULL)
				break;
			//�û�ע��
			cout << "�����û���\n";
			cin >> name;
			for (temp = head; temp != NULL; temp = temp->next){
				if (temp->name == name){
					//�Ѵ��ڵ��û���
					cout << "�Ѵ��ڵ��û������������������ֱ�ӵ�¼\n";
					break;
				}
			}
			if (temp == NULL){
				//�����ڵ��û���
				cout << "��������\n";
				cin >> password;
				new_user.name = name;
				new_user.password = password;
				uifo.write_back_user_list(&new_user);//�����û�д���ļ�
				//�����ɹ�
				//���� user �������û����н�������δʵ��
				cout << "ע��ɹ���\n";
				b_new_user = true;
			}
			break;
		case'3':
			//����Ա��¼
			cout << "�������Ա�˺�\n";
			//cin >> name;
			cout << "���������Ա����\n";
			//cin >> password;
			if (1||name == ADMIN_NAME && password == ADMIN_PASSWORD){
				//����Ա��¼�ɹ�
				cout << "��¼�ɹ�\n";
				Admin admin;
				bool admin_loop = true;
				while (admin_loop){
					cout << "===========================================================================\n";
					cout << "0��ע����¼ 1����ѯ��Ʒ 2��������Ʒ 3��ɾ����Ʒ 4���޸���Ʒ���� 5���ۻ��嵥\n";
					cout << "===========================================================================\n";
					cout << "���������\n";
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
						cout << "����������Ʒ������ Ʒ�� �۸� ������";
						cin >> admin.info.name >> admin.info.brand >> admin.info.price >> admin.info.num;
						if (admin.insert_goods()){
							cout << "���ӳɹ���\n";
						}
						else
							cout << "����ʧ�ܣ�\n";
						break;
					case'3':
						cout << "����ɾ����Ʒ��ID��";
						cin >> str;
						if (str.length() != 5){
							cout << "ID ���Ȳ���ȷ����������ȷ�ĳ���\n";
							break;
						}
						if (str.at(0) != GOODS_ID_FIRST){
							cout << "ɾ��ʧ�ܣ��������˴����ID\n";
							break;
						}
						admin.id.set((char*)str.data());
						if (admin.delete_goods())
							cout << "ɾ���ɹ���\n";
						else
							cout << "ɾ��ʧ�ܣ��������˴����ID\n";
						break;
					case'4':
						cout << "===================================================\n";
						cout << "0��������Ʒ���� 1��������Ʒ���� 2��ֱ���޸���Ʒ����\n";
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
							cout << "��������룡\n";
							break;
						}
						cout << "�����޸���Ʒ��ID��";
						cin >> str;
						cout << "�����޸ĵ�������";
						cin >> admin.num;
						if (str.length() != 5){
							cout << "ID ���Ȳ���ȷ����������ȷ�ĳ���\n";
							break;
						}
						if (str.at(0) != GOODS_ID_FIRST){
							cout << "�޸�ʧ�ܣ��������˴����������ID\n";
							break;
						}
						admin.id.set((char*)str.data());
						if (admin.change_goods_number(myflag))
							cout << "�޸ĳɹ���\n";
						else
							cout << "�޸�ʧ�ܣ��������˴����������ID\n";
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
						cout << "�������\n";
						break;
					}
				}
				
			}
			else{
				cout << "�˺Ż�������������󣬵�¼ʧ�ܣ�\n";
			}
			break;
		case'#':
			cout << "�ɹ���ȫ�˳�\n";
			loop = false;
			break;
		default:
			//
			cout << "�������\n";
			break;
		}

	}
	/*database data;
	//file f(GOODS_FILE);
	file f(SHOPPING_LIST_FILE);
	//f.read(data);

	//file f("data\\user5.txt");
	goods_info gf;
	gf.brand = "����Ʒ��2";
	gf.name = "��������2";
	gf.num = 10;
	gf.price = 51.1;

	data.insert(pair<int, goods_info>(16, gf));
	
	if (f.write(data,"user_test")){
	cout << "�ɹ�" << endl;
	}
	else
	cout << "ʧ��" << endl;
	
	database::iterator itr;

	for (itr = data.begin(); itr != data.end(); itr++){
	cout << itr->first << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
	}*/


	system("pause");
	return 0;
}

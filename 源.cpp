#include"project.h"

/*
��ʵ�ֹ��ܣ�
�� ��� �����嵥 �е����ݶ�ȡ������ database �С�
�� ���ﳵ�е����� ����ָ�����ļ���
���޸Ĺ��� database ���� ���.txt
׷�� �����嵥 �е���Ŀ
�û��ĵ�¼��ע��
��һ��ʵ�� �û������Ա�����ݵĲ���
*/



int main(){
	bool loop = true;
	while (loop){
		cout << "====================================================================\n";
		cout << "1���û���¼ 2���û�ע�� 3������Ա��¼ #��ȫ�˳�\n";
		cout << "====================================================================\n";
		char c;
		cin >> c;
		file uifo(USER_LIST_FILE);//�Ѿ����ڵ��û����û������������Ϣ
		user_info *head = uifo.open_user_list();
		if (head == NULL){
			cout << "�Ҳ����û��б���Ϣ��\n";
		}
		user_info *temp = head;
		user_info new_user;//������Ҫ�������û�����Ϣ�����������
		User_name name;
		User_password password;
		switch (c){
		case '1':
			if (head == NULL)
				break;
			//�û���¼
			cout << "�����û���\n";
			cin >> name;
			cout << "��������\n";
			cin >> password;
			for (temp = head; temp != NULL; temp = temp->next){
				if (temp->name == name){
					if (temp->password == password){
						//�û�������ƥ��
						//��¼�ɹ�
						//���� user �������û����н�������δʵ��
						cout << "��¼�ɹ���\n";
						bool user_loop = true;
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

								break;
							case'2':
								break;
							case'3':
								break;
							case'4':
								break;
							case'5':
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
			}
			break;
		case'3':
			//����Ա��¼
			cout << "�������Ա�˺�\n";
			cin >> name;
			cout << "���������Ա����\n";
			cin >> password;
			if (name == ADMIN_NAME && password == ADMIN_PASSWORD){
				//����Ա��¼�ɹ�
				//��������Ա������δʵ��
				cout << "��¼�ɹ�\n";
				Admin admin;
				bool admin_loop = true;
				while (admin_loop){
					cout << "===========================================================================\n";
					cout << "0��ע����¼ 1����ѯ��Ʒ 2��������Ʒ 3��ɾ����Ʒ 4���޸���Ʒ���� 5���ۻ��嵥\n";
					cout << "===========================================================================\n";
					cout << "���������\n";
					cin >> c;
					database tempdata;
					database::iterator itr;
					switch (c){
					case'0':
						admin_loop = false;
						break;
					case'1':
						admin.search_goods(tempdata);
						for (itr = tempdata.begin(); itr != tempdata.end(); itr++){
							cout << itr->first << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
						}
						break;
					case'2':
						break;
					case'3':
						break;
					case'4':
						break;
					case'5':
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

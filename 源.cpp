#include"project.h"

/*
��ʵ�ֹ��ܣ�
�� ��� �����嵥 �е����ݶ�ȡ������ database �С�
�� ���ﳵ�е����� ����ָ�����ļ���
���޸Ĺ��� database ���� ���.txt
׷�� �����嵥 �е���Ŀ
*/



int main(){
	cout << "====================================================================\n";
	cout << "1���û���¼ 2���û�ע�� 3������Ա��¼\n";
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
	gf.brand = "����Ʒ��2";
	gf.name = "��������2";
	gf.num = 10;
	gf.price = 51.1;

	data.insert(pair<int, goods_info>(16, gf));
	/*
	if (f.write(data,"user_test")){
		cout << "�ɹ�" << endl;
	}
	else
		cout << "ʧ��" << endl;
		*/
	database::iterator itr;

	/*for (itr = data.begin(); itr != data.end(); itr++){
		cout << itr->first << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
	}*/


	system("pause");
	return 0;
}
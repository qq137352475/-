#include"project.h"

/*
��ʵ�ֹ��ܣ�
�� ��� �����嵥 �е����ݶ�ȡ������ database �С�
�� ���ﳵ�е����� ����ָ�����ļ���
���޸Ĺ��� database ���� ���.txt
׷�� �����嵥 �е���Ŀ
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

	/*for (itr = data.begin(); itr != data.end(); itr++){
		cout << itr->first << " " << itr->second.name << " " << itr->second.brand << " " << itr->second.price << ' ' << itr->second.num << endl;
	}*/


	system("pause");
	return 0;
}
#include"project.h"

ID::ID(){
	return;
}

ID::ID(int n){
	sprintf_s(buf, GOODS_ID_LENGTH, "%c%04d", 'F', n);
	return;
}

ID::operator int(){
	char temp[GOODS_ID_LENGTH - 1];
	for (int i = 0; i < GOODS_ID_LENGTH - 1; i++){
		temp[i] = buf[i + 1];
	}
	return atoi(temp);
}

ifstream& operator >>(ifstream &in, ID &id){
	in >> id.buf;
	return in;
}

int main(){
	ifstream file;
	file.open(GOODS_FILE, ios::in);
	if (!file){
		cout << "´ò¿ªÊ§°Ü" << endl;
		return 0;
	}
	char buf[50];
	file.getline(buf,50);
	ID id;
	file >> id;
	int n = int(id);
	cout << n << endl;
	ID id2 = n + 1;
	cout << id2.get() << endl;
	system("pause");
	return 0;
}
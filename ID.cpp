#include"project.h"

ID::ID(){
	return;
}

ID::ID(int n){
	sprintf_s(buf, GOODS_ID_LENGTH, "%c%04d", GOODS_ID_FIRST, n);
	return;
}

ID::operator int(){
	char temp[GOODS_ID_LENGTH - 1];
	for (int i = 0; i < GOODS_ID_LENGTH - 1; i++){
		temp[i] = buf[i + 1];
	}
	return atoi(temp);
}
#include"project.h"

ID::ID(){
	return;
}

ID::ID(int n){
	sprintf_s(buf, GOODS_ID_LENGTH, "%c%04d", GOODS_ID_FIRST, n);
	return;
}

ID::operator int(){
	if (strlen(buf) != GOODS_ID_LENGTH - 1)
	{
		return 0;
	}
	char temp[GOODS_ID_LENGTH - 1];
	for (int i = 0; i < GOODS_ID_LENGTH - 1; i++){
		temp[i] = buf[i + 1];
	}
	int n = atoi(temp);
	return n;
}
void ID::set(char * temp)
{
	for (int i = 0; i < GOODS_ID_LENGTH; i++)
	{
		buf[i] = temp[i];
	}
	temp[GOODS_ID_LENGTH - 1] = '\0';
}
#include"project.h"

shopping_cart::shopping_cart(){
	username = ' ';
	return;
}

shopping_cart::shopping_cart(User_name temp){
	username = temp;
	string str;
	str = temp + ".txt";
	f = (char*)str.data();
	data.clear();
	f.read(data);

}
void shopping_cart::chang_user(User_name temp){
	username = temp;
	string str;
	str = temp + ".txt";
	f = (char*)str.data();
	data.clear();
	f.read(data);
}
#include"project.h"

sell_list::sell_list(){
	f = SHOPPING_LIST_FILE;
	data.clear();
	f.read(data);
	return;
}
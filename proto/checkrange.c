
int check_range_exp(int number, char* expression){
	
	int first_half_len = strcspn(expression, "-");
	char* firsthalf = (char*)malloc(first_half_len+1);
	strncpy(firsthalf, expression, first_half_len);
	firsthalf[first_half_len] = '\0';
	
	char* end_num = (char*)strpbrk(expression, "-")+1;

	int firstnum = atoi(firsthalf);
	int secondnum = atoi(end_num);
	if (number <= secondnum && number >= firstnum){
		return 1;
	}
	return 0;
}

int main(){
	int checked = 10;
	check_range_exp(checked, "2-10");
	return 0;
}
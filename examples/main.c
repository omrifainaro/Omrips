void addTo(int* a, int b){
	*a += b;
}

int mul(int a, int b){
	return a * b;
}

int main(){
	int a = 10, b = 20;
	int c = 0;

	addTo(&a, b);
	c = mul(a, b);
	return c;
}
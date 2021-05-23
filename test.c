#include <stdio.h>

unsigned short a1 = 1;
unsigned short a2 = 2;
unsigned short a3 = 997;

unsigned short b1 = 12;
unsigned short b2 = 3;
unsigned short b3 = 2;
unsigned short b4 = 61;

struct TData2 { // описание структуры в виде битовых полей. формат "битовое поле:ширина"
	unsigned short a1 : 3;
	unsigned short a2 : 3;
	unsigned short a3 : 10;
	unsigned short b1 : 4;
	unsigned short b2 : 3;
	unsigned short b3 : 3;
	unsigned short b4 : 6;
};

void DecToHex(int p_intValue, char* buf) // десятичное в 16-ричную
{
	sprintf(buf, "%X", p_intValue);
}

// buf - массив, в котором будут хранится данные
void dump(struct TData2* p, char buf[][32]) { 
	DecToHex(p->a1, buf[0]);
	DecToHex(p->a2, buf[1]);
	DecToHex(p->a3, buf[2]);
	DecToHex(p->b1, buf[3]);
	DecToHex(p->b2, buf[4]);
	DecToHex(p->b3, buf[5]);
	DecToHex(p->b4, buf[6]);
}


int main(){
    int i;
	struct TData2 d;
	d.a1 = a1;
	d.a2 = a2;
	d.a3 = a3;

	d.b1 = b1;
	d.b2 = b2;
	d.b3 = b3;
	d.b4 = b4;
	
	char bufData[7][32]; //[кол-во эл-тов в стуктуре][]
	dump(&d, bufData);
	for(i=0;i<7;i++) printf("%s ",bufData[i]);
}

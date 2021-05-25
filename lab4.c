#include <stdio.h>
#include <winsock2.h>
//--1 --------------------------------------------------------------------------
void dump (unsigned char *p, int s, char buf[][32]); // p параметр - адрес данных, s параметр - их размер. Функция нужна для вывода данных побайтно, buf - буффер, для сохранение
void pdump (unsigned char *p, int s); // p параметр - адрес данных, s параметр - их размер. Функция нужна для вывода данных побайтно
void swap (unsigned short *d, int size); // осуществляет перестановку данных. перестраивает порядок байтов в сетевой.
void unswap (unsigned short *d, int size); // осуществляет перестановку данных. перестраивает сетевой порядок в байтовый

unsigned short getf (unsigned short d, unsigned short sb, unsigned short w); // получение поля. d - значение слова, sb - стартовый бит(бит начала поля), w - ширина поля. возвращает значение поля
void setf (unsigned short *p, unsigned short d, unsigned short sd, unsigned short w); // устновка поля. p - указатель на слово, в которое мы должны записать все данные. d,sd,w - по аналогии выше.

void Test1 (void); // тест на то, как располагаются байты целого числа
void Test2 (void); // тест на то, как формируются поля
void Test3 (void); // тест с использованием setf,getf (масочная установка полей)
//--2 --------------------------------------------------------------------------
unsigned short a1=1;
unsigned short a2=2;
unsigned short a3=997;

unsigned short b1=12;
unsigned short b2=3;
unsigned short b3=2;
unsigned short b4=61;

char buffer [20][11]; // буффер для пакетов
int amountPackage = 0;
//--3 --------------------------------------------------------------------------
struct  TData2 { // описание структуры в виде битовых полей. формат "битовое поле:ширина"
	unsigned short a1:3;
	unsigned short a2:3;
	unsigned short a3:10;
	unsigned short b1:4;
	unsigned short b2:3;
	unsigned short b3:3;
	unsigned short b4:6;	
};
//--4 --------------------------------------------------------------------------
struct TData3 { //
	unsigned short a;
	unsigned short b;
};
//
//
void Test1 (void){
	unsigned int d=0x01020304;
	puts ("Test1:");
	pdump (&d,sizeof(d));
}
//
void pdump (unsigned char *p, int s){
	int i;
	for (i=0;i<s;++i) {
		printf (i%2? "%02X ":"%02X" ,p[i]);
	}
	puts("");
}

void dump (unsigned char *p, int s, char buf[][32]){
	int i;
	char tempBuf[4][4]; 
	for (i=0;i<s;++i) {
		sprintf (tempBuf[i],i%2? "%02X ":"%02X" ,p[i]);
	}
	buffer[amountPackage][0] = tempBuf[0][0]; buffer[amountPackage][1] = tempBuf[0][1];
	buffer[amountPackage][2] = tempBuf[1][0]; buffer[amountPackage][3] = tempBuf[1][1];
	buffer[amountPackage][4] = ' ';
	buffer[amountPackage][5] = tempBuf[2][0]; buffer[amountPackage][6] = tempBuf[2][1];
	buffer[amountPackage][7] = tempBuf[3][0]; buffer[amountPackage][8] = tempBuf[3][1];
	buffer[amountPackage][9] = '\0';
	puts("");
}

//

void swap(unsigned short *d, int size){
     int i;
     for(i=0;i<size>>1;++i) d[i] = htons(d[i]);
}

void unswap(unsigned short *d,int size){
	int i;
	for(i=0;i<size>>i;++i) d[i] = ntohs(d[i]);
}
//

unsigned short getf(unsigned short d, unsigned short sb, unsigned short w){
	unsigned short m = ((1<<w)-1) << sb;
	return (d&m)>>sb;
}

void setf(unsigned short *p, unsigned short d, unsigned short sb, unsigned short w){
	unsigned short m = ((1<<w)-1) << sb;
	*p &=~m;
	*p|=(d<<sb);
}
//

void Test2(void){
	struct TData2 d;

	d.a1 = a1;
	d.a2 = a2;
	d.a3 = a3;

	d.b1 = b1;
	d.b2 = b2;
	d.b3 = b3;
	d.b4 = b4;

	puts("\nTest2:");

	puts("read fields:");
	printf("a1=%d\n",d.a1);
	printf("a2=%d\n",d.a2);
	printf("a3=%d\n",d.a3);

	puts("dump:");
	dump(&d,sizeof(d), buffer);
	puts(buffer[0]);

	amountPackage++;
	puts("swap:");
	swap(&d,sizeof(d));
	dump(&d,sizeof(d), buffer);
	puts(buffer[1]);
	
	puts("unswap:");
	unswap(&d,sizeof(d));
	dump(&d,sizeof(d), buffer);
	puts(buffer[0]);
}

void Test3(void){
	struct TData3 d;
	setf (&d.a,a1,0,3);
	setf (&d.a,a2,3,3);
	setf (&d.a,a3,6,10);

	setf (&d.b,b1,0,4);
	setf (&d.b,b2,4,3);
	setf (&d.b,b3,7,3);
	setf (&d.b,b4,10,6);

	puts ("\nTest3:");
	puts("read fields:");
	printf("a1=%d\n",getf(d.a,0,3));
	printf("a2=%d\n",getf(d.a,3,3));
	printf("a3=%d\n\n",getf(d.a,6,10));

	puts("dump:");
	dump(&d,sizeof(d), buffer);

	puts("swap:");
	swap(&d,sizeof(d));
	dump(&d,sizeof(d), buffer);
	
	puts("unswap:");
	unswap(&d,sizeof(d));
	dump(&d,sizeof(d), buffer);
}

int main(int argc,char* argv[]){
    Test1();
    Test2();
    Test3();
    
    getchar();
    
    return 0;
}


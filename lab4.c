#include <stdio.h>
#include <winsock2.h>
//--1 --------------------------------------------------------------------------
void dump (unsigned char *p, int s); // p �������� - ����� ������, s �������� - �� ������. ������� ����� ��� ������ ������ ��������.
void swap (unsigned short *d, int size); // ������������ ������������ ������. ������������� ������� ������ � �������.
void unswap (unsigned short *d, int size); // ������������ ������������ ������. ������������� ������� ������� � ��������

unsigned short getf (unsigned short d, unsigned short sb, unsigned short w); // ��������� ����. d - �������� �����, sb - ��������� ���(��� ������ ����), w - ������ ����. ���������� �������� ����
void setf (unsigned short *p, unsigned short d, unsigned short sd, unsigned short w); // �������� ����. p - ��������� �� �����, � ������� �� ������ �������� ��� ������. d,sd,w - �� �������� ����.

void Test1 (void); // ���� �� ��, ��� ������������� ����� ������ �����
void Test2 (void); // ���� �� ��, ��� ����������� ����
void Test3 (void); // ���� � �������������� setf,getf (�������� ��������� �����)
//--2 --------------------------------------------------------------------------
unsigned short a1=1;
unsigned short a2=2;
unsigned short a3=997;

unsigned short b1=12;
unsigned short b2=3;
unsigned short b3=2;
unsigned short b4=61;
//--3 --------------------------------------------------------------------------
struct  TData2 { // �������� ��������� � ���� ������� �����. ������ "������� ����:������"
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
	dump (&d,sizeof(d));
}
//
void dump (unsigned char *p, int s){
	int i;
	for (i=0;i<s;++i)
		printf (i%2? "%02X ":"%02X",p[i]);
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
	dump(&d,sizeof(d));

	puts("swap:");
	swap(&d,sizeof(d));
	dump(&d,sizeof(d));
	
	puts("unswap:");
	unswap(&d,sizeof(d));
	dump(&d,sizeof(d));
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
	dump(&d,sizeof(d));

	puts("swap:");
	swap(&d,sizeof(d));
	dump(&d,sizeof(d));
	
	puts("unswap:");
	unswap(&d,sizeof(d));
	dump(&d,sizeof(d));
}

int main(int argc,char* argv[]){
    Test1();
    Test2();
    Test3();
    
    getchar();
    
    return 0;
}

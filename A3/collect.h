#ifndef COLLECT_H
#define COLLECT_H

char generate(int seed);

class A
{
private:
	char name;

public:
	A(){name='A';}
	char getName(){return name;}
};

class B
{
private:
	char name;
	char B1;

public:
	B(){name='B';}
	char getName(){return name;}
};

class C
{
private:
	char name;
	char C1,C2,C3;

public:
	C(){name='C';}
	char getName(){return name;}
};

class D
{
private:
	char name;
	char D1,D2,D3;
	int D4;

public:
	D(){name='D';}
	char getName(){return name;}
};

class E
{
private:
	char name;
	char E1,E2,E3;
	int E4, E5, E6;

public:
	E(){name='E';}
	char getName(){return name;}
};

class F
{
private:
	char name;
	char F1,F2,F3;
	int F4, F5, F6;
	double F7, F8;

public:
	F(){name='F';}
	char getName(){return name;}
};

class G
{
private:
	char name;
	char G1,G2,G3;
	int G4,G5,G6;
	double G7,G8;
	long double G9,G10;

public:
	G(){name='G';}
	char getName(){return name;}
};

#endif

#include <cstdio>
#include "utils.h"

#define nv 5000


void main()
{

/*
	// ========================
	//  AQUI USAMOS ALIASING y RESIRTIC
	// ========================
	int data1 = 20;
	int data2 = 30;
//  Sin Aliasing
	int resultado = sumAlising(&data1, &data1);
//  Con Restrict
//	int resultado = sumRestrict(&data1, &data2);
	printf("resultado %d\n",resultado);
*/

	// ========================
	//  AQUI USAMOS INTR�NSECOS. _SADD
	// ========================

	/*
    int intrinseco[nv], manual[nv];

	int valor1 = 10, valor2 = 4;

    printf("Sadd intr�nseco\n");
    // int _sadd(int src1, int src2);
    // Adds src1 to src2 and saturates the result.
    // Returns the result
	for(i=1;i<nv;i++){
		intrinseco[i] = _sadd(valor1,valor2);
		printf("a�adir--> %d\n", intrinseco[i]);
	}

    printf("Sadd sin intr�nseco");
	for(i=1;i<nv;i++){
		manual[i] = sadd(valor1,valor2);
		printf("a�adir. Add programado--> %d\n", manual[i]);
	}
	*/

	// ========================
	//  AQUI USAMOS INTR�NSECOS. Multiplicaci�n
	// ========================
	/*
	short in1[nv], in2[nv];
	short *pin1 = &in1[0];
	short *pin2 = &in2[0];
	int N = 100;
	int resultado,i;

	for(i=0;i<N;i++){
		in1[i] = i*10;
		in2[i] = i+10;
	}

	resultado = dotproducto(pin1, pin2, N);
	printf("%d",resultado);
	*/

	// ========================
	//  AQUI USAMOS PRAGMAS
	// ========================
	// ========================
	//  Optimizar bucles haciendo
	//  cuenta descendente
	// ========================
	/*
	int i;
	int N = 200;
	printf("Cuenta creciente\n");
	for (i = 0; i < N; i++){ // i = trip counter, N = trip count
		printf("%d\n",i);
	}
	printf("Cuenta decreciente\n");
	for (i = N; i != 0; i--){ // Downcounting trip counter
		printf("%d\n",i);
	}
	printf("Fin\n");

    */
	// ========================
	//  AQUI USAMOS MUST ITERATE
	// ========================

	short sum[nv], in1[nv], in2[nv];
	short *psum = &sum[0];
	short *pin1 = &in1[0];
	short *pin2 = &in2[0];

	int N = 50;
	int i;

	for(i=0;i<N;i++){
		in1[i] = i*10;
		in2[i] = i+10;
	}
	printf("\nSin must iterator\n");
	vecsumSinMust(psum, pin1, pin2, N);

	for(i=0;i<N;i++){
		in1[i] = i*10;
		in2[i] = i+10;
	}

	printf("\Con must iterator\n");
	vecsumConMust(psum, pin1, pin2, N);


	// ========================
	//  AQUI USAMOS _nassert
	// ========================
	/*
	short in1[nv], in2[nv], sum[nv];
	short *pin1 = &in1[0];
	short *pin2 = &in2[0];
	int N = 100;
	int resultado,i;

	for(i=0;i<N;i++){
		in1[i] = i*10;
		in2[i] = i+10;
	}

	resultado = dotproductonassert(pin1, pin2, N);
	printf("%d",resultado);
	*/

	// ========================
	//  AQUI USAMOS Desenrrollar bucles
	// ========================

	/*
	int sum[nv], in1[nv], in2[nv];
	int *psum = &sum[0];
	int *pin1 = &in1[0];
	int *pin2 = &in2[0];
	int N = 10;
	int i;

	for(i=0;i<N;i++){
		in1[i] = i*10;
		in2[i] = i+10;
	}

	vecsumSinDesenrrollar(psum, pin1, pin2, N);
	vecsumDesenrrollado(psum, pin1, pin2, N);
	*/

}


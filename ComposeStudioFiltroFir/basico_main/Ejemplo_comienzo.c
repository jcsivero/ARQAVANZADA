#include <cstdio>


#define nvMax 3500

float v_datos_default [] = {1,3,2,5,7,11,4,2,1,3};
float v_coef_default [] = {0.33,0.33,0.33};
float salida,valorEntrada,borradorFloat;

int indiceValor,indiceCoeficiente,tmp,nv,nc;
char borradorCaracter;

float * restrict v_coef; ///puntero hacia array con los coeficientes leidos desde fichero csv
float * restrict v_datos; ///puntero hacia array con los datos leidos desde fichero csv

void obtenerValores()
{

	///
	///Primero intento abrir fichero de coeficientes
	///
	FILE *fich_num = fopen("Coeficientes.csv","r");

	if (fich_num == NULL){
		///
		///si no se encontr� o pudo abrir, lo indico y utilizao el array por defecto.
		///
		printf("\nNo se puede abrir fichero: Coeficientes.csv");
		printf("\nUsando valores por defecto");

		nc=3;
		v_coef =  v_coef_default;
	}

	else
	{

		nc=0;
		while (!feof(fich_num))
		{
			fscanf(fich_num,"%f",&borradorFloat); ///leo el valor en flotante
			nc++; ///numero de coeficientes que he leido
			if (!feof(fich_num))
				fscanf(fich_num,"%c",&borradorCaracter); ///leo la coma.

		}

		v_coef = (float *)  malloc(nc * sizeof(float));
		fseek(fich_num,0,SEEK_SET); ///me vuelvo a colocar al principio del fichero

		nc=0;
		while (!feof(fich_num))
		{
			fscanf(fich_num,"%f",&v_coef[nc]); ///leo el valor en flotante
			nc++; ///numero de coeficientes que he leido
			if (!feof(fich_num))
				fscanf(fich_num,"%c",&borradorCaracter); ///leo la coma.

		}

		fclose(fich_num);
	}


	///Imprimo los coeficientes leidos.
    for ( tmp = 0; tmp < nc; tmp++)
    	printf("\nCoeficiente %d: %lf",tmp,v_coef[tmp]);

	///
	///Ahora intento lo mismo con fichero de datos
	///
	fich_num = fopen("musica4.csv","r");

	if (fich_num == NULL){
		///
		///si no se encontr� o pudo abrir, lo indico y utilizao el array por defecto.
		///
		printf("\nNo se puede abrir fichero: musica4.csv");
		printf("\nUsando valores por defecto");

		nv=10;
		v_datos =  v_datos_default;
	}

	else
	{
 ///aqui leo el fichero y voy contando para saber cuantos memoria tengo que asignar realmente.As�
		//no dependo de un tama�o prefijado, sino depende del tama�o del fichero.
		nv=0;
		while ((!feof(fich_num)) && (nv < nvMax)) ///limite de valores a leer.
		{
			fscanf(fich_num,"%f",&borradorFloat); ///leo el valor en flotante
			nv++; ///numero de coeficientes que he leido
			if (!feof(fich_num))
				fscanf(fich_num,"%c",&borradorCaracter); ///leo la coma.

		}

		v_datos = (float *)  malloc(nv * sizeof(float));
		fseek(fich_num,0,SEEK_SET); ///me vuelvo a colocar al principio del fichero

		nv=0;
		while ((!feof(fich_num)) && (nv < nvMax)) ///establezco un l�mite de valores en 3500
		{
			fscanf(fich_num,"%f",&v_datos[nv]); ///leo el valor en flotante
			nv++; ///numero de coeficientes que he leido
			if (!feof(fich_num))
				fscanf(fich_num,"%c",&borradorCaracter); ///leo la coma.

		}

		fclose(fich_num);
	}

///Imprimo los valores leidos
	    for ( tmp = 0; tmp < nv; tmp++)
	    	printf("\nValor %d: %lf",tmp,v_datos[tmp]);


}
void main()
{

obtenerValores();

///Una vez rellenados los vectores de coeficientes y de datos, procedo al c�culo de la salida

	///bucle que comprobar� todas las entradas posibles.
  for (indiceValor = 0; indiceValor < nv; indiceValor++)
  {
		salida=0.0; ///inicialmente salida = 0

	  //bucle que realiza el c�culo para una entrada dada
	    for (indiceCoeficiente=0; indiceCoeficiente < nc;indiceCoeficiente++) ///tengo que sumar si o s�, mientras no recorra todos los coeficientes.
	    {
	      tmp=indiceValor-indiceCoeficiente;
	    	if ((tmp >= 0) && (tmp < nv))  ///controlo que el �ndice de datos est� dentro del rango, si no es as�, pongo el valor a cero, para que al multiplicar de cero y no aumente nada su valor en la suma.
	    		///esto puede pasar cuando el valor del �ndice es m�s peque�o que el n�mero de coeficientes que hay, por ejemplo.

	    		valorEntrada= v_datos[tmp];
	    	else
	    		valorEntrada = 0.0;

	    	salida = salida + (v_coef[indiceCoeficiente]*valorEntrada);

	    }

	    //printf("\nIteraci�n : %d Valor: %lf",indiceValor,salida);
  }

}

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

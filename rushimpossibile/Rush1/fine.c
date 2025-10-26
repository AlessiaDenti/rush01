#include <stdio.h>

int checkrighe(int nume, int riga[4])	//cerca numero in righe
{
	int j =0;
	while(j<4)
	{
		if(riga[j] == nume)
			return 1;
		j++;
	}
	return 0;
}

int checkcol(int nume,int col, int matrice[4][4])	//cerca numero in colonne
{
	int i = 0;
	while(i<4)
	{
		if(matrice[i][col] == nume)
			return 1;
		i++;
	}
	return 0;
}


int checkalt(int col, int matrice[4][4])		//controlla altezza delle colonne
{
	int i =0;
	int k = 1;
	int max = matrice[0][col];
	while (i < 4 && max != 4)
	{
		if(matrice[i+1][col] > max)
		{
			k++;
			max = matrice[i+1][col];
		}
		i++;
	}
	return (k); // numero di scatole vedo contandole 
}

int checkaltrev(int col, int matrice[4][4])		//controlla altezza delle colonne
{
	int i = 3;
	int k = 1;
	int max = matrice[3][col];
	while (i > 0 && max != 4)
	{
		if(matrice[i-1][col] > max)
		{
			k++;
			max = matrice[i-1][col];
		}
		i--;
	}
	return (k); // numero di scatole vedo contandole 
}

void riempicolonna(int p, int col, int matrice[4][4]) // riempe la colonna
{
	int i = 0;
	int n = 1+p;
	while (i < 4)				//colonne
		{
			if (matrice[i][col] == 0)		//cella vuota
			{	
				while (n <= 4)
				{
					if(checkcol(n,col,matrice) == 0 && checkrighe(n, matrice[i]) == 0)
					{
						matrice[i][col] = n;
						break;
					}
					n++;
				}
			}
			n = 1;
			i++;
		}	// riempito colonna
}


int main(void)
{
	int i = -1;
	int j;
	int matricey[4][4] = {{3,0,0,0} ,{2,0,0,0}, {1,0,0,0},{4,0,0,0}};
	//int cerca[16] = {4,3,2,1,1,2,2,2,4,3,2,1,1,2,2,2}; 
	//int cerca[16] = {2,2,1,4,2,2,4,1,2,1,2,3,2,3,2,1}; 
	int cerca[16] = {1,3,2,1,1,2,2,2,4,3,2,1,1,2,2,2}; 


	//riempicolonna(0, 0, matricey);
	printf("%d \n",checkaltrev(0, matricey));
	//printf("\n"); 
	//caso4(4, 1, cerca, matricey);
	//g(1, 4, cerca, matricey);
	//put4_4(matricey);
	//back(cerca, matricey, 0);
	//printf("%d \n", trovan(2,cerca));
	while (++i <4){
		j=-1;
		while(++j <4)
			printf("%d", matricey[i][j]);
		printf("\n");  
	}
}

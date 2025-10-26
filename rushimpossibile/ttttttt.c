/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   riempitabella.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 15:27:50 by adenti            #+#    #+#             */
/*   Updated: 2025/10/25 15:27:53 by adenti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
	
#include <stdio.h>

int checkrighe(int nume, int riga[4])
{
    int j = 0;
    while(j < 4)
    {
        if(riga[j] == nume)
            return 1;
        j++;
    }
    return 0;
}

int checkcol(int nume, int col, int matrice[4][4])
{
    int i = 0;
    while(i < 4)
    {
        if(matrice[i][col] == nume)
            return 1;
        i++;
    }
    return 0;
}

int checkalt(int col, int matrice[4][4])
{
    int i = 0;
    int k = 1;
    int max = matrice[0][col];
    while (i < 3)
    {
        if(matrice[i+1][col] > max)
        {
            k++;
            max = matrice[i+1][col];
        }
        i++;
    }
    return k;
}

int checkaltrev(int col, int matrice[4][4])
{
    int i = 3;
    int k = 1;
    int max = matrice[3][col];
    while (i > 0)
    {
        if(matrice[i-1][col] > max)
        {
            k++;
            max = matrice[i-1][col];
        }
        i--;
    }
    return k;
}

int checkleft(int row, int matrice[4][4])
{
    int j = 0;
    int k = 1;
    int max = matrice[row][0];
    while (j < 3)
    {
        if(matrice[row][j+1] > max)
        {
            k++;
            max = matrice[row][j+1];
        }
        j++;
    }
    return k;
}

int checkright(int row, int matrice[4][4])
{
    int j = 3;
    int k = 1;
    int max = matrice[row][3];
    while (j > 0)
    {
        if(matrice[row][j-1] > max)
        {
            k++;
            max = matrice[row][j-1];
        }
        j--;
    }
    return k;
}

int controllocerca(int matrice[4][4], int cerca[16])		// separa controllo righe e colonne
{
	int i = 0;
	
	while (i < 4)
	{
		if (checkalt(i, matrice) != cerca[i])		//controlla alt da alto 
			return 0;
		i++;
	}
	
	i = 0;
	while (i < 4)
	{
		if (checkaltrev(i, matrice) != cerca[i + 4])		//controlla basso a alto 
			return 0;
		i++;
	}
	
	i = 0;
	while (i < 4)
	{
		if (checkleft(i, matrice) != cerca[i + 8])		//controlla sx a dx 
			return 0;
		i++;
	}
	
	i = 0;
	while (i < 4)
	{
		if (checkright(i, matrice) != cerca[i + 12])		//controlla dx a sx 
			return 0;
		i++;
	}
	
	return 1;		//tutto a posto
}


int riempicolonna(int riga, int col, int matrice[4][4], int *cerca)
{
    int ktop;
    int kbot;
    
    if (riga == 4)
    {
        ktop = checkalt(col, matrice);
        kbot = checkaltrev(col, matrice);
        if (ktop == cerca[col] && kbot == cerca[col+4])
            return 1;
        return 0;
    }
    
    if (matrice[riga][col] != 0)
        return riempicolonna(riga+1, col, matrice, cerca);
    
    int n = 1;
    while(n <= 4)
    {
        if (checkrighe(n, matrice[riga]) == 0 && checkcol(n, col, matrice) == 0)
        {
            matrice[riga][col] = n;
            
            if (riempicolonna(riga+1, col, matrice, cerca))
                return 1;
            
            matrice[riga][col] = 0;
        }
        n++;
    }
    return 0;
}

int back(int *cerca, int matrice[4][4], int j)
{
    int i;
    int backup[4];
    
    if (j == 4)
        return controllocerca(matrice, cerca);
    
    i = 0;
    while(i < 4)
    {
        backup[i] = matrice[i][j];
        i++;
    }
    
    while(1)
    {
        if (riempicolonna(0, j, matrice, cerca))
        {
            if (back(cerca, matrice, j+1))
                return 1;
        }
        else
        {
            break;
        }
        
        i = 3;
        while(i >= 0)
        {
            if (matrice[i][j] < 4)
            {
                int vecchio = matrice[i][j];
                matrice[i][j] = 0;
                
                int k = i;
                while(k < 4)
                {
                    matrice[k][j] = 0;
                    k++;
                }
                
                int n = vecchio + 1;
                int trovato = 0;
                while(n <= 4)
                {
                    if (checkrighe(n, matrice[i]) == 0 && checkcol(n, j, matrice) == 0)
                    {
                        matrice[i][j] = n;
                        trovato = 1;
                        break;
                    }
                    n++;
                }
                
                if (trovato)
                    break;
            }
            i--;
        }
        
        if (i < 0)
            break;
    }
    
    i = 0;
    while(i < 4)
    {
        matrice[i][j] = backup[i];
        i++;
    }
    
    return 0;
}

int main(void)
{
    int i = -1;
    int j;
    int matricey[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
    int cerca[16] = {4,3,2,1,1,2,2,2,4,3,2,1,1,2,2,2};
    //int cerca[16] = {2,1,2,4,2,4,2,1,2,3,1,2,3,2,2,1};
    
    printf("Risoluzione puzzle...\n\n");
    
    if(back(cerca, matricey, 0))
    {
        printf("Soluzione trovata:\n");
        while (++i < 4)
        {
            j = -1;
            while(++j < 4)
                printf("%d ", matricey[i][j]);
            printf("\n");
        }
    }
    else
    {
        printf("Nessuna soluzione trovata!\n");
    }
    
    return 0;
}

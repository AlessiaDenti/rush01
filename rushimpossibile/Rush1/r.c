/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenti <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 14:54:56 by adenti            #+#    #+#             */
/*   Updated: 2025/10/25 14:54:57 by adenti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_strlen()

int *ft_strcheck(char *str){
	int *numeri;
	while (*str)
	{
		if(*str == " ")
			str++;
		else if(*str >= '1' && *str <= '4')
		{
			*numeri = *str;
			numeri++;
			str++;
		}
		else
			return (0);
	}
	return (numeri);
}


int main(int argc, char **argv)
{
	
	if (argc == 2)
	{	
		int *l;
		l = ft_strcheck(argv[1]);
		if (*l !='\0' && ft_strlen(l) == 16)
		{
			// riempire tabella argv[1]
		}
	}
	else
		write(1, "Error", 5);
	return (0);
}

// nella lista solo numeri compresi tra 1 e 4
// lettere o altro deve tornare errore 48<= o >=53 sono i caratteri che non vanno bene 
// spazi e tab vanno bene 


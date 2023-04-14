#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char	*set_spliter(char *str, char c)
{
	char	*s;
	int		i;

	if (!str)
		return (NULL);
	s = malloc(strlen(str) + 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			while (str[i])
			{
				s[i] = str[i];
				i++;
				printf("+___%d\n", i);
				if (str[i] == 39)
					break ;
			}
			// skip_and_fill_in_quotes(str, &s, 39, &i);
			
		}
		else if (str[i] == 34)
		{
			while (str[i])
			{
				s[i] = str[i];
				i++;
				printf("-___%d\n", i);
				if (str[i] == 34)
                {
                    s[i] = str[i];
				    i++;    
					break ;
                }
			}
			// skip_and_fill_in_quotes(str, &s, 34, &i);
		}
		else if (str[i] == c)
		{
			printf("c___%d\n", i);
			s[i] = -1;
		    i++;
		}
		else
		{
			printf("else___%d\n", i);
			s[i] = str[i];
		    i++;
		}
	}
	s[i] = 0;
	printf("----%s----\n",s);
	return (s);
}
int main(int argc, char const *argv[])
{
    printf("%s\n", set_spliter("ab cd \" \" ef", '|'));
    printf("%s\n", set_spliter("ab cd \" \" ef", ' '));
    return 0;
}

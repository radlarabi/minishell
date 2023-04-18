#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
#include <signal.h>
 #include <fcntl.h>

void	ft_putchar_fd(char c, int fd)
{
	if (write(fd, &c, 1) == -1)
	{
		perror("write");
		exit(0);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			ft_putchar_fd(s[i], fd);
			i++;
		}
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (strlen(s) < start)
		return (strdup(""));
	if (len > strlen(s) - start)
		len = strlen(s) - start;
	ret = (char *)malloc(len * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	while (s[i] && i < len)
	{
		ret[i] = s[start++];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
static int	count_words(char *str, char c)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = 1;
	i = 0;
	while (str && str[i])
	{
		if (str[i] != c && j)
		{
			count++;
			j = 0;
		}
		if (str[i] == c)
			j = 1;
		i++;
	}
	return (count);
}

static int	count_set(const char *str, char set, int i)
{
	while (str[i] && str[i] == set)
		i++;
	return (i);
}

static int	count_non_set(const char *str, char set, int i)
{
	while (str[i] && str[i] != set)
		i++;
	return (i);
}

static int	free_str(char **ret, int d)
{
	int	i;

	i = 0;
	if (!ret[d])
	{
		while (ret[i])
		{
			free(ret[i]);
			i++;
		}
		free(ret);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *str, char set)
{
	int		j;
	int		i;
	int		len;
	char	**ret;
	int		start;

	j = 0;
	i = 0;
	len = count_words((char *)str, set);
	ret = (char **)malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	while (str && str[i])
	{
		start = count_set(str, set, i);
		i = count_non_set(str, set, start);
		if (len > j)
		{
			ret[j] = ft_substr(str, start, i - start);
			if (!free_str(ret, j++))
				return (NULL);
		}
	}
	ret[j] = NULL;
	return (ret);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a_len;
	int		b_len;
	int		i;
	char	*ret;

	if (!s2)
		return (NULL);
	if (!s1)
		return strdup(s2);
	a_len = strlen((char *)s1);
	b_len = strlen((char *)s2);
	i = -1;
	ret = (char *)malloc(sizeof(char) * (a_len + b_len + 1));
	if (!ret)
		return (0);
	while (s1[++i])
		ret[i] = s1[i];
	i = -1;
	while (s2[++i])
		ret[a_len + i] = s2[i];
	ret[a_len + i] = '\0';
	// free((char *)s1);
	return (ret);
}
int	fill_content_heredoc(char *stop, int fd)
{
	char *str = NULL;
	char *content = NULL;
	while (1)
	{
		str = readline(">");
		content = NULL;
		if (!strcmp(str, stop))
		{
			close(fd);
			break ;
		}
		content = ft_strjoin(content, str);
		content = ft_strjoin(content, "\n");
		write(fd, content, strlen(content));
		free(content);
		free(str);
	}
	return (0);
}
int	files_here_doc(char *stop)
{
	int		status;
	pid_t	pid;
	int infile = 0;
	int 	fd;

	// if (pipe(fd) < 0)
	// {
	// 	perror("pipe");
	// 	return -1;
	// }
	fd = open("test", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		perror("open");
	pid = fork();
	if (pid == 0)
	{
		fill_content_heredoc(stop, fd);
		exit(0);
	}
	write(fd, "content", 7);
	printf("---> %d\n", fd);
	waitpid(pid, &status, 0);
	return (fd);
}
void	ft_cat(int fd)
{
	pid_t pid;
	int		status;
	char **str = ft_split("cat -e", ' ');
	pid = fork();
	if (pid == 0)
	{
		// close(fd);
		// fd = open("jjjjjjjj", O_CREAT | O_RDWR | O_TRUNC, 0644);
		// close(fd);
		// write(fd, "content", 7);
		// printf("====%d====\n", fd);
		// printf("pip %d====\n", fd);
		// close(fd);
		close(fd);
		fd = open("test", O_RDONLY );
		printf("*****%d\n", fd);
		// ft_putstr_fd("fdsfdsf-------->fdsfsdjfhsdfjfdshfsdfjsdhfsdgdfhsd\n",fd);
		// printf("--%d--> %d^^\n", fd, write(fd, "000000000000000000000", 21));
		dup2(fd, 0);
		close(fd);
		execve("/bin/cat", str, NULL);
		perror("execve");
	}

	waitpid(pid, &status, 0);
	unlink("test");
	printf("********\n");
}
int main(int argc, char const *argv[])
{
	int fd = files_here_doc("pp");
	printf("!!!!!!\n");
	ft_cat(fd);
    // while(1);
	return 0;
}

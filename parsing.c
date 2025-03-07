#include "philosophers.h"

static int	is_all_space(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13)))
		i++;
	return (!s[i]);
}

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int ft_check_arg(char **str)
{
	int		i;
	char	**ar;

	i = 0;
	ar = ft_split(*str, ' ');
	if (!ar)
		return (NULL);
	while (ar[i])
	{
		if (!ft_isnum(ar[i]) && !ft_check_num(ft_atoi(ar[i])))
            return (0);
		else
            return (1);
		i++;
	}
	return (0);
}

char    *ft_check_join(char **av)
{
	int		i;
	char	*temp;
    char    *str;

	i = 1;
    str = NULL;
	while (av[i])
	{
		if (is_all_space(av[i]))
		{
			write(2, "Error\n", 6);
			free(str);
			exit(1);
		}
		temp = ft_strjoin(str, av[i]);
		free(str);
		str = temp;
		temp = ft_strjoin(str, " ");
		free(str);
		str = temp;
		i++;
	}
	return (str);
}
int parsing(char **str)
{
    ft_check_join(str);
    if (ft_check_arg(str))
        return (1);
    return (0);
}
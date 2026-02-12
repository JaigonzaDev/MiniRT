

int main (int ac, char **av)
{
    if (ac != 2)
    {
        ft_printf("Error: Num arguments");
        return (1);
    }
    else
    {
        parse_properties(av);
        return (0);
    }
}
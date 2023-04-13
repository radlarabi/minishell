int main(int argc, char const *argv[])
{
    char *a = malloc(5);
    a = "ppp";
    free(a);
    a = "aaa";
    printf("%s\n", a);
    return 0;
}

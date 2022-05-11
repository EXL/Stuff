test(a1, a2, a3, a4, a5)
char *a5;
{
    printf("%d %d %d %d %s\n", a1, a2, a3, a4, a5);
}

main(argc, argv)
char **argv;
{
    test(1, 2, 3, 4, "s");
}

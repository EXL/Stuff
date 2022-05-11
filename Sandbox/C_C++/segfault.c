int* a();

int main() {
    int* x = a();
    int b = *x;
    printf("%d\n",b);
}

int* a() {
    int x= 25;
    return &x;
}

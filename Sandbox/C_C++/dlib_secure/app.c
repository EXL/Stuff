// $ gcc app.c -o app -L. -lA
// $ LD_PRELOAD="./libB.so ./libD.so" LD_LIBRARY_PATH=. ./app

extern void something();

int main() {
    something();
    return 0;
}

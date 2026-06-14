// zcc +Zux -startup=5 -v -o testputsk.bin testputsk.c printk.c
// z88dk-dis -o 0 -x testputsk.map testputsk.bin > testputsk.bin.asm

void putsk(unsigned char *s);

int main(){
    putsk((unsigned char*)"Hello World\n");
}
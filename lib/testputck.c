// zcc +Zux -startup=5 -v -o testputck.bin testputck.c printk.c
// z88dk-dis -o 0 -x testputck.map testputck.bin > testputck.bin.asm

void printk(char *s, ...);

int main(){
    printk("Hello %s\n", "World");
}
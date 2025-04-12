/* This program takes the previously compiled and linked pieces of the
* operating system, and puts them together to build an image file:
*
*      kernel:         the operating system kernel
*      mm:             the memory manager
*      fs:             the file system
*      init:           the system initializer
*
*   z88dk-dis -x 0 image-Zux-1.0.bin > image-Zux-1.0.bin.asm
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define PROGRAMS 4              /* kernel + mm + fs + init = 4 */
#define SECTOR_SIZE 512         /* size of buf */
#define READ_UNIT 512           /* how big a chunk to read in */
#define KERNEL_D_MAGIC 0x526F   /* identifies kernel data space */

FILE *image;                    /* file descriptor used for output file */

struct sizes {
    long text_size;           /* size in bytes */
//    unsigned data_size;           /* size in bytes */
//    unsigned bss_size;            /* size in bytes */
//    int sep_id;                   /* 1 if separate, 0 if not */
} sizes[PROGRAMS];

long cum_size;                  /* Size of kernel+mm+fs+init */
long orgin;                     /* Origin of each part */

char *name[] = {"kernel\t", "mm\t", "fs\t", "init\t"};

void create_image(char *f);
void open_image(char *f);
void copy2(int num, char *file_name);
void patch(void);
void read_block(int blk, char *buff);
void write_block(int blk, char *buff);
unsigned short get_byte();
void put_byte(long offset, long data);
void pexit(char *s1, char *s2);
//void debug(char *message, char *p);

void main(int argc, char *argv[])
{
    /* Copy the 4 programs to the output. */

    int i;

    //debug("argc:%d\n",argc, 0);

    if (argc != PROGRAMS+2) // +1: argv[0]; +1: image
        pexit("five file names expected.", "");

    create_image(argv[PROGRAMS+1]); /* create the output file */

    /*for (i = 0; i < PROGRAMS+2; i++) {
        debug("argv[%d]:%s\n", i, (void*)argv[i]);
    }*/
    /* Copy the 5 programs to the output file or diskette. */
    for (i = 0; i < PROGRAMS; i++)
        copy2(i, argv[i+1]);

    printf("                                                -----           -----\n");
    printf("Operating system image size   %29ld     %5lx\n", cum_size, cum_size);

    open_image(argv[PROGRAMS+1]);

    patch();
    exit(0);
}

void create_image(char *f)
{
    //debug("Creating image %s\n", f);
    printf("Creating image %s\n", f);

    /* Create the output file. */
    if ( (image = fopen(f, "wb")) == NULL)
        pexit("can't open image\n", "");
}

void open_image(char *f)
{
    //debug("Creating image %s\n", f);
    printf("Opening image %s\n", f);

    /* Reopen the output file. */
    if ( (image = fopen(f, "rb+")) == NULL)
        pexit("can't reopen image\n", "");
}

/*void read_block(int blk, char *buff) // SECTOR_SIZE
{
    fseek(image, (long)SECTOR_SIZE * (long) blk, SEEK_SET);
    if (fread(buff, 1, SECTOR_SIZE, image) != SECTOR_SIZE)
        pexit("block read error", "");
}

void write_block(int blk, char *buff) // SECTOR_SIZE
{
    fseek(image, (long)SECTOR_SIZE * (long) blk, SEEK_SET );
    if (fwrite(buff, 1, SECTOR_SIZE, image) != SECTOR_SIZE)
        pexit("block write error", "");
}*/

/* which program is this (0 - PROGRAMS-1) */
/* file to open */
void copy2(int num, char *file_name)
{
    FILE *fd;
    struct stat st;
    size_t bytes_read, count;
    size_t left_to_read, tot_bytes;
    char inbuf[READ_UNIT];

        //debug("Opening file %s\n", file_name);
        printf("Opening file %s\n", file_name);

        if ( (fd = fopen(file_name, "rb")) == NULL)
            pexit("can't open ", file_name);

        /* Read the status to see how big the file is. */
        stat(file_name, &st);

        tot_bytes = cum_size + st.st_size;

        printf("%s\torg=%5u\tlen=%5u\ttot=%6u\thex=%5X\n",
                    name[num], cum_size, st.st_size, tot_bytes, tot_bytes);

        cum_size = (long)tot_bytes;

        /* Record the size information in the table. */
        if ( num > 0) // skip kernel
            sizes[num].text_size = cum_size;

    /* Read in the text, and copy them to output. */
    left_to_read = st.st_size;
    while (left_to_read > 0) {
        count = (left_to_read < READ_UNIT ? left_to_read : READ_UNIT);
        bytes_read = fread(inbuf, 1, READ_UNIT, fd);
        if (bytes_read < 1) pexit("read error on file ", file_name);
        if (bytes_read > 0)
            fwrite(inbuf, bytes_read, 1, image);
        left_to_read -= count;
        putchar('.');
    }
    putchar('\n');

    fclose(fd);
}

void patch(void)
{
    unsigned short i ;

        i = get_byte();
        if ( i != KERNEL_D_MAGIC )
            pexit("kernel data space: no magic number","");

        put_byte(0x40L, sizes[1].text_size);
        put_byte(0x44L, sizes[2].text_size);
        put_byte(0x48L, sizes[3].text_size);
}

unsigned short get_byte()
{
    int status;
    size_t count;
    unsigned short inbuf[READ_UNIT];

        if ( (status = fseek(image, 0x40L, SEEK_SET)) != 0 )
            pexit("seeking error on image file\n", "");
        if ( (count = fread(inbuf, sizeof(unsigned short), 1, image)) != 1)
            pexit("read error on seeked image file\n", "");

        return inbuf[0];
}

void put_byte(long offset, long data)
{
    int status;
    size_t count;

        if ( fseek(image, offset, SEEK_SET) != 0 )
            pexit("reseeking error on image file\n", "");
        if ( fwrite(&data, sizeof(long), 1, image) != 1 )
            pexit("put error on image file\n", "");
}

void pexit(char *s1, char *s2)
{
    printf("Build: %s%s\n", s1, s2);
    exit(1);
}

void debug(char *message, char *p) {
    printf(message, p);
}
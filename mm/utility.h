#ifndef UTILITY_H
#define UTILITY_H

int mem_copy(int src_proc, int src_seg, long src_vir, int dst_proc, int dst_seg, long dst_vir, long bytes);
int tell_fs(int what, int p1, int p2, int p3);
int allowed(char *name_buf, struct stat *s_buf, int mask);
static int read_header(int fd, int *ft, vir_bytes *text_bytes, vir_bytes *data_bytes, vir_bytes *bss_bytes, phys_bytes *tot_bytes, vir_clicks sc);
static int new_mem(vir_bytes text_bytes, vir_bytes data_bytes, vir_bytes bss_bytes, vir_bytes stk_bytes, phys_bytes tot_bytes, char bf[], int zs);
static void patch_ptr(char stack[], vir_bytes base);
static void load_seg(int fd, int seg, vir_bytes seg_bytes);

void panic(char *s, int n);

void  sys_exec(int proc, char *ptr);

#endif //UTILITY_H

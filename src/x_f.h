/*
 * x_f.h
 *
 *  Created on: Dec 4, 2013
 *      Author: reboot
 */

#ifndef X_F_H_
#define X_F_H_

#include <fp_types.h>

#include <time.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define CRC_FILE_READ_BUFFER_SIZE       64512

#ifdef HAVE_ST_BIRTHTIME
#define birthtime(x) x->st_birthtime
#else
#define birthtime(x) x->st_ctime
#endif

#define F_FC_MSET_SRC                   (a32 << 1)
#define F_FC_MSET_DEST                  (a32 << 2)

#define UPDC32(octet,crc) (crc_32_tab[((crc) ^ ((uint8_t)octet)) & 0xff] ^ ((crc) >> 8))

typedef struct gu_nfo
{
  uint32_t id;
  char name[64];
} gu_n, *p_gu_n;

#define PGF_MAX_LINE_SIZE       8192
#define PGF_MAX_LINE_PROC       134217728

off_t
get_file_size(char *file);
time_t
get_file_creation_time(struct stat *);
off_t
file_crc32(char *file, uint32_t *crc_out);

_d_achar_i self_get_path, file_exists, get_file_type, dir_exists, check_path;

int
find_absolute_path(char *exec, char *output);

ssize_t
file_copy(char *source, char *dest, char *mode, uint32_t flags);
off_t
read_file(char *file, void *buffer, size_t read_max, off_t offset, FILE *_fp);
int
write_file_text(char *data, char *file);
size_t
exec_and_redirect_output(char *command, FILE *output);
off_t
enum_readline(char *file, void *buffer, size_t read_max, off_t max_l, FILE *_fp,
    int
    (*call_b)(char *b, void *a), void *arg);

typedef int
_pf_eof(void *p);

_pf_eof gz_feof, g_feof;

int
load_guid_info(pmda md, char *path);
p_gu_n
search_xuid_id(pmda md, uint32_t id);
p_gu_n
search_xuid_name(pmda md, char *name);

#ifdef HAVE_ZLIB_H
int
g_is_file_compressed(char *file);
#endif

int
r_preload_guid_data(pmda md, char *path);

#endif /* X_F_H_ */

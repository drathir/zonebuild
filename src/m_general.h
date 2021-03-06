/*
 * m_general.h
 *
 *  Created on: Dec 4, 2013
 *      Author: reboot
 */

#ifndef M_GENERAL_H_
#define M_GENERAL_H_

#include "m_comp.h"
#include "fp_types.h"
#include <stdio.h>

#define G_MATCH         ((int)0)
#define G_NOMATCH       ((int)1)

#define F_GM_ISREGEX                    ((uint32_t)1 << 1)
#define F_GM_ISMATCH                    ((uint32_t)1 << 2)
#define F_GM_ISLOM                      ((uint32_t)1 << 3)
#define F_GM_IMATCH                     ((uint32_t)1 << 4)
#define F_GM_NAND                       ((uint32_t)1 << 5)
#define F_GM_NOR                        ((uint32_t)1 << 6)
#define F_GM_ISACCU                     ((uint32_t)1 << 7)
#define F_GM_TFD                        ((uint32_t)1 << 8)
#define F_GM_ISFNAME                    ((uint32_t)1 << 9)
#define F_GM_LOM_SET                    ((uint32_t)1 << 10)
#define F_GM_IS_MOBJ                    ((uint32_t)1 << 11)

#define F_GM_TYPES                      (F_GM_ISREGEX|F_GM_ISMATCH|F_GM_ISLOM|F_GM_ISFNAME)
#define F_GM_TYPES_STR                  (F_GM_ISREGEX|F_GM_ISMATCH|F_GM_ISFNAME)

#define F_GH_IFRES                      ((uint64_t)1 << 30)
#define F_GH_IFHIT                      ((uint64_t)1 << 31)
#define F_GH_HASMATCHES                 ((uint64_t)1 << 25)
#define F_GH_HASMAXRES                  ((uint64_t)1 << 28)
#define F_GH_HASMAXHIT                  ((uint64_t)1 << 29)
#define F_GH_APFILT                     ((uint64_t)1 << 27)
#define F_GH_TFD_PROCED                 ((uint64_t)1 << 55)
#define F_GH_SPEC_SQ01                  ((uint64_t)1 << 56)



#define F_GH_ISMP                       (F_GH_HASMATCHES|F_GH_HASMAXRES|F_GH_HASMAXHIT)

#define GM_MAX                          16384

typedef float
(*g_tf_p)(void *base, size_t offset);
typedef uint64_t
(*g_t_p)(void *base, size_t offset);
typedef int64_t
(*g_ts_p)(void *base, size_t offset);
typedef int
(*g_op)(int s, int d);
void
g_ipcbm(void *hdl, pmda md, int *r_p, void *ptr);
int
g_filter(__g_handle hdl, pmda md);
int
g_bmatch(void *, __g_handle, pmda md);
int
g_bmatch_dummy(void *d_ptr, __g_handle hdl, pmda md);

typedef int
(*pt_g_bmatch)(void *, __g_handle, pmda md);

int
opt_g_operator_or(void *arg, int m, void *opt);
int
opt_g_operator_and(void *arg, int m, void *opt);

int
opt_g_m_raise_level(void *arg, int m, void *opt);
int
opt_g_m_lower_level(void *arg, int m, void *opt);

int
opt_g_lookup(void *arg, int m, void *opt);

typedef struct ___g_lom
{
  int result;
  /* --- */
  uint32_t flags;
  g_t_p g_t_ptr_left;
  g_ts_p g_ts_ptr_left;
  g_t_p g_t_ptr_right;
  g_ts_p g_ts_ptr_right;
  g_tf_p g_tf_ptr_left;
  g_tf_p g_tf_ptr_right;
  int
  (*g_icomp_ptr)(uint64_t s, uint64_t d);
  int
  (*g_iscomp_ptr)(int64_t s, int64_t d);
  int
  (*g_fcomp_ptr)(float s, float d);
  int
  (*g_lom_vp)(void *d_ptr, void * lom);
  g_op g_oper_ptr;

  void *left, *right;
  uint64_t t_left, t_right;
  int64_t ts_left, ts_right;
  float tf_left, tf_right;
  /* --- */
  size_t t_l_off, t_r_off;
  void *p_glob_stor;
  mda math_l;
  mda math_r;
  mda chains;
  int vb_l, vb_r;
} _g_lom, *__g_lom;

typedef struct ___g_match_h
{
  uint32_t flags;
  char *match, *field;
  int match_i_m, regex_flags, fname_flags;
  regex_t preg;
  mda lom;
  g_op g_oper_ptr;
  __g_proc_v pmstr_cb;
  _d_drt_h dtr;
  char *data;
  void *hdl_ref;
  pmda next;
} _g_match, *__g_match;

mda _match_rr;
pmda _match_clvl;

typedef struct ___last_match
{
  uint32_t flags;
  void *ptr;
} _l_match, *__l_match;

__g_match
g_global_register_match(void);
int
do_string_match(__g_handle hdl, void *d_ptr, __g_match _gm);

_l_match _match_rr_l;

#define MAX_RT_C_EXEC           4096

typedef struct ___rt_conditional
{
  _g_match match;
  __g_proc_v p_exec;
} _rt_c, *__rt_c;

#endif /* M_GENERAL_H_ */

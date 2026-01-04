#ifndef __MATRIX_H
#define __MATRIX_H

// 20 Bytes

typedef struct {
  short m[3][3]; /* 3x3 rotation matrix */
  short _pad;    /* padding */
} SHORTMATRIX;

#endif // !__MATRIX_H

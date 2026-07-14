#ifndef __IMAGES_H
#define __IMAGES_H

/// @brief Blends two colors together
/// @param pColor1 The first color
/// @param pColor2 The second color
/// @param pAmount The amount to blend the colors (0-4096)
/// @return The blended color
int ColorLerp(int pColor1, int pColor2, int pAmount);

void func_80017F24(void *in, void *out, int valueOffset);

/// @brief Converts the given BGR555 buffer to grey scale
/// @param buf The buffer to convert, also the output buffer
/// @param size The size of the buffer
void func_80017E98(void *buf, int size);

#endif

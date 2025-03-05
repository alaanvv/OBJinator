#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

void rotate(float vertex[3], char axis, float angle) {
  float x = vertex[0], y = vertex[1], z = vertex[2];

  if      (axis == 'x') {
    y = vertex[1] * cos(angle) - vertex[2] * sin(angle);
    z = vertex[1] * sin(angle) + vertex[2] * cos(angle);
  }
  else if (axis == 'y') {
    x = vertex[0] * cos(angle) - vertex[2] * sin(angle);
    z = vertex[0] * sin(angle) + vertex[2] * cos(angle);
  }
  else if (axis == 'z') {
    x = vertex[0] * cos(angle) - vertex[1] * sin(angle);
    y = vertex[0] * sin(angle) + vertex[1] * cos(angle);
  }

  vertex[0] = x;
  vertex[1] = y;
  vertex[2] = z;
}

void scale(float vertex[3], char axis, float factor) {
  if (axis == 'x' || axis == 'a') vertex[0] *= factor;
  if (axis == 'y' || axis == 'a') vertex[1] *= factor;
  if (axis == 'z' || axis == 'a') vertex[2] *= factor;
}

void move(float vertex[3], char axis, float amount) {
  if (axis == 'x' || axis == 'a') vertex[0] += amount;
  if (axis == 'y' || axis == 'a') vertex[1] += amount;
  if (axis == 'z' || axis == 'a') vertex[2] += amount;
}

int main(int argc, char** argv) {
  char* in_path = argv[1];
  char* op      = argv[2];
  char* _num    = argv[3];

  char out_path[32];
  sprintf(out_path, "%s_", in_path);

  FILE* in  = fopen(in_path,  "r");
  FILE* out = fopen(out_path, "w");

  float vertex[3];
  char  buffer[256];
  char  type[32];
  float num = atof(_num);

  while (fgets(buffer, 256, in)) {
    sscanf(buffer, "%s %f %f %f", type, &vertex[0], &vertex[1], &vertex[2]);
    if (strcmp(type, "v")) { fprintf(out, "%s", buffer); continue; }

    if      (op[0] == 'r') rotate(vertex, op[1], num);
    else if (op[0] == 's') scale(vertex, op[1], num);
    else if (op[0] == 'm') move(vertex, op[1], num);

    fprintf(out, "v % f % f % f\n", vertex[0], vertex[1], vertex[2]);
  }

  fclose(in);
  fclose(out);
  return 0;
}

#ifndef COMMON_H
#define COMMON_H

enum Colors { Black, White };

typedef unsigned int u_int;

int abs(int x) {
	if (x=>0) return x;
	return -x;
}

#endif
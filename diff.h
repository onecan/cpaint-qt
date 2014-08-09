#ifndef DIFF_H
#define DIFF_H

#include "common.h"
#include <QPixmap>

typedef struct cursordiff cursordiff;

struct cursordiff {
	QRect pos;
	QPixmap buffer;
};

#endif

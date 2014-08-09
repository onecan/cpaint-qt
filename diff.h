#ifndef DIFF_H
#define DIFF_H

#include "common.h"
#include <QPoint>
#include <QPointF>
#include <QPixmap>

typedef struct diff diff;
typedef struct cursordiff cursordiff;

struct diff {
	QPointF pos;
	QPixmap buffer;
};

struct cursordiff {
	QRect pos;
	QPixmap buffer;
};

#endif

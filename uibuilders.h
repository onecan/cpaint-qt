#ifndef UIBUILDERS_H
#define UIBUILDERS_H

#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTabWidget>

#include "inputedit.h"
#include "layouts.h"
#include "graphcontroller.cpp"

void ui_functionControls(QTabWidget *t, QPushButton *apply, QPushButton *cancel, QComboBox *mode, GraphController *g);
void ui_functionControls_cancel(QPushButton *cancel, GraphController *g);
void ui_functionControls_mode(QComboBox *mode);
void ui_functionControls_presets(QComboBox *presets);
void ui_functionControls_subfuncs(QListWidget *l);

#endif

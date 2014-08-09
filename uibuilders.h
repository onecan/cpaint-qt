#ifndef UIBUILDERS_H
#define UIDBUILDERS_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QListWidget>
#include <QListWidgetItem>
#include <QTabWidget>

#include "inputedit.h"
#include "layouts.h"

void ui_functionControls_presets(QComboBox *presets);
void ui_functionControls_subfuncs(QListWidget *l);
void ui_functionControls(QTabWidget *t, QPushButton *apply, QPushButton *cancel, QComboBox *mode);

#endif

#ifndef INPUTEDIT_H
#define INPUTEDIT_H

#include <QLineEdit>

class InputEdit : public QLineEdit {
	Q_OBJECT

public:
	InputEdit(QWidget *parent = 0);
	~InputEdit();

protected:
	void changeEvent(QEvent *ev);

public slots:
	void s_cancel();
	void s_apply();
private:
	QString buffer;

};
#endif

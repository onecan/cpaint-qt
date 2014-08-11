#ifndef APPLYFUNCTIONSETTINGS_H
#define APPLYFUNCTIONSETTINGS_H

#include <QPushButton>
#include <QString>

class ApplyFunctionSettings: public QPushButton {
public:
	ApplyFunctionSettings(QWidget *parent = 0);
	~ApplyFunctionSettings();

private: 
	bool somethingChanged;
	static const QString defaultStyle;
	static const QString alteredStyle;

protected:
	void mousePressEvent(QMouseEvent *ev);
	
public slots:
	void s_functionAltered(QString &text);
};
#endif

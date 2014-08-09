/*
 * Proxy between Qt and Parser data types
 * Handles iteration
 */

#ifndef CALCULATOR_H
#define CALCULATOR_H


#define ITR_VAR	"Z"
#include "parser.h"
#include <QPointF>

using std::string;
class Calculator {
	parser::Tree *t;

	QPointF cxToQpf(cx a);
	cx qpfToCx(QPointF p);
	QPointF cxToQpf(cx *a);
	cx qpfToCx(QPointF *p);

public:
	Calculator();
	Calculator(string func);
	~Calculator();
	void setFunc(string f);
	void setVar(string var, string a);
	void setVar(string var, QPointF p);
	QPointF evalVar(string var);
	QPointF eval(QPointF seed);
	string toString();
	void applyPreset(int preset);
	string getFct();
	string getVarFct(string var);
	void iterate(QPointF seed, int numTimes, std::vector<QPointF> *output);
	
};
#endif

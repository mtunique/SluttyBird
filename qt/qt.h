#ifndef QT_H
#define QT_H

#include <QtWidgets/QtWidgets>
#include "ui_qt.h"
#include <Box2D.h>

class QPainter;
class QLabel;

class qt : public QMainWindow
{
	Q_OBJECT

public:
	qt(QWidget *parent = 0);
	~qt();
	QPainter *painter;

private:
	Ui::qtClass ui;
	QLabel *cir;

protected:
    void paintEvent(QPaintEvent *);
	//void timerEvent(QTimerEvent *Event);
	//void showEvent(QShowEvent *Event);
	//void hideEvent(QShowEvent *Event);
	void keyPressEvent(QKeyEvent * event);

private slots:
	void box2();

public:	
	void initBox2D();
	QTimer *timer;
	void setCirUp(int);	
	void build();


};

#endif // QT_H
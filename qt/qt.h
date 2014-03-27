#ifndef QT_H
#define QT_H

#include <QtWidgets/QtWidgets>
#include "ui_qt.h"
#include <Box2D.h>
#include <string>

class QPainter;
class QLabel;
class MyLabel;
class MyContact;

class qt : public QMainWindow
{
	Q_OBJECT

public:
	qt(QWidget *parent = 0);
	~qt();
	QPainter *painter;
	float CH;

private:
	Ui::qtClass ui;
	QLabel *cir;
	QLabel *background;
	MyLabel *startButton;

protected:
    void paintEvent(QPaintEvent *);
	//void timerEvent(QTimerEvent *Event);
	//void showEvent(QShowEvent *Event);
	//void hideEvent(QShowEvent *Event);
	void keyPressEvent(QKeyEvent * event);

private slots:
	void box2();
	void startButtonClick();

public:	
	void initBox2D();
	QTimer *timer;
	void setCirUp();	
	void setCirDown();	
	void setCirLeft();	
	void setCirRight();	
	void build();
	void start();
	void end();
	void startTime();
	void load();
	void replay();
	std::string fileName;
	MyContact *listener;
	int started, loaded,success;
	QMovie *movie;
	QPixmap backgroundpic;
};




#endif // QT_H
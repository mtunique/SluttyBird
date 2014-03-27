#ifndef MYLABEL_H
#define MYLABEL_H
#include <qlabel.h>
class MyLabel: public QLabel 
{
 Q_OBJECT 
public: 
	MyLabel(QWidget * parent = 0); 
	private: 
protected: 
	virtual void mouseReleaseEvent(QMouseEvent * ev); 
signals: 
	void clicked(void); 
}; 
#endif MYLABEL_H
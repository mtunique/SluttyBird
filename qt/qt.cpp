#include "qt.h"
#include <QPainter>
#include <fstream>
#include <iostream>
#include <string>
#include <qtimer>
#include <Box2D.h>
#include <bug.h>
#include <qlabel.h>
#include <fstream>
#include <qevent.h>
#include <qnamespace.h>

qt::qt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setMaximumSize(800, 600);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(box2()));
	timer->start(20);

	this->initBox2D();
	cir = new QLabel(this);	
	QPixmap pic(tr("2.png"));
	cir->setPixmap(pic);
	cir->adjustSize();
}

qt::~qt()
{

}


void qt::paintEvent(QPaintEvent *event)
{
	painter = new QPainter(this);
    QPixmap pix;
    
	QPen pen; 
    pen.setColor(QColor(255, 0, 0));
    QBrush brush(QColor(0, 255, 0, 125)); 
    painter->setPen(pen); 
    painter->setBrush(brush); 
    

	using namespace std;

	fstream infile("a.txt");
	fstream outfile("out.txt");

	QPointF points[20000];
	int num=0;
	while(infile)
	{
		int x,y;
		char c1,c2,c3;
		string line;
		getline(infile, line);
		if(line[0]=='*') 
		{
			painter->drawPolygon(points, num);
			num = 0;
			continue;
			outfile<<"***"<<endl;
		}
		x = atoi(line.substr(0,line.find(" ")).c_str());
		//outfile<<x;
		y = atoi(line.substr(line.find(" ")+1).c_str());
		outfile<<y<<' ' <<x<<endl;
		points[num++] = QPointF(x,y);
		painter->drawPoint(QPointF(x,y));
		if(num == 720)
		{
			num=720;
		}
		/*++num;
		if(num>10000) break;
		int x,y;
		string line;
		getline(infile, line);
		x = atoi(line.substr(0,line.find(" ")).c_str())*2-500;
		//outfile<<x;
		y = atoi(line.substr(line.find(" ")+1).c_str())*2-500;
		points[num++] = QPointF(x,y);
		painter->drawPoint(QPointF(x,y));*/
	}

	//painter.drawPolygon(points, num);
	infile.close();
	outfile.close();	

	//QPointF p(100, 100);
	//painter->drawEllipse(p, 10, 10);
}

void qt::build()
{
using namespace std;

	fstream infile("a.txt");

	b2Vec2 vertices[20000];
	int num=0;
	while(infile)
	{
		int x,y;
		char c1,c2,c3;
		string line;
		getline(infile, line);
		if(line[0]=='*') 
		{
			
			num = 0;
			continue;

		}
		x = atoi(line.substr(0,line.find(" ")).c_str());
		//outfile<<x;
		y = atoi(line.substr(line.find(" ")+1).c_str());
		//vertices[num].Set()
	}

	infile.close();

			b2PolygonShape polyShape;
			polyShape.Set(vertices,  4);
			b2BodyDef polyDef;
			b2FixtureDef polyFixDef;
			polyFixDef.shape = &polyShape;
			polyDef.position.Set(0,20);
			b2Body *poly = world->CreateBody(&polyDef);
			poly->CreateFixture(&polyFixDef);

}

void qt::initBox2D()
{		
	b2Vec2 gravity(0.0f, -10.0f);
	world=new b2World(gravity);

	//build();

	

	
}

void qt::box2()
{
	world->Step(timeStep, velocity, position);
	//b2Vec2 pos = body->GetPosition();


	painter = new QPainter(this);
	/*
	QPointF p(-pos.x, -pos.y);
	painter->drawEllipse(p, 10, 10);
	
	update();
	*/
	//cir->setGeometry(pos.x*10,pos.y*10,50,50);
	cir->adjustSize();
}

void qt::setCirUp(int i=5)
{
	QPoint p = cir->pos();
	int x=p.x();
	int y=p.y();
	cir->setGeometry(x*100,y*100,50,50);
}

void qt::keyPressEvent(QKeyEvent *event)
{
	if(event->key() == Qt::Key_Up)
		setCirUp();
}
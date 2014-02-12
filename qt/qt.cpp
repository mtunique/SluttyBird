#include "qt.h"
#include <QPainter>
#include <fstream>
#include <iostream>
#include <string>
#include <qtimer>
#include <Box2D.h>
#include <bug.h>
#include <qlabel.h>
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

	//ÌùÄñ
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
		}
		x = atoi(line.substr(0,line.find(" ")).c_str());//get x		
		y = atoi(line.substr(line.find(" ")+1).c_str());//get y		
		points[num].setX(x);
		points[num].setY(y);
		++num;
	}

	//painter.drawPolygon(points, num);
	infile.close();
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
		string line;
		getline(infile, line);
		if(line[0]=='*') 
		{
			b2PolygonShape polyShape;
			polyShape.Set(vertices,  num);
			b2BodyDef polyDef;
			b2FixtureDef polyFixDef;
			polyFixDef.shape = &polyShape;
			polyDef.position.Set(0,0);
			b2Body *poly = world->CreateBody(&polyDef);
			poly->CreateFixture(&polyFixDef);

			num = 0;
			continue;
		}
		x = atoi(line.substr(0,line.find(" ")).c_str());
		//outfile<<x;
		y = atoi(line.substr(line.find(" ")+1).c_str());
		vertices[num].Set(x/50, -y/50);
		++num;
	}
	infile.close();
}

void qt::initBox2D()
{		
	b2Vec2 gravity(0.0f, -10.0f);
	world=new b2World(gravity);

	build();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;		
	body =world ->CreateBody(&bodyDef);
	

	b2Vec2 point[4];
			point[0].Set(0,0);
			point[1].Set(0,-1);
			point[2].Set(1,-1);
			point[3].Set(1,0);
	b2PolygonShape dynamicBox;
	dynamicBox.Set(point, 4);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 20.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	body->SetTransform( b2Vec2( 1, -5 ), 0 );	
	body->SetFixedRotation(true);
	body->SetGravityScale(2.5);

		b2BodyDef myBodyDef;
		myBodyDef.type = b2_dynamicBody;

		//shape definition
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(1, 1); //a 2x2 rectangle

		//fixture definition
		b2FixtureDef myFixtureDef;
		myFixtureDef.shape = &polygonShape;
		myFixtureDef.density = 1;



		//a static floor to drop things on
		myBodyDef.type = b2_staticBody;
		myBodyDef.position.Set(0, 0);

		b2Vec2 v1(0,0);
		b2Vec2 v2(0,-600/50);
		b2EdgeShape edge;
		edge.Set( v1, v2 );
		myFixtureDef.shape = &edge;
		world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);	
		
		v1.Set(0,-600/50);
		v2.Set(800/50,-600/50);
		edge.Set( v1, v2 );
		world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
		v1.Set(800/50,-600/50);
		v2.Set(800/50,0);
		edge.Set( v1, v2 );
		world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);
		v1.Set(0,0);
		v2.Set(800/50,0);
		edge.Set( v1, v2 );
		world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);		

	timeStep = 1.0f/60.0f;
	velocity = 6;
	position = 4;
}

void qt::box2()
{
	world->Step(timeStep, velocity, position);
	b2Vec2 pos = body->GetPosition();	
	cir->setGeometry(pos.x*50,-pos.y*50,50,50);
	cir->adjustSize();
}

void qt::setCirUp()
{
	body->ApplyLinearImpulse( b2Vec2(0,250), body->GetWorldCenter());
}
void qt::setCirRight()
{
	body->ApplyLinearImpulse( b2Vec2(30,0), body->GetWorldCenter());
}
void qt::setCirDown()
{
	body->ApplyLinearImpulse( b2Vec2(0,-200), body->GetWorldCenter());
}
void qt::setCirLeft()
{
	body->ApplyLinearImpulse( b2Vec2(-30,0), body->GetWorldCenter());
}

void qt::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_Up:
			setCirUp();
			break;
		case Qt::Key_Down:
			setCirDown();
			break;
		case Qt::Key_Left:
			setCirLeft();
			break;
		case Qt::Key_Right:
			setCirRight();
			break;

	}
}
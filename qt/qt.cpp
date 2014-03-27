#include "qt.h"
#include <qpainter>
#include <fstream>
#include <iostream>
#include <string>
#include <qtimer>
#include <Box2D.h>
#include <bug.h>
#include <qlabel.h>
#include <qevent.h>
#include <qnamespace.h>
#include <MyLabel.h>
#include <MyContact.h>
#include "DLL_SAMPLE.h"
#include <strstream>
#pragma comment(lib,"DLLTEST.lib")
//初始化窗体
qt::qt(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setMaximumSize(800, 600);
	success = 0;
	backgroundpic.load("background.png");

	fileName = "";
	
	//贴鸟	
	cir = new QLabel(this);	
	cir->setStyleSheet("border:0px;");
	movie = new QMovie("nobird.gif");
	cir->setMovie(movie);
	movie->start ();
	cir->adjustSize();
	//开始
	startButton = new MyLabel(this);
	connect(startButton, SIGNAL(clicked()),this, SLOT(startButtonClick()));


	movie = new QMovie("press-me.gif");
	startButton->setMovie(movie);
	movie->start ();		
	startButton->setGeometry(275,410,0,0);
	startButton->adjustSize();
	startButton->setStyleSheet("border:0px solid red;");

	started = 0;
	loaded = 0;
}

qt::~qt()
{

}
//开始游戏
void qt::start()
{
	loaded = 1;
	int ii=8;
	//uploadAnalyzing(ii);
	int now = imageRectAnalyzing(ii);
	cir = new QLabel(this);	
	//cir->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	cir->setStyleSheet("border:0px;");
	movie = new QMovie("bird.gif");
	cir->setMovie(movie);
	movie->start ();
	cir->show();	
	cir->setGeometry(50,250,50,50);
	cir->adjustSize();

	backgroundpic.load("backgroundstart");
	if(fileName == "D:/pointdata_A.txt")
	{
		end();
		return;
	}
	fileName = "D:/pointdata_A.txt";
	
/*
	if(fileName == "a.txt")
	{
		end();
		return;
	}
	fileName = "a.txt";*/
	this->initBox2D();		
	update();
}
//开始计时器
void qt::startTime()
{
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(box2()));
	timer->start(20);
	started = 1;
}
//结束游戏
void qt::end()
{
	movie = new QMovie("nobird.gif");
	cir->setMovie(movie);
	movie->start ();
	cir->show();	
	cir->adjustSize();
	fileName = "noa.txt";
	backgroundpic.load("backgroundend.png");	
	movie = new QMovie("replay.gif");
	startButton->setMovie(movie);
	movie->start ();		
	startButton->setGeometry(275,410,0,0);
	startButton->adjustSize();
	update();
}
//绘图
void qt::paintEvent(QPaintEvent *event)
{
	painter = new QPainter(this);
    QPixmap pix;
    
	QPen pen; 
    pen.setColor(QColor(220, 220, 220));
    QBrush brush(QColor(210, 210, 210, 125)); 
    painter->setPen(pen); 
    painter->setBrush(brush); 
    	
	painter->drawPixmap(0,0,800,600,backgroundpic);
	using namespace std;

	fstream infile(fileName);
	QPointF points[20000];
	int num=0;
	while(infile)
	{
		float x,y;
		string line;		
		if(num==4) 
		{
			painter->drawPolygon(points, num);
			getline(infile, line);
			num = 0;
			continue;
		}
		getline(infile, line);
		istringstream ss(line);
		ss>>x>>y;	
		points[num].setX(x);
		points[num].setY(y);
		++num;
	}

	//painter.drawPolygon(points, num);
	infile.close();
}
//建立矩形
void qt::build()
{
	using namespace std;

	fstream infile(fileName);

	b2Vec2 vertices[20000];
	int num=0;

	while(infile)
	{
		float x,y;
		string line;
		
		if(num==4) 
		{
			b2PolygonShape polyShape;
			polyShape.Set(vertices,  num);
			b2BodyDef polyDef;
			b2FixtureDef polyFixDef;
			polyFixDef.shape = &polyShape;
			polyDef.position.Set(0,0);
			b2Body *poly = world->CreateBody(&polyDef);
			poly->CreateFixture(&polyFixDef);
			getline(infile, line);
			num = 0;
			continue;
		}
		getline(infile, line);
		istringstream ss(line);
		ss>>x>>y;
		vertices[num].Set(x/50, -y/50);
		++num;
	}
	infile.close();
}
//建立物理引擎
void qt::initBox2D()
{		
	b2Vec2 gravity(0.0f, -10.0f);
	world=new b2World(gravity);
	listener = new MyContact();
	world->SetContactListener(listener);

	build();

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;		
	body =world ->CreateBody(&bodyDef);
	body->SetUserData(this);
	body->SetBullet(true);

	b2Vec2  point[4];
			point[0].Set(0,0);
			point[1].Set(0,-1*0.6);
			point[2].Set(1*0.8,-1*0.6);
			point[3].Set(1*0.8,0);
	b2PolygonShape dynamicBox;
	dynamicBox.Set(point, 4);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 30.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);
	body->SetTransform( b2Vec2( 1, -5 ), 0 );	
	body->SetFixedRotation(true);	
	if (body->GetGravityScale()!=2.5)
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
		endedge = world->CreateBody(&myBodyDef);
		endedge->CreateFixture(&myFixtureDef);
		v1.Set(0,0);
		v2.Set(800/50,0);
		edge.Set( v1, v2 );
		world->CreateBody(&myBodyDef)->CreateFixture(&myFixtureDef);		

	timeStep = 1.0f/60.0f;
	velocity = 6;
	position = 4;
}
//移动物体
void qt::box2()
{
	if (started)
	{
	world->Step(timeStep, velocity, position);
	b2Vec2 pos = body->GetPosition();
	if (success)
		return;
	if (pos.x>16-0.88) 
	{
		success = 1;
		return;
	}
	cir->setGeometry(pos.x*50,-pos.y*50,50,50);
	cir->adjustSize();
	}
}
//对物体加冲量
void qt::setCirUp()
{
	body->ApplyLinearImpulse( b2Vec2(0,100), body->GetWorldCenter());
}
void qt::setCirRight()
{
	body->ApplyLinearImpulse( b2Vec2(30,0), body->GetWorldCenter());
}
void qt::setCirDown()
{
	body->ApplyLinearImpulse( b2Vec2(0,-60), body->GetWorldCenter());
}
void qt::setCirLeft()
{
	body->ApplyLinearImpulse( b2Vec2(-30,0), body->GetWorldCenter());
}
//重载键盘
void qt::keyPressEvent(QKeyEvent *event)
{
	switch (event->key())
	{
		case Qt::Key_Up:
			{
				if(loaded)
				{
					if(started)
					{
					setCirUp();
					}
					else
					{
					startTime();
					}
				}
				else
				{
					start();
				}
			}
			break;
		case Qt::Key_Down:
			{
				if(loaded)
				{
					if(started)
					{
					setCirDown();
					}
					else
					{
					startTime();
					}
				}
				else
				{
					start();
				}
			}
			break;
		case Qt::Key_Left:
			{
				if(loaded)
				{
					if(started)
					{
					setCirLeft();
					}
					else
					{
					startTime();
					}
				}
				else
				{
					start();
				}
			}
			break;
		case Qt::Key_Right:
			{
				if(loaded)
				{
					if(started)
					{
					setCirRight();
					}
					else
					{
					startTime();
					}
				}
				else
				{
					start();
				}
			};
			break;
	}
}
//加载游戏
void qt::load()
{
	movie = new QMovie("nobird.gif");
	startButton->setMovie(movie);
	movie->start ();
	startButton->show();	
	startButton->adjustSize();
	backgroundpic.load("backgroundzi.png");
	update();
	
}
//重玩
void qt::replay()
{
	backgroundpic.load("backgroundstart");
	fileName = "D:/pointdata_A.txt";

	this->initBox2D();	

	movie = new QMovie("no-me.gif");
	startButton->setMovie(movie);
	movie->start ();		
	startButton->setGeometry(275,410,0,0);
	startButton->adjustSize();

	movie = new QMovie("bird.gif");
	cir->setMovie(movie);
	movie->start ();
	cir->show();	
	cir->setGeometry(50,250,50,50);
	cir->adjustSize();

	
	//initBox2D();
	update();
	started = 0;
}
//重载类
void qt::startButtonClick()
{
	if (loaded == 0)
	load();
	else
	{
		replay();
		body->SetGravityScale(0.5);
	}
}
////////////////////////////////////////////////////////////////////////////////
//自定义label类
MyLabel::MyLabel(QWidget * parent) : QLabel(parent) 
{
} 
void MyLabel::mouseReleaseEvent(QMouseEvent * ev) 
{ 
	Q_UNUSED(ev) 
	emit clicked(); 
}
////////////////////////////////////////////////////////////////////////////////////
//自定义物理接触类
void MyContact::BeginContact(b2Contact* contact)
{
	b2Fixture* a = contact->GetFixtureA();
	b2Fixture* b = contact->GetFixtureB();
	b2Body *tmp = a->GetBody();
	b2Body *tmp2 = b->GetBody();
	qt *main = static_cast<qt*>(body->GetUserData());
	if(main->success) return;
	if(tmp == body)
	{
		if  (tmp2!=endedge)
		{
		qt *main = static_cast<qt*>(body->GetUserData());
		main->end();
		}
	}
	else
	{
	if(tmp2 == body)
	{
		if  (tmp!=endedge)
		{
		qt *main = static_cast<qt*>(body->GetUserData());
		main->end();
		}
	} 
	}

}
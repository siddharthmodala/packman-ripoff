#include<stdio.h>
#include<conio.h>
#include<graphics.h>
#include<process.h>
#include<alloc.h>
#include<dos.h>

#define ESC 0x1b
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4b
#define RIGHT 0x4d
#define XX 00

int h,v,x=344,y=144;
int ext[12]={0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,0x100,0x200,0x400,0x800};
int hrz[14]={0x7ff,0x3fe,0x1dc,0x0f8,0x050,0x020,0x000,0x000,0x020,0x050,0x0f8,0x1dc,0x3fe,0x7ff};
int vrt[14]={0x801,0xc03,0xe07,0xf0f,0xf9f,0xfff,0xa95,0xfff,0xf9f,0xf0f,0xe07,0xc03,0x801,0x000};
int food[13]={0x7ff,0x7ff,0x7ff,0x7ff,0x7ff,0x7ff,0x7ff,0x7ff,0x7ff,0x7ff,0x7ff,0x7ff,0x7ff};
int flag=0;
int i=4,j=6;


	void* packman1;
	void* packmanup1;
	void* packmanup2;
	void* packmandn1;
	void* packmandn2;
	void* packmanlt1;
	void* packmanlt2;
	void* packmanrt1;
	void* packmanrt2;
	void* packman2;
	void* ball;
	void* ballerase;

	void menu();
	void gameover();
	void credits();


void main()
{
	void findv(int,int);
	void findh(int,int);
	void initpackman();
	void checkgame();


	int gd=DETECT,gm,gerror;
	char ch=0;
	int a=10,s=0;
	initgraph(&gd,&gm,"c:\\tc\\bgi");
	gerror=graphresult();
	if(gerror!=grOk)
	{
		printf("error in graph init %s",grapherrormsg(gerror));
		exit(0);
	}
	menu();
	cleardevice();
	initpackman();
	cleardevice();
	setlinestyle(SOLID_LINE,1,3);
	setcolor(3);
	for(i=0;i<14;i++)
	{
		for(j=0;j<12;j++)
		{
			if((hrz[i]&ext[j])!=0)
			{
				line(a,s,a+54,s);
			}
			if((vrt[i]&ext[j])!=0)
			{
			       line(a,s,a,s+36);
			}
			if((food[i]&ext[j])!=0)
			putimage(a+24,s+14,ball,XOR_PUT);
			a+=54;
		}
		s+=36;
		a =10;
	}
	i=4;
	j=6;
	while(ch!=ESC)
	{    fflush(stdin);
	     if(kbhit())
	     {
		ch=getch();
		if(ch==ESC)
		gameover();
		if(ch==XX)
		{
			ch=getch();
			switch(ch)
			{
			case UP:
				flag=1;
				findv(i,j);
				packman1=packmanup1;
				packman2=packmanup2;
				break;
			case DOWN:flag=2;
				findv(i,j);
				packman1=packmandn1;
				packman2=packmandn2;
				break;
			case LEFT:
				flag=3;
				findh(i,j);
				packman1=packmanlt1;
				packman2=packmanlt2;
				break;
			case RIGHT:flag=4;
				findh(i,j);
				packman1=packmanrt1;
				packman2=packmanrt2;
				break;
			default:flag=0;
			}
		}
	     }

		switch(flag)
		{
			case 1:if(v!=0 && y>=20 )
				{
					y-=36;
					v--;
					i--;
					if(i<0)
					i=0;
					putimage(x+10,y+10,ballerase,AND_PUT);
					checkgame();
				}
				break;
			case 2:if(v!=0 && y<=440)
				{
					y+=36;
					v--;
					i++;
					if(i>13)
					i=13;
					putimage(x+10,y+10,ballerase,AND_PUT);
				    checkgame();
				}
				break;
			case 3:if(h!=0 && x>=20)
				{
					x-=54;
					h--;
					j--;
					if(j<0)
					j=0;
					putimage(x+10,y+10,ballerase,AND_PUT);
					checkgame();
				}
				break;
			case 4:if(h!=0 && x<=600)
				{
					x+=54;
					h--;
					j++;
					if(j>11)
					j=11;
					putimage(x+10,y+10,ballerase,AND_PUT);
					checkgame();
				}
				break;
		}
		putimage(x,y,packman1,XOR_PUT);
		delay(180);
		putimage(x,y,packman1,XOR_PUT);
		putimage(x,y,packman2,XOR_PUT);
		delay(130);
		putimage(x,y,packman2,XOR_PUT);


  }
}

void menu()
{

     int maxx=getmaxx();
     int maxy=getmaxy();

	setcolor(2);
	setlinestyle(DASHED_LINE,1,3);
	rectangle(maxx/2-300,maxy/2-150,maxx/2+300,maxy/2+150);
	rectangle(maxx/2-280,maxy/2-130,maxx/2+280,maxy/2+130);
	settextstyle(4,0,5);
	outtextxy(200,0,"PACK MAN");
	settextstyle(3,0,2);
	setcolor(9);
	outtextxy(maxx/2-260,maxy/2-80,"* Use arrow keys to move the packman.");
	outtextxy(maxx/2-260,maxy/2-30,"* Press ESC to exit the game.");
	outtextxy(maxx/2-260,maxy/2+30,"* Press any key to start the game.....");
	getch();
	setlinestyle(SOLID_LINE,1,3);
	settextstyle(0,0,1);
}

void findh(int p,int q)
{
	h=0;
      if(flag==3)
      {
		for(;q>=0;q--)
		{
			if((vrt[p]&ext[q])!=0)
			break;
			else
			h++;
		}
      }
      if(flag==4)
      {
		for(;q<11;q++)
		{
			if((vrt[p]&ext[q+1])!=0)
			break;
			else
			h++;
		}
      }
}




void findv(int p,int q)
{
     v=0;
     if(flag==1)
     {
		for(;p>=0;p--)
		{
			if((hrz[p]&ext[q])!=0)
			break;
			else
			v++;
		}
     }
     if(flag==2)
     {
		for(;p<14;p++)
		{
			if((hrz[p+1]&ext[q])!=0)
			break;
			else
			v++;
		}
     }
}
void checkgame()
{
int p=0;
int sum=0;
		food[i]=(food[i]&(0xfff-ext[j]));
		for(p=0;p<13;p++)
		{
		   sum+=food[p];
		}
		if(sum==0)
		gameover();
}

void gameover()
{
	putimage(x,y,packman1,XOR_PUT);
	delay(300);
	cleardevice();
	setcolor(2);
	settextstyle(4,0,6);
	outtextxy(150,200,"GAME OVER");
	delay(1200);
	credits();
}
void credits()
{
	int maxx,maxy;
	maxx=getmaxx();
	maxy=getmaxy();
	cleardevice();
	setcolor(2);
	settextstyle(4,0,3);
	outtextxy(maxx/2-textwidth("closing simulation....")/2,maxy/2,"closing simulation.....");
	delay(1000);
	outtextxy(maxx-textwidth("Programming by:")-20,maxy-9,"Programming by:");
	outtextxy(maxx-textwidth("SIDDHARTH"),maxy-50,"SIDDHARTH");
	delay(1000);

	closegraph();
}




void initpackman()
{   cleardevice();
	setfillstyle(1,14);
	setcolor(14);

	//right packman
	pieslice(30,30,45,315,11);
	packman1=malloc(imagesize(15,15,45,45));
	packmanrt1=malloc(imagesize(15,15,45,45));
	getimage(15,15,45,45,packman1);
	packmanrt1=packman1;
	pieslice(30,30,10,350,11);
	packman2=malloc(imagesize(15,15,45,45));
	packmanrt2=malloc(imagesize(15,15,45,45));
	getimage(15,15,45,45,packman2);
	packmanrt2=packman2;
	putimage(15,15,packmanrt2,XOR_PUT);

	//left packman
	pieslice(30,30,0,135,11);
	pieslice(30,30,225,360,11);
	packmanlt1=malloc(imagesize(15,15,45,45));
	getimage(15,15,45,45,packmanlt1);
	pieslice(30,30,0,170,11);
	pieslice(30,30,190,360,11);
	packmanlt2=malloc(imagesize(15,15,45,45));
	getimage(15,15,45,45,packmanlt2);
	putimage(15,15,packmanlt2,XOR_PUT);

	//down packman
	pieslice(30,30,0,225,11);
	pieslice(30,30,315,360,11);
	packmandn1=malloc(imagesize(15,15,45,45));
	getimage(15,15,45,45,packmandn1);
	pieslice(30,30,0,260,11);
	pieslice(30,30,290,360,11);
	packmandn2=malloc(imagesize(15,15,45,45));
	getimage(15,15,45,45,packmandn2);
	putimage(15,15,packmandn2,XOR_PUT);

	//packman up
	pieslice(30,30,0,45,11);
	pieslice(30,30,135,360,11);
	packmanup1=malloc(imagesize(15,15,45,45));
	getimage(15,15,45,45,packmanup1);
	pieslice(30,30,0,80,11);
	pieslice(30,30,100,360,11);
	packmanup2=malloc(imagesize(15,15,45,45));
	getimage(15,15,45,45,packmanup2);
	putimage(15,15,packmanup2,XOR_PUT);

	setcolor(15);
	setfillstyle(1,15);
	fillellipse(5,5,2,2);
	ball=malloc(imagesize(2,2,8,8));
	getimage(3,3,7,7,ball);
	putimage(3,3,ball,XOR_PUT);

	setcolor(0);
	rectangle(5,5,15,15);
	ballerase=malloc(imagesize(5,5,15,15));
	getimage(5,5,15,15,ballerase);
}




//Charlie
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<process.h>
#include<stdlib.h>
void menu();                               //menu
void instructions();                       //instructions
void layout1();                            //for layout of the screen before start
void layout2();                            //for layout of the screen after start
void initialise_1();                       //for the function bullet_1
void initialise_2();                       //for the function bullet_2
void reinitialise();                       //to bring e/t to initial state
void arrowkeys();                          //to check any activity on the keyboard
void bullet_1();                           //for the first run of bullets
void bullet_2();                           //for further run of bullets
void detect();                             //to detect hits
void lev();                                //for level and score
void bonuses();                            //to generate bonuses
void polyn();                              //to give the co-ords of vertices of the ship
void gameover();                           //end graphics
int ch;                                    //to catch the keys pressed on the keyboard
int ship_posx=80,ship_posy=240;            //position co-ords of the ship
int bul_posx[12],bul_posy[12];             //x and y co-ords of the 11 bullets I will have in the screen at one instant
int x,y;                                   //to get the max pos of x and y, i.e., maxx=639 and maxy=479
int brk_var=0;                             //to break the first loop
int esc_var=0;                             //to break both loops if escape is pressed
int poly[16];                              //co.ords of ship corners
long long score=0,level=0;                 //score and level
int life=15;                               //life
int pos_life;                              //for pos. of the heart of life
int s=6;                                   //for game speed
int choice;                                //for checking choice in menu
char choice1;                              //for checking the choice after pressing escape b/w a game
int damage;                                //random variable for penalty if ship hides out of screen
int bonus;				   //random variable to generate bonus life and score
int bonusx,bonusy;                         //coords of bonus item
int bonus_run;                             //to control how long bonus will retain
int shield;                                //duration of shield active

void main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,"c:/turboc3/bgi");
randomize();
while(1)
 {
   reinitialise();
   menu();
   initialise_1();
   layout1();
       while(1)                            //loop 1
	{
	  if(brk_var==1 || esc_var==1)
	    break;
	  if(kbhit())
	    arrowkeys();
	  bullet_1();
	  layout2();
	  lev();
	  detect();
	}
       while(1)                            //loop 2
	{
	  if(kbhit())
	    arrowkeys();
	  if(esc_var==1)
	    break;
	  bonuses();
	  bullet_2();
	  layout2();
	  detect();
	  lev();
	  if(bul_posx[1]<=0)
	    initialise_2();
	}
 }
}

void menu()
{
  setbkcolor(BLUE);
  while(choice!=1)
    {
	rectangle(0,0,638,479);
	settextstyle(0,0,5);
	outtextxy(185,35,"CHARLIE");
	line(175,75,470,75);
	settextstyle(0,0,1);
	outtextxy(245,175,"1 - PLAY GAME");
	outtextxy(245,200,"2 - INSTRUCTIONS");
	outtextxy(245,225,"3 - CREDITS");
	outtextxy(245,250,"4 - EXIT");
	rectangle(175,338,428,378);
	outtextxy(195,354,"Enter choice number : ");
	gotoxy(49,23);
	cin>>choice;
	cleardevice();
	if(choice==2)
	   instructions();
	if(choice==3)
	   {
	     setfillstyle(SOLID_FILL,RED);
	     bar(220,165,420,315);
	     rectangle(220,165,420,315);
	     outtextxy(265,235,"ARYAMAAN JAIN");
	     getch();
	     cleardevice();
	     setfillstyle(SOLID_FILL,WHITE);
	   }
	if(choice==4)
	   {
	     closegraph();
	     restorecrtmode();
	     exit(0);
	   }
    }
}

void instructions()
{
 rectangle(0,0,638,479);
 outtextxy(272,40,"INSTRUCTIONS");
 line(265,50,373,50);
 outtextxy(25,150,"Planet earth is in a problem !");
 outtextxy(25,170,"We are in war with aliens.");
 outtextxy(25,190,"The weapon to win the war is hidden beyond the asteroid belt.");
 outtextxy(25,210,"You are CHARLIE.");
 outtextxy(25,230,"Cross the belt and win the war.");
 outtextxy(440,400,"Press enter to continue");
 getch();
 cleardevice();

 rectangle(0,0,638,479);
 line(265,50,373,50);
 outtextxy(272,40,"INSTRUCTIONS");
 line(17,100,175,100);
 outtextxy(25,90,  "Spaceship controls");
 outtextxy(25,140, "up          up arrow key");
 outtextxy(25,170, "down        down arrow key");
 outtextxy(25,200, "left        left arrow key");
 outtextxy(25,230, "right       right arrow key");
 outtextxy(25,260, "And.....");
 outtextxy(25,290, "Try not to press the keys for long,");
 outtextxy(25,320, "your ship might catch momentum.");
 outtextxy(25,350, "Press keys short and discrete.");
 outtextxy(440,400,"Press enter to continue");
 getch();
 cleardevice();

 rectangle(0,0,638,479);
 line(265,50,373,50);
 outtextxy(272,40,"INSTRUCTIONS");
 outtextxy(25,140,"Look out for these");
 outtextxy(25,180,"Extra life         ");
 outtextxy(25,220,"Extra points       $");
 outtextxy(25,260,"Shield             ");
 outtextxy(430,400,"Press enter to go to menu");
 getch();
 cleardevice();
}

void layout1()
{
 x=getmaxx(),y=getmaxy();
 polyn();
 setcolor(WHITE);
 fillpoly(8,poly);
 outtextxy(20,450,"PRESS ANY KEY TO START");
 rectangle(0,0,x-1,y);
 line(0,35,x,35);
 line(150,0,150,35);
 line(500,0,500,35);
 line(570,0,570,35);
 line(346,0,346,35);
 outtextxy(4,20,"LIFE :");
 pos_life=8;
 for(int i=life;i>0;i-=5)
   {
    gotoxy(pos_life,2);
    cout<<(char)3;
    pos_life+=2;
   }
 outtextxy(154,20,"SCORE :" );
 gotoxy(29,2);
 cout<<score/10;
 outtextxy(350,20,"LEVEL :");
 gotoxy(53,2);
 cout<<7-s;
 outtextxy(504,20,"ESC:EXIT");
 outtextxy(575,20,"P:PAUSE");
 getch();
}

void layout2()
{
 cleardevice();
 polyn();
 fillpoly(8,poly);
 rectangle(0,0,639,35);
 line(150,0,150,35);
 line(500,0,500,35);
 line(570,0,570,35);
 line(346,0,346,35);
 outtextxy(4,20,"LIFE :");
 pos_life=8;
 for(int i=life;i>0;i-=5)
  {
    gotoxy(pos_life,2);
    cout<<(char)3;
    pos_life+=2;
  }
 outtextxy(154,20,"SCORE :" );
 gotoxy(29,2);
 cout<<score/10;
 outtextxy(350,20,"LEVEL :");
 gotoxy(53,2);
 cout<<7-s;
 outtextxy(504,20,"ESC:EXIT");
 outtextxy(575,20,"P:PAUSE");
}

void initialise_1()
{
  ship_posx=80,ship_posy=240;              //initial position of the ship
  for(int i=1;i<=11;i++)
    {
      bul_posx[i]=660;                     //giving my 16 bullets the x pos
      bul_posy[i]=(random(45)+3)*10;       //giving my 16 bullets the y pos
    }
  bul_posx[1]=2000;                        //for delay in the begeinning,i.e., time for the player to settle
}

void initialise_2()
{
  for(int i=1;i<=10;i++)
    {
     bul_posx[i]=bul_posx[i+1];
     bul_posy[i]=bul_posy[i+1];
    }
  bul_posx[11]=640;
  bul_posy[11]=(random(44)+4)*10;          //to keep range from 0 to 480 in multiples of 10
}

void reinitialise()
{
  ship_posx=80,ship_posy=240;
  brk_var=0;
  esc_var=0;
  score=0;
  level=0;
  life=15;
  s=6;
  choice=0;
  choice1='n';
  bonus_run=0;
  cleardevice();
}

void arrowkeys()                          //ship will only go in multiples of 10
{                                         //initial position was x=40 and y=240
    ch=getch();
	    if(ch==72)
		ship_posy-=10;
	    else if(ch==75)
		ship_posx-=10;
	    else if(ch==77)
		ship_posx+=10;
	    else if(ch==80)
		ship_posy+=10;
	    else if(ch==27)
		{
		  outtextxy(165,280,"Are you sure you want to exit(Y/N)");
		  gotoxy(47,23);
		  rectangle(195,338,408,378);
		  outtextxy(240,354,"Enter choice : ");
		  cin>>choice1;
		  if(choice1=='Y' || choice1=='y')
		    {
		     cleardevice();
		     esc_var=1;
		    }
		}
	    else if(ch==80 || ch==112)
		{
		  outtextxy(280,240,"GAME PAUSED");
		  outtextxy(230,300,"PRESS ANY KEY TO CONTINUE");
		  getch();
		}
}

void bullet_1()
{
    if(bul_posx[1]>=0)                     //1
    {
    circle(bul_posx[1],bul_posy[1],5);
    bul_posx[1]-=10;
    delay(s);

    if(bul_posx[1]<=590)                   //2
    {
    circle(bul_posx[2],bul_posy[2],5);
    bul_posx[2]-=10;
    delay(s);

    if(bul_posx[2]<=590)                   //3
    {
    circle(bul_posx[3],bul_posy[3],5);
    bul_posx[3]-=10;
    delay(s);

    if(bul_posx[3]<=590)                   //4
    {
    circle(bul_posx[4],bul_posy[4],5);
    bul_posx[4]-=10;
    delay(s);

    if(bul_posx[4]<=590)                   //5
    {
    circle(bul_posx[5],bul_posy[5],5);
    bul_posx[5]-=10;
    delay(s);

    if(bul_posx[5]<=590)                   //6
    {
    circle(bul_posx[6],bul_posy[6],5);
    bul_posx[6]-=10;
    delay(s);

    if(bul_posx[6]<=590)                   //7
    {
    circle(bul_posx[7],bul_posy[7],5);
    bul_posx[7]-=10;
    delay(s);

    if(bul_posx[7]<=590)                   //8
    {
    circle(bul_posx[8],bul_posy[8],5);
    bul_posx[8]-=10;
    delay(s);

    if(bul_posx[8]<=590)                   //9
    {
    circle(bul_posx[9],bul_posy[9],5);
    bul_posx[9]-=10;
    delay(s);

    if(bul_posx[9]<=590)                   //10
    {
    circle(bul_posx[10],bul_posy[10],5);
    bul_posx[10]-=10;
    delay(s);

    if(bul_posx[10]<=590)                  //11
    {
    circle(bul_posx[11],bul_posy[11],5);
    bul_posx[11]-=10;
    delay(s);

    if(bul_posx[1]<=0)
     brk_var=1;
  }}}}}}}}}}}
}

void bullet_2()
{
  for(int i=1;i<=11;i++)
   {
     circle(bul_posx[i],bul_posy[i],5);
     bul_posx[i]-=10;
     delay(s);
   }
}

void detect()
{
   if(shield<=0)
     {
       for(int i=1;i<=11;i++)
	if(
	(bul_posx[i]==ship_posx     ||
	 bul_posx[i]==ship_posx-10  ||
	 bul_posx[i]==ship_posx-20  ||
	 bul_posx[i]==ship_posx-30  ||
	 bul_posx[i]==ship_posx-40  ||
	 bul_posx[i]==ship_posx-50)
	&&
	(bul_posy[i]==ship_posy     ||
	 bul_posy[i]==ship_posy-10  ||
	 bul_posy[i]==ship_posy-20  ||
	 bul_posy[i]==ship_posy+10  ||
	 bul_posy[i]==ship_posy+20)
	)life--;
       if(life==0)
	 gameover();
       if(ship_posx<0 || ship_posx>640 || ship_posy<30 || ship_posy>480)
	 {
	   damage=random(10);
	   if(damage==1)
	   life--;
	 }
     }
   else
     shield--;
}

void lev()
{
 score++;
 level++;
 if(level/10>500)
  {
   s=0;
   setbkcolor(9);
  }
 else if(level/10>300)
  {
   s=1;
   setbkcolor(0);
  }
 else if(level/10>190)
  {
   s=2;
   setbkcolor(4);
  }
 else if(level/10>110)
  {
   s=3;
   setbkcolor(5);
  }
 else if(level/10>70)
  {
   s=4;
   setbkcolor(6);
  }
 else if(level/10>40)
  {
   s=5;
   setbkcolor(2);
  }
 else
  {
   s=6;
   setbkcolor(1);
  }
}

void bonuses()
{
     if(bonus_run<=0)
       {
	 bonus=random(350);
	 if(bonus==1 || bonus==2 || bonus==3)
	   {
	     bonusx=random(55)*10;
	     bonusy=(random(43)+4)*10;
	     bonus_run=250;
	   }
       }
     else if(bonus_run>0)
       {
	 bonus_run--;
	 if(bonus==1)
	   outtextxy(bonusx,bonusy,"");
	 else if(bonus==2)
	   outtextxy(bonusx,bonusy,"$");
	 else if(bonus==3)
	   outtextxy(bonusx,bonusy,"");
	 if((bonusx==ship_posx     ||
	     bonusx==ship_posx-10  ||
	     bonusx==ship_posx-20  ||
	     bonusx==ship_posx-30  ||
	     bonusx==ship_posx-40  ||
	     bonusx==ship_posx-50)
	    &&
	    (bonusy==ship_posy     ||
	     bonusy==ship_posy-10  ||
	     bonusy==ship_posy-20  ||
	     bonusy==ship_posy+10  ||
	     bonusy==ship_posy+20)
	    )
	      {
		if     (bonus==1)life+=5;
		else if(bonus==2)score+=random(150);
		else if(bonus==3)shield+=150;
		bonus_run=0;
	      }
       }
}

void polyn()
{
  poly[0] =ship_posx-15 ;
  poly[1] =ship_posy-15 ;
  poly[2] =ship_posx    ;                  //x-coord. of the tip
  poly[3] =ship_posy    ;                  //y-coord. of the tip
  poly[4] =ship_posx-15 ;
  poly[5] =ship_posy+15 ;
  poly[6] =ship_posx-45 ;
  poly[7] =ship_posy+15 ;
  poly[8] =ship_posx-55 ;
  poly[9] =ship_posy+25 ;
  poly[10]=ship_posx-55 ;
  poly[11]=ship_posy-25 ;
  poly[12]=ship_posx-45 ;
  poly[13]=ship_posy-15 ;
  poly[14]=ship_posx-15 ;
  poly[15]=ship_posy-15 ;
}

void gameover()
{
  cleardevice();
  rectangle(150,150,490,330);
  outtextxy(280,240,"GAME OVER");
  delay(2000);
  cleardevice();
  rectangle(150,150,490,330);
  gotoxy(34,15);
  cout<<"SCORE : "<<score/10;
  gotoxy(34,17);
  cout<<"LEVEL : "<<7-s;
  gotoxy(34,12);
  if(score/10>=200 && score/10<300)
    cout<<"Good Score";
  else if((7-s)==5)
    cout<<"Good Control";
  else if((score/10>=300 && score/10<500) || (7-s)==6)
    cout<<"Excellent";
  else if(score/10>=500 || (7-s)==7)
    cout<<"The planet is saved";
  else
    cout<<"You crashed";
  delay(3000);
  cleardevice();
  esc_var=1;
}

/*
 Aryamaan Jain
 215
 Jaipur House
 12 - A
 Mayo College
*/



#include<bits/stdc++.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

using namespace std;
enum eDir{ STOP = 0, LEFT = 1, UPLEFT = 2,DOWNLEFT = 3,RIGHT = 4, UPRIGHT = 5, DOWNRIGHT=6};
class cBall //CLASS FOR THE BALL
{
private:
     int x,y; //ball position
     int originalX,originalY;
     eDir direction;
public:
    //constructor
    cBall(int posX,int posY)
    {
        //for reseting game later hence saving position
        originalX=posX;
        originalY=posY;
        x=posX;
        y=posY;
        direction=STOP;
    }
    void Reset()
    {   //x y are current position
        x=originalX;
        y=originalY;
        direction=STOP;
    }
    //func to change direction of ball
    void changeDirection(eDir d)
    {
        direction=d;
    }
    //random direction change of ball
    void randomDirection()
    {
        direction =(eDir)((rand() % 6) +1);
    }

    inline int getX(){return x;}
    inline int getY(){return y;}
    inline eDir getDirection(){return direction;}

    void Move()
    {
        switch(direction)
        {   //coordinate system starts from top left corner
            //going right increases x and going down increases y
        case STOP:
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UPLEFT:
            x--;
            y--;
            break;
        case DOWNLEFT:
             x--;
             y++;
             break;
        case UPRIGHT:
            x++;
            y--;
            break;
        case DOWNRIGHT:
            x++;
            y++;
            break;

        default:
            break;
        }
    }

    friend ostream & operator<<(ostream & o, cBall c)
    {
        o<<"Ball [" << c.x <<"," << c.y <<"][" <<c.direction <<"]"<<"\n";
        return o;
    }
};

//class to handle the two platforms by player 1 and player 2
class cPaddle
{
    private:
        int x,y;
        int originalX,originalY;
    public:
        //constructor
        cPaddle()
        {
           x=y=0;
        }
        cPaddle(int posX,int posY) : cPaddle()
        {
            originalX=posX;
            originalY=posY;
            x=posX;
            y=posY;
        }

        inline void Reset() { x=originalX;y=originalY;}
        inline getX() { return x;}
        inline getY() { return y;}
        inline void moveUp() { y--;}
        inline void moveDown() { y++; }

        friend ostream & operator<<(ostream & o, cPaddle c)
    {
        o<<"Paddle [" << c.x <<"," << c.y <<"]";
        return o;
    }
};

//class to bring both cball and cpaddle class toghether
class cGameManager
{
private:
    int width,height;
    int score1,score2;
    char up1,down1,up2,down2;//keys to control player
    bool quit;
    cBall * ball;//pointer to object;
    cPaddle * player1;
    cPaddle * player2;
public:
    //construct
    cGameManager(int w,int h)
    {
        srand(time(NULL));
        quit=false; //game runs
        up1='w';
        up2='i';
        down1='s';
        down2='k';

        score1=score2=0;
        width= w;
        height=h;
        ball =new cBall(w/2,h/2); //position of ball
        player1= new cPaddle(1,h/2 - 3);
        player2= new cPaddle(w-2,h/2 - 3);
     }
     //Destructor as we have dynamic memory to prevent memory leak
     ~cGameManager()
     {
            delete ball,player1,player2;
     }

     void  scoreUp(cPaddle * player)
     {
         if(player==player1)
            score1++;
         else if(player==player2)
            score2++;

         ball ->Reset();
         player1->Reset();
         player2->Reset();
     }
     //use of console and not fancy graphics
     void draw()
     {
        system("cls");
        for(int i=0;i<width+2;i++)
            cout<<"\xB2";
        cout<<endl;
        for(int i=0;i<height;i++) //i -> y coordinate
           {
               for(int j=0;j<width;j++) //j -> x coordinate
               {
                    int ballx = ball->getX();
                    int bally = ball->getY();
                    int player1x= player1->getX();
                    int player2x= player2->getX();
                    int player1y= player1->getY();
                    int player2y= player2->getY();

                    if(j==0)
                        cout<<"\xB2";
                    if(ballx==j && bally ==i)
                        cout<<"0";//ball

                    else if(player1x == j && player1y ==i)
                        cout<<"\xDB"; //player1
                    else if(player2x == j && player2y ==i)
                        cout<<"\xDB"; //player2

                    else if(player1x == j && player1y+1 ==i)
                        cout<<"\xDB"; //player1
                    else if(player1x == j && player1y+2 ==i)
                        cout<<"\xDB"; //player1
                    else if(player1x == j && player1y+3 ==i)
                        cout<<"\xDB"; //player1

                    else if(player2x == j && player2y+1 ==i)
                        cout<<"\xDB"; //player1
                    else if(player2x == j && player2y+2 ==i)
                        cout<<"\xDB"; //player1
                    else if(player2x == j && player2y+3 ==i)
                        cout<<"\xDB"; //player1

                    else
                        cout<< " ";

                    if(j==width-1)
                       cout<<"\xB2";
               }
                cout<<endl;
           }

        for(int i=0;i<width+2;i++)
            cout<<"\xB2";
        cout<<endl;

        cout<<"Score PLAYER 1:"<<score1<<endl<<"Score PLAYER 2:"<<score2<<endl;


    }

    void input()
    {
        ball ->Move();
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x= player1->getX();
        int player2x= player2->getX();
        int player1y= player1->getY();
        int player2y= player2->getY();

        if(_kbhit())    //if keyboard key pressed or not
         {
            char currrent=getch();
            if(currrent==up1)
                if(player1y>0)
                    player1->moveUp();
            if(currrent==up2)
                if(player2y>0)
                    player2->moveUp();
            if(currrent==down1)
                if(player1y + 4 < height)
                    player1->moveDown();
            if(currrent==down2)
                if(player2y + 4 < height)
                    player2 ->moveDown();

            if(ball->getDirection() == STOP)
                        ball->randomDirection();
            if(currrent=='q')
                quit=true;
          }
     }

     void Logic()
     {
        ball ->Move();
        int ballx = ball->getX();
        int bally = ball->getY();
        int player1x= player1->getX();
        int player2x= player2->getX();
        int player1y= player1->getY();
        int player2y= player2->getY();

            //left paddle
         for(int i=0;i<4;i++)
            if(ballx== player1x +1)
                if(bally ==player1y +i)
                    ball->changeDirection((eDir)((rand()%3) + 4 ));
          //right paddle
         for(int i=0;i<4;i++)
            if(ballx== player2x -1)
                if(bally ==player2y +i)
                    ball->changeDirection((eDir)((rand()%3) + 1 ));
            //bottomwall
          if(bally==height-1)
            ball->changeDirection(ball->getDirection()== DOWNRIGHT ? UPRIGHT : UPLEFT);

              //topwall
          if(bally==height-1)
            ball->changeDirection(ball->getDirection()== UPRIGHT ? DOWNRIGHT : DOWNLEFT);

            //rightwall
            if(ballx==width-1)
                scoreUp(player1);

            //leftwall
            if(ballx==0)
                scoreUp(player2);
     }

     void Run()
     {
         while(!quit)
         {
             draw();
             input();
             Logic();
             //Sleep(20);
         }
      }
};




int main()
{
   /* cBall c(0,0);//object c of cBall class
    cout<<c<<endl; //[0,0][0]

    c.randomDirection();
    cout<<c<<endl; //[0,0][6]

    c.Move();
    cout<<c<<endl; //[1,1][6]

    c.randomDirection();
    c.Move();
    cout<<c<<endl; //[2,2][6]

    c.randomDirection();
    c.Move();
    cout<<c<<endl;  //[3,2][5]
    */

   /* cPaddle p1(0,0);  //object of cpaddle
    cPaddle p2(10,0);
    cout<<p1<<endl;
    cout<<p2<<endl;

    p1.moveUp();
    p2.moveDown();
    cout<<p1<<endl;
    cout<<p2<<endl;
    */

    cGameManager c(40,20);
    c.Run();

    return 0;
}

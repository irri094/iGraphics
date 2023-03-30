# include "iGraphics.h"
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
#define whitecolor iSetColor(255,255,255)
#define blackcolor iSetColor(0,0,0)
#define bluecolor iSetColor(0,0,255)
#define redcolor iSetColor(200,5,5)

const int screenheit=800, screenwidth=1000;

vector <pii> platx;
vector<int> genjam;

bool lalmode;
FILE *fp;
int shuru=1;
int bhasha=1, langmenu=0, highscor=0, dificulty=0;

int life=3;
int platlen=200, platthick=10, platdis=200;
int rr,gg,bb;
int r1,g1=255,b1;
char digit[6]={'x','.','b','m','p','\0'},final_digit[7]={'F','x','.','b','m','p','\0'};
ll shomoy=0, level=1, score=0,displayed_score=0,final_displayed_score=0,highest_score=0;
int downmotion=0, g=1;
bool stopleft, stopright;
int shorifs_constant=552,unit=1000,LSD_Position=screenwidth-30,language=1;
int x = 300, y = 200, r = 200,mode=1,condition=1,score_timer_counter=0;
double time_passed=0,square_ball_length=24,screen_length=1000,screen_width=600,mover=60,slider=0,mover_speed=2,slider_speed=10;
int main_menu_mode=1;
char MainMenu[]={'M','a','i','n','M','e','n','u',language+48,'.','b','m','p','\0'},highscore[]={'h','i','g','h','s','c','o','r','e',language+48,'.','b','m','p','\0'},languages[]={'l','a','n','g','u','a','g','e',language+48,'.','b','m','p','\0'},levels[]={'l','e','v','e','l',language+48,'.','b','m','p','\0'}
,SCORE[]={'S','C','O','R','E',language+48,'.','b','m','p','\0'},Final_Score[]={'F','i','n','a','l',' ','S','c','o','r','e',language+48,'.','b','m','p','\0'};//Paste this function into iMouse under if(main_menu_mode)

/*
    function iDraw() is called again and again by the system.
*/
void showLife()
{
    for(int i=1;i<=life;i++)
    {
        iShowBMP((i-1)*50,screenheit-50,"LifeSymbol.bmp");
    }
}

int marajabo;

int number_of_digits(long long int n)
{
    int counter=0;
    do
    {
        n=n/10;
        counter++;
    }while(n>0);
    return counter;
}
void show_final_score()
{

    fp=fopen("Game Info.txt", "r");
    int al, sal;
    fscanf(fp, "%d %d", &al, &sal);
    highest_score=sal;
    fclose(fp);

    //cout<<highest_score<<"  "<<score<<endl;
    if(score>highest_score)
    {
        highest_score=score;
        fp=fopen("Game Info.txt","w");
        fprintf(fp,"%d %lld",language,highest_score);
        fclose(fp);
        Final_Score[11]+=4;
        if(bhasha==1)iShowBMP(0,0, "Final Score5.bmp");
        if(bhasha==2)iShowBMP(0,0, "Final Score6.bmp");
        if(bhasha==3)iShowBMP(0,0, "Final Score7.bmp");

        final_displayed_score=score;
        do
        {
            final_digit[1]=(char) (final_displayed_score%10)+48;
            iShowBMP(LSD_Position,400,final_digit);
            LSD_Position=LSD_Position-50;
            final_displayed_score=final_displayed_score/10;
        }while(final_displayed_score>0);
    }

    else{
        iShowBMP(0,0,Final_Score);
        LSD_Position=screenwidth/2+(number_of_digits(score)/2)*50+(number_of_digits(score)%2)*25;
        final_displayed_score=score;



        do
        {
            final_digit[1]=(char) (final_displayed_score%10)+48;
            iShowBMP(LSD_Position,400,final_digit);
            LSD_Position=LSD_Position-50;
            final_displayed_score=final_displayed_score/10;
        }while(final_displayed_score>0);
    }
}
void show_score()
{

    if(mode==0) return;
    showLife();
    unit=1050-25*level*(level+1);
    iSetColor(0,0,0);
    //iRectangle(920-number_of_digits(score)*50, 572, 70+number_of_digits(score)*50, 25);
    iSetColor(0,0,0);
    //iText(930-number_of_digits(score)*50, 580, "SCORE :");
    LSD_Position=screenwidth-65;
    if(mode) score_timer_counter++;
    if(score_timer_counter>=unit) score++;
    SCORE[5]=language+48;
    score_timer_counter=score_timer_counter%unit;
    displayed_score=score;



    do
    {
        digit[0]=(char) (displayed_score%10)+48;
        iShowBMP(LSD_Position,screenheit-55,digit);
        LSD_Position=LSD_Position-50;
        displayed_score=displayed_score/10;

    }while(displayed_score>0);

    if(bhasha==1) iShowBMP(LSD_Position-175,screenheit-55,"SCORE1.bmp");
    if(bhasha==2) iShowBMP(LSD_Position-175,screenheit-55,"SCORE2.bmp");
    if(bhasha==3) iShowBMP(LSD_Position-175,screenheit-55,"SCORE3.bmp");
}

void reset()
{
    //if(mode==0) return;
    mover=100;
    mode=1;
    slider=0;
    iResumeTimer(0);
    iResumeTimer(1);
    iResumeTimer(2);
    iResumeTimer(3);
        shuru=0;
        score_timer_counter=0;
        unit=1000;
        displayed_score=0;
        final_displayed_score=0;
        shomoy=0, level=marajabo, score=0,displayed_score=0,final_displayed_score=0;
}
void is_game_over()
{
    int ballposx=slider+screen_length/2;
    int ballposy= shorifs_constant-mover;
    int sbl=(int)square_ball_length;
    if(!(ballposy+sbl<screenheit-96 && ballposy>30))
    {
        life--;
        mover=100;
        mode=1;
        slider=0;

        if(life==0){
            mode=0;
            return;
        }
    }
    //if(life) mode=1;
    //else mode=0;//Insert the conditions of game over.
}
//void iDraw() {
//  iClear();
//  //place your drawing codes here
//  iSetColor(255,0,0);
//  iFilledRectangle(screen_length/2-square_ball_length/2+slider,screen_width-2*square_ball_length-mover,square_ball_length,square_ball_length);
//  is_game_over();
//  if(mode) mover=mover+mover_speed;
//}
//

/*
    function iDraw() is called again and again by the system.

    */
    double nicherx[3]={0,30,15},nichery[3]={0,0,30};
    double uporerx[3]={0,15,30},uporery[3]={600,574,600};

void iDraw() {
    //place your drawing codes here

    if(mode==0){
        iPauseTimer(0);
        iPauseTimer(1);
        iPauseTimer(2);
        iPauseTimer(3);
    }

    iClear();

    //whitecolor;
    iSetColor(r1,g1,b1);

    iFilledRectangle(0,0,1e3,1e3);
    bluecolor;


    for(int i=0; i<platx.size(); i++){
        if(genjam[i])
        iFilledRectangle(platx[i].first, platx[i].second, platlen, platthick);
        else {
            redcolor;
            iFilledRectangle(platx[i].first, platx[i].second, platlen, platthick);
            bluecolor;
        }
    }

    iSetColor(255,0,0);

    //
    int ballposx=slider+screen_length/2;
    int ballposy= shorifs_constant-mover;
    int sbl=(int)square_ball_length;
    //

    //iFilledRectangle(screen_length/2-square_ball_length/2+slider,screen_width-2*square_ball_length-mover,square_ball_length,square_ball_length);
    iFilledCircle(ballposx, ballposy+sbl/2, sbl/2);
    is_game_over();
//    if(downmotion==1)
//        if(mode) mover=mover+mover_speed;
    whitecolor;
    iFilledRectangle(0,screenheit-60,1e3,screenheit-80);
    iSetColor(rr,gg,bb);

    double nicherx[3]={0,30,15},nichery[3]={0,0,30};
    double uporerx[3]={0,15,30},uporery[3]={screenheit-60,screenheit-96,screenheit-60};

    for(int i=1 ; i<=35 ;i++ )
    {
        iFilledPolygon(nicherx ,nichery ,3);
        nicherx[0]+=30;nicherx[1]+=30;nicherx[2]+=30;

    }
    for(int i=1 ;i<35 ;i++)
    {
        iFilledPolygon(uporerx , uporery , 3);
        uporerx[0]+=30;uporerx[1]+=30;uporerx[2]+=30;
    }
    show_score();
    //place your drawing codes here

    //

    if(shuru){
        iClear();
        iShowBMP(0,0, MainMenu);
    }

    if(mode==0){
        iClear();
        show_final_score();
    }
    if(langmenu and shuru!=1){
        iClear();
        iShowBMP(0,0, languages);
    }
    if(highscor){
        iClear();
        if(bhasha==1)iShowBMP(0,0, "highscore1.bmp");
        if(bhasha==2)iShowBMP(0,0, "highscore2.bmp");
        if(bhasha==3)iShowBMP(0,0, "highscore3.bmp");
        displayed_score=highest_score;
        //iShowBMP(0,0,Final_Score);

        LSD_Position=screenwidth/2+(number_of_digits(score)/2)*50+(number_of_digits(score)%2)*25;
        final_displayed_score=highest_score;

        do
        {
            final_digit[1]=(char) (final_displayed_score%10)+48;
            iShowBMP(LSD_Position,400,final_digit);
            LSD_Position=LSD_Position-50;
            final_displayed_score=final_displayed_score/10;
        }while(final_displayed_score>0);
    }

    if(dificulty){
        if(bhasha==1)iShowBMP(0,0, "level1.bmp");
        if(bhasha==2)iShowBMP(0,0, "level2.bmp");
        if(bhasha==3)iShowBMP(0,0, "level3.bmp");
    }
    //
}

//void fallball(){
//    if(downmotion==1)
//        if(mode){
//            mover=mover+mover_speed;
//        }
//}

void ballonplatform(){
    int falling=0;
    int bam=1, dan=1;

    int ballposx=slider+screen_length/2;
    int ballposy= shorifs_constant-mover;
    int sbl=(int)square_ball_length;

    for(int i=0; i<platx.size(); i++){
        int c = ballposy-(platx[i].second+platthick);

        if(c<=0 and ballposy+sbl>=platx[i].second){
            if(ballposx+sbl/2<=platx[i].first and ballposx+sbl/2>=platx[i].first-5) dan=0;
            if(ballposx-sbl/2>=platx[i].first+platlen and ballposx-sbl/2<=platx[i].first+platlen+5) bam=0;
        }


        if( fabs(ballposx- (platx[i].first+platlen/2)) -platlen/2 <=sbl/2 ){
            if( ballposy>=platx[i].second+platthick && ballposy< platx[i].second+platthick+3+level){
                falling=i+1;
                if(genjam[i]==0) mode=0;
                break;
            }
        }

    }

    //cout<<ballposx<<"  "<<ballposy<<endl;
    shomoy+=10;
    if(falling==0) downmotion=0;
    else downmotion=falling;
    if(bam==0) stopleft=true; else stopleft=false;
    if(dan==0) stopright=true; else stopright=false;
}

void chenjtime(){
    int ballposx=slider+screen_length/2;
    int ballposy= shorifs_constant-mover;
    int sbl=(int)square_ball_length;





    if(platx.back().second>screenheit){
        //downmotion++;
        if(downmotion) downmotion++;
        int y=platx.back().second;
        platx.pop_back();
        platx.insert(platx.begin(), make_pair((rand()%(screenwidth-platlen)), y-4*platdis));

        if(lalmode)
            genjam.pop_back(), genjam.insert(genjam.begin(), rand()%5);
    }
     // speed of platform

    for(int i=0; i<platx.size(); i++){
        platx[i].second+=level;
        //if(downmotion==0) mover-=level;
    }

    if(downmotion){
        if(mode){
            ballposy=platx[downmotion-1].second + platthick ;
            mover=shorifs_constant-ballposy;
        }
    }
    else mover=mover+mover_speed;


    if(shomoy>10000) level = (level>=5 ? 5: level+1), shomoy=0;
    if(level==5) lalmode=true;
    //cout<<shomoy<<endl;
}


/*
    function iMouseMove() is called when the user presses and drags the mouse.
    (mx, my) is the position where the mouse pointer is.
    */
void iMouseMove(int mx, int my) {
    printf("%d %d\n",mx,my);
    //place your codes here
}

/*
    function iMouse() is called when the user presses/releases the mouse.
    (mx, my) is the position where the mouse pointer is.
    */
void iMouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            if(mode==0&&((mx>=601&&mx<=876&&my>=43&&my<=125)||(mx>=876&&mx<=933&&62*my>=57*mx-49900&&62*my+57*mx<=57025)))
            {
                exit(0);
            }
            if(shuru and (mx>=587&&mx<=958&&my>=587&&my<=716)){
                shuru=0,dificulty=1;
            }



            if(dificulty and (mx>=67&&mx<=440&&my>=400&&my<=531)){
                dificulty=0, reset(), level=1,marajabo=1, life=3;
            }
            if(dificulty and (mx>=67&&mx<=440&&my>=240&&my<=371)){
                dificulty=0, reset(), level=3,marajabo=3, life=3;
            }
            if(dificulty and (mx>=67&&mx<=440&&my>=78&&my<=209)){
                dificulty=0, reset(), level=4,marajabo=4, life=3;
            }

            if(mode==0 and (mx>=101&&mx<=376&&my>=43&&my<=125)){
                reset(); life=3, level=marajabo, shuru=1;
            }




            if(highscor and (mx>=601&&mx<=876&&my>=43&&my<=125)){
                exit(0);
            }
            if(highscor and (mx>=101&&mx<=376&&my>=43&&my<=125)){
                shuru=1, highscor=0;
            }
            if(shuru and (mx>=587&&mx<=958&&my>=419&&my<=548)) highscor=1, shuru=0;
            if(shuru and (mx>=587&&mx<=958&&my>=78&&my<=207)) exit(0);
            if(shuru and (mx>=587&&mx<=958&&my>=246&&my<=375)){
                langmenu=1,shuru=0;
            }

            if(langmenu and (mx>=67&&mx<=440&&my>=400&&my<=531)) {
                    bhasha=1,langmenu=0,shuru=1;
                SCORE[5]=Final_Score[11]=MainMenu[8]=highscore[9]=languages[8]=levels[5]=bhasha+48;
                fp=fopen("Game Info.txt","w");
                fprintf(fp,"%d %lld",bhasha,highest_score);
                fclose(fp);
            }
            if(langmenu and (mx>=67&&mx<=440&&my>=240&&my<=371)) {
                    bhasha=2,langmenu=0,shuru=1;
                SCORE[5]=Final_Score[11]=MainMenu[8]=highscore[9]=languages[8]=levels[5]=bhasha+48;
                fp=fopen("Game Info.txt","w");
                fprintf(fp,"%d %lld",bhasha,highest_score);
                fclose(fp);
            }
            if(langmenu and (mx>=67&&mx<=440&&my>=78&&my<=209)) {
                    bhasha=3,langmenu=0,shuru=1;
                SCORE[5]=Final_Score[11]=MainMenu[8]=highscore[9]=languages[8]=levels[5]=bhasha+48;
                fp=fopen("Game Info.txt","w");
                fprintf(fp,"%d %lld",bhasha,highest_score);
                fclose(fp);
            }

            if(highscor and (mx>=557&&mx<=933&&my>=78&&my<=213)) shuru=1, highscor=0;
        //  printf("x = %d, y= %d\n",mx,my);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        //place your codes here
    }
}

/*
    function iKeyboard() is called whenever the user hits a key in keyboard.
    key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key) {
    if(key=='\r')
    {
        reset();
    }
    if(mode and !shuru and !highscor){
        if(key=='p'){

            iPauseTimer(0);
            iPauseTimer(1);
            iPauseTimer(2);
            iPauseTimer(3);

        }
        if (key == 'q') {
            exit(0);
        }

        if(mode)
        {
        if(key=='w')
        {
            //mover=mover-120*mover_speed;
        }
        if(key=='a' and slider>-screen_length/2.0+ 20.0 +2*level and !stopleft) slider=slider-slider_speed*level;
        if(key=='d' and slider< screen_length/2.0+-20.0 -2*level and !stopright) slider=slider+slider_speed*level;
        }
    }
    //place your codes for other keys here
}

void iSpecialKeyboard(unsigned char key) {
    if (key == GLUT_KEY_END) {
        exit(0);
    }
}
void changecolor()
{
    rr=rand()%200;
    gg=rr;
    bb=rr;
}
void background_color()
{
    r1=rand()%256;
    b1=rand()%256;
}

int main() {
//  //place your own initialization codes here.
    srand(time(NULL));

    for(int i=0; i<4; i++){
        platx.push_back(make_pair(rand()%(screenwidth-platlen), i*platdis));
        genjam.push_back(1);
    }
    fp=fopen("Game Info.txt","r");
    fscanf(fp,"%d %lld",&bhasha,&highest_score);
    fclose(fp);
    SCORE[5]=Final_Score[11]=MainMenu[8]=highscore[9]=languages[8]=levels[5]=bhasha+48;


    iSetTimer(1000,changecolor);
    iSetTimer(10, chenjtime);
    iSetTimer(1, ballonplatform);
    iSetTimer(1000,background_color);
    //iSetTimer(1, fallball);

    iInitialize(screenwidth, screenheit, "rapid roll");
    return 0;
}

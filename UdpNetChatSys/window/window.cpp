#include"window.h"
using namespace std;
myWindow::myWindow()
{
	initscr();
	curs_set(0);
}

myWindow::~myWindow()
{
	delwin(header);
	delwin(output);
	delwin(friendList);
	delwin(input);
	endwin();
}

void myWindow::createHeader()
{
	int y=0;
	int x=0;
	int h=LINES/5;
	int w=COLS;
	header=createNewWin(h,w,y,x);
}

void myWindow::createOutput()
{
	int y=LINES/5;
	int x=0;
	int h=LINES*3/5;
	int w=COLS*2/3;
	output=createNewWin(h,w,y,x);
}


void myWindow::createFriendList()
{
	int y=LINES/5;
	int x=COLS*2/3;
	int h=LINES*3/5;
	int w=COLS*1/3;
	friendList=createNewWin(h,w,y,x);
}

void myWindow::createInput()
{
	int y=LINES*4/5;
	int x=0;
	int h=LINES/5;
	int w=COLS;
	input=createNewWin(h,w,y,x);
}
	
void myWindow::myWinRefresh(WINDOW *win)  // 刷新窗口
{
	wrefresh(win);
}

WINDOW* myWindow::createNewWin(int h,int w,int stratY,int stratX)
{
	WINDOW *local=newwin(h,w,stratY,stratX);
	box(local,0,0);
	return local;
}

void myWindow::putStrToWin(WINDOW *win,int startY,int startX,const std::string &msg)  // 向窗口中写数据
{
	mvwaddstr(win,startY,startX,msg.c_str());
}


void myWindow::clearWinLine(WINDOW* win,int begin,int line)       // 清除窗口从begin开始的line行
{
	while(line-->0)
	{
		wmove(win,begin++,0);
		wclrtoeol(win);
	}
}

std::string myWindow::getWinStr(WINDOW* win)   //  得到窗口里面的内容
{
	char buf[1024]={0};
	wgetnstr(win,buf,sizeof(buf));
	return buf;
}


#ifdef DEBUG
int main()
{
	myWindow win;
	
	win.createHeader();
	win.myWinRefresh(win.header);

	int y,x;
	std::string msg="welecom to chat sys!";
	getmaxyx(win.header,y,x);
	int startY=y/2;
	int startX=x*2/5;
	win.putStrToWin(win.header,startY,startX,msg);
	win.myWinRefresh(win.header);
	
 	win.createOutput();
 	win.createFriendList();
 	win.createInput();

 	sleep(5);
 	win.myWinRefresh(win.output);
 	sleep(5);	
 	win.myWinRefresh(win.friendList);
 	sleep(5);	
 	std::string getWinStr(WINDOW* win);
 	win.myWinRefresh(win.input);
 	sleep(5);


	std::string str=win.getWinStr(win.header);
	win.myWinRefresh(win.header);
	sleep(5);	
	
	win.clearWinLine(win.header,startY,1);
	win.myWinRefresh(win.header);
	
	
	win.putStrToWin(win.header,0,0,str);
	win.myWinRefresh(win.header);
	sleep(5);	
	return 0;
}

#endif

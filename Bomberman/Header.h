#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <ctime>
#include <algorithm>
#include <conio.h>
#define HEIGHT 25
#define WIDTH 80
#define PATH 0
#define WALL 1
#define PLAYER 3
#define ENEMY 2
int masihmain=1;
enum direction{UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, SPACE = 32, BOMB = 4, ASAP = 10};
using namespace std;
HANDLE enemyHandle,handle;
int map[HEIGHT][WIDTH];
void gotoxy(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(h, pos);
}
void lose();
void win();
class Bomb{
public:
	int x;
	int y;
	int dur;
	int kekiri,keatas,kekanan,kebawah;
	int from;
	Bomb(int x, int y, int from){
		this->x = x;
		this->y = y;
		this->dur = 3;
		this->paint();
		map[y][x]=BOMB;
		this->from = from;
	}
	void clearArea(){
		for(int i=0;i<kekiri;i++){
			gotoxy(this->x-i,this->y);
			cout<<' ';
			map[this->y][this->x-i]=PATH;
		}
		for(int i=0;i<kekanan;i++){
			gotoxy(this->x+i,this->y);
			cout<<' ';
			map[this->y][this->x+i]=PATH;
		}
		for(int i=0;i<keatas;i++){
			gotoxy(this->x,this->y-i);
			cout<<' ';
			map[this->y-i][this->x]=PATH;
		}
		for(int i=0;i<kebawah;i++){
			gotoxy(this->x,this->y+i);
			cout<<' ';
			map[this->y+i][this->x]=PATH;
		}
	}
	void explode(){
		int kiri=1,kanan=1,atas=1,bawah=1;
		kekiri = kekanan = keatas = kebawah = 1;
		int kenaPlayer=0;
		int kenaMusuh=0;
		int ketemuX=-1,ketemuY=-1;
		for(int i=0;i<6;i++){
			if(kiri){
				if(map[this->y][this->x-i]==PLAYER){
					kenaPlayer=1;
				}else if(map[this->y][this->x-i]==ENEMY){
					kenaMusuh=1;
				}else if(map[this->y][this->x-i]==WALL){
					kiri=0;
					map[this->y][this->x-i]=PATH;
				}
				if(this->x-i >= WIDTH-1 || this->x-i < 0){
					
				}else{
					gotoxy(this->x-i,this->y);
					cout<<'@';
					map[this->y][this->x-i]=ASAP;
					kekiri++;
				}
			}
			if(kanan){
				if(map[this->y][this->x+i]==PLAYER){
					kenaPlayer=1;
				}else if(map[this->y][this->x+i]==ENEMY){
					kenaMusuh=1;
				}else if(map[this->y][this->x+i]==WALL){
					kanan=0;
					map[this->y][this->x+i]=PATH;
				}
				if(this->x+i >= WIDTH-1 || this->x+i < 0){
					
				}else{
					gotoxy(this->x+i,this->y);
					cout<<'@';
					map[this->y][this->x+i]=ASAP;
					kekanan++;
				}
			}
			if(atas){
				if(map[this->y-i][this->x]==PLAYER){
					kenaPlayer=1;
				}else if(map[this->y-i][this->x]==ENEMY){
					kenaMusuh=1;
				}else if(map[this->y-i][this->x]==WALL){
					atas=0;
					map[this->y-i][this->x]=PATH;
				}
				if(this->y-i >= HEIGHT-1 || this->y-i < 0){
					
				}else{
					gotoxy(this->x,this->y-i);
					map[this->y-i][this->x]=ASAP;
					cout<<'@';
					keatas++;
				}
			}
			if(bawah){
				if(map[this->y+i][this->x]==PLAYER){
					kenaPlayer=1;
				}else if(map[this->y+i][this->x]==ENEMY){
					kenaMusuh=1;
				}else if(map[this->y+i][this->x]==WALL){
					bawah=0;
					map[this->y+i][this->x]=PATH;
				}
				if(this->y+i >= HEIGHT-1 || this->y+i < 0){
					
				}else{
					gotoxy(this->x,this->y+i);
					map[this->y+i][this->x]=ASAP;
					cout<<'@';
					kebawah++;
				}
			}
		}
		if(kenaMusuh){
			system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");
			masihmain=0;
			Sleep(100);
			system("cls");
			win();
		}else if(kenaPlayer){
			system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");
			masihmain=0;
			Sleep(100);
			system("cls");
			lose();
		}
	}
	void paint(){
		gotoxy(this->x,this->y);
		cout<<'o';
	}
};
class Point{
public:
	int x;
	int y;
	Point *parent;
	Point(int x, int y, Point* parent){
		this->x = x;
		this->y = y;
		this->parent = parent;
	}
	Point* opposite(){
		int c = (this->x < parent->x) ? -1 : 1;
		int r = (this->y < parent->y) ? -1 : 1;

		if(this->x == parent->x)
			return new Point(this->x, this->y + r, this);
		else if(this->y == parent->y)
			return new Point(this->x + c, this->y, this);

		return NULL;
	}
};
vector<Bomb*> vBomb;
vector<Bomb*> hapus;
class Player{
public:
	int x;
	int y;
	int kind;
	int oldX;
	int oldY;
	int bombCounter;
	vector<Point*> vPoint;
	vector<Point*> way;
	~Player(){

	}
	Player(int x, int y, int kind){
		this->x = x;
		this->y = y;
		this->kind = kind;
		oldX = x;
		oldY = y;
		bombCounter=0;
	}
	void move(int direction){
		int plusX=0,plusY=0;
		if(direction == UP){
			plusY=-1;
		}else if(direction == DOWN){
			plusY = 1;
		}else if(direction == LEFT){
			plusX = -1;
		}else if(direction == RIGHT){
			plusX = 1;
		}
		if(this->y+plusY<0 || this->y+plusY>=HEIGHT || this->x+plusX<0 || this->x+plusX>=WIDTH){
			return;
		}
		if(map[this->y+plusY][this->x+plusX]==PATH || map[this->y+plusY][this->x+plusX]==ASAP){
			if(map[this->y+plusY][this->x+plusX]==ASAP){
				if(kind==ENEMY){
			system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");
					masihmain=0;
					Sleep(100);
					system("cls");
					win();
				}else{
			system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");system("cls");
					masihmain=0;
					Sleep(100);
					system("cls");
					lose();
				}
				return;
			}
			oldX = this->x;
			oldY = this->y;
			this->x += plusX;
			this->y += plusY;
			int temp = map[oldY][oldX];
			map[oldY][oldX] = map[y][x];
			map[y][x] = (this->kind==ENEMY)?ENEMY:PLAYER;
			this->repaint();
		}
	}
	void hapus(){
		gotoxy(this->x, this->y);
		cout<<' ';
	}
	void repaint(){
		if(map[oldY][oldX]==PATH){
			gotoxy(this->oldX, this->oldY);
			cout<<' ';
		}
		this->print();
	}
	void gerakRandom(){
		int move = rand()%4;
		if(move==1){
			this->move(LEFT);
		}else if(move==2){
			this->move(UP);
		}else if(move==3){
			this->move(RIGHT);
		}else{
			this->move(DOWN);
		}
		Sleep(250);
	}
	void print()
	{
		gotoxy(this->oldX,this->oldY);
		cout<<" ";
		gotoxy(this->x, this->y);
		cout<<(char)this->kind;
		gotoxy(0, 0);
	}
	void deleteBomb(){
		bombCounter--;
	}
	void dropBomb(){
		if(bombCounter<3){
			int x = this->x;
			int y = this->y;
			move(UP);
			if(this->y == y){
				move(DOWN);
				if(this->y == y){
					move(LEFT);
					if(this->x == x){
						move(RIGHT);
					}
				}
			}
			map[y][x]=BOMB;
			Bomb *b = new Bomb(x,y,kind);
			this->repaint();
			b->paint();
			bombCounter++;
			vBomb.push_back(b);
		}
	}
	int belumKetemu;
	int tujuanX;
	int tujuanY;
	Point *dest;
	bool peta[WIDTH][HEIGHT];
	int lihatSekitar(){
		int ketemuPlayer=0;
		for(int i=-13;i<13;i++){
			for(int j=-13;j<13;j++){
				if(i+this->y<0 || i+this->y>=HEIGHT || j+this->x<0 || j+this->x>=WIDTH ||map[i+this->y][j+this->x]==WALL){continue;}
				if(map[i+this->y][j+this->x]==PLAYER){
					ketemuPlayer=1;
				}
			}
		}
		return ketemuPlayer;
	}
	Point *start;
	Point *end;
	Player *kita;
	Player *musuh;
	void pathFinding(Player *destination, Player *from){
		if(kind==ENEMY){
			vPoint.clear();
			way.clear();
			start = new Point(from->x,from->y,NULL);
			tujuanX = destination->x;
			tujuanY = destination->y;
			this->kita = destination;
			this->musuh = from;
			vPoint.push_back(start);
			for(int i=0;i<HEIGHT;i++){
				for(int j=0;j<WIDTH;j++){
					peta[i][j]=false;
				}
			}
			belumKetemu=1;
				while((belumKetemu || vPoint.size()!=0)&&masihmain){
					Point *curr = vPoint.at(0);
					open(curr->x+1,curr->y,curr);
					open(curr->x,curr->y+1,curr);
					open(curr->x-1,curr->y,curr);
					open(curr->x,curr->y-1,curr);
					vPoint.erase(vPoint.begin());
				}
			if(1!=belumKetemu && masihmain){
				Point *curr = dest;
				while(curr->parent!=NULL){
					way.push_back(curr);
					curr=curr->parent;
				}
				reverse(way.begin(),way.end());
				if(way.size()>2 && masihmain){
					for(int i=0;i<way.size()-2&&masihmain;i++){
						Point *temp = way.at(i);
						if(map[temp->y][temp->x]==PATH){
							this->oldX = this->x;
							this->oldY = this->y;
							this->x = temp->x;
							this->y = temp->y;
							int t = map[this->oldY][this->oldX];
							map[this->oldY][this->oldX] = map[this->y][this->x];
							map[y][x]=t;
							repaint();
							Sleep(150);
						}else{
							gerakRandom();
						}
						delete temp;
					}
					way.clear();
					dropBomb();
					return;
				}else{
					way.clear();
				}
			}else gerakRandom();
		}
	}
	void open(int x,int y,Point* parent){
		if(belumKetemu){
			if(x<0 || y <0 || x>=WIDTH || y>=HEIGHT){
				return;
			}else if(peta[y][x]==true || map[y][x]==WALL || map[y][x]==BOMB || map[y][x]==ASAP){
				return;
			}else{
				peta[y][x] = true;
				Point *temp = new Point(x,y,parent);
				vPoint.push_back(temp);
				if(y==tujuanY && x ==tujuanX){
					belumKetemu = false;
					dest = temp;
				}
			}
		}
	}
};
Player *p=NULL,*e=NULL;
DWORD WINAPI run(LPVOID arg){
	while(masihmain){
		try{
			for(int i=0;i<vBomb.size();i++){
				if(masihmain && vBomb.size()>=1){
					Bomb *b = vBomb.at(i);
					if(--b->dur<=0){
						b->explode();
						if(b->from==ENEMY && masihmain){
							e->deleteBomb();	
							hapus.push_back(b);
							vBomb.erase(vBomb.begin()+i);
						}else if(b->from!=ENEMY && masihmain){
							p->deleteBomb();
							hapus.push_back(b);
							vBomb.erase(vBomb.begin()+i);
						}
					}
				}
			}
			Sleep(1000);
			for(int i=0;i<hapus.size();i++){
				if(i<=hapus.size()&&masihmain)hapus.at(i)->clearArea();
			}
			hapus.clear();
		}catch(exception ee){
			continue;
		}
	}
	
	CloseHandle(handle);
	return 0;
}
DWORD WINAPI threadEnemy(LPVOID arg){
	while(masihmain){
		try{
			int ketemuPlayer=e->lihatSekitar();
			if(ketemuPlayer){
				e->pathFinding(p,e);
			}else{
				e->gerakRandom();
			}
		}catch(exception ee){
			continue;
		}
	}
	CloseHandle(enemyHandle);
	return 0;
}
void win(){
	for(int i=0;i<10;i++){
		system("cls");
	}
	cout<<"\n\n\n\n\n\n\n\n\n\n\n __     __          __          ___\n";       
	cout<<" \\ \\   / /          \\ \\        / (_)     \n";   
	cout<<"  \\ \\_/ /__  _   _   \\ \\  /\\  / / _ _ __\n";    
	cout<<"   \\   / _ \\| | | |   \\ \\/  \\/ / | | '_ \\ \n";  
	cout<<"    | | (_) | |_| |    \\  /\\  /  | | | | |\n";  
	cout<<"    |_|\\___/ \\__,_|     \\/  \\/   |_|_| |_|\n";  
	p = e = NULL;
}
void lose(){
	for(int i=0;i<10;i++){
		system("cls");
	}
	cout<<"\n\n\n\n\n\n\n\n\n\n\n __     __           _                    \n";
	cout<<" \\ \\   / /          | |                   \n";
	cout<<"  \\ \\_/ /__  _   _  | |     ___  ___  ___ \n";
	cout<<"   \\   / _ \\| | | | | |    / _ \\/ __|/ _ \\\n";
	cout<<"    | | (_) | |_| | | |___| (_) \\__ \\  __/\n";
	cout<<"    |_|\\___/ \\__,_| |______\\___/|___/\\___|\n";  
	p = e = NULL;
}
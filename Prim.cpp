#include <iostream>
#include <vector>
#include <time.h>
#include <Windows.h>
#define WALL 0
#define PATH 1
#define PLAYER 2
#define GOAL 3
using namespace std;



struct Node
{	
	int x;
	int y;
	bool visited;
	int type;
	Node *parent;
	void open(){
	}
}*map[25][75];

vector<Node*> asu;

void anjingMap(){
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<75;j++)
		{
			if(map[i][j]->type==WALL){
				cout<<(char)219;
			}else if(map[i][j]->type==PLAYER){
				cout<<(char)2;
			}else if(map[i][j]->type==PATH){
				cout<<' ';
			}
		}
		cout << endl;
	}
}

int main()
{
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<75;j++)
		{
			map[i][j]=(Node *)malloc(sizeof(Node));
			map[i][j]->x=j;
			map[i][j]->y=i;
			map[i][j]->type= WALL;
			map[i][j]->visited=false;
		}
	}
	anjingMap();
	
	

	asu.push_back(map[13][36]);

	map[13][36]->type=PLAYER;

	while(!asu.empty()){
		int index = rand()%asu.size();
		Node * asusementara=asu[index];
		asu.erase(asu.begin()+index);
		//kiri
		if(asusementara->x-2>0&&!map[asusementara->y][asusementara->x-2]->visited){
			asu.push_back(map[asusementara->y][asusementara->x-2]);
			map[asusementara->y][asusementara->x-2]->type=PATH;
			map[asusementara->y][asusementara->x-2]->visited=true;
			map[asusementara->y][asusementara->x-1]->type=PATH;
			map[asusementara->y][asusementara->x-1]->visited=true;
			//cout<<"kiri"<<endl;
		}
		//kanan
		if(asusementara->x+2<74&&!map[asusementara->y][asusementara->x+2]->visited){
			asu.push_back(map[asusementara->y][asusementara->x+2]);
			map[asusementara->y][asusementara->x+2]->type=PATH;
			map[asusementara->y][asusementara->x+2]->visited=true;
			map[asusementara->y][asusementara->x+1]->type=PATH;
			map[asusementara->y][asusementara->x+1]->visited=true;
			//cout<<"kanan"<<endl;
		}
		//atas
		if(asusementara->y-2>0&&!map[asusementara->y-2][asusementara->x]->visited){
			asu.push_back(map[asusementara->y-2][asusementara->x]);
			map[asusementara->y-2][asusementara->x]->type=PATH;
			map[asusementara->y-2][asusementara->x]->visited=true;
			map[asusementara->y-1][asusementara->x]->type=PATH;
			map[asusementara->y-1][asusementara->x]->visited=true;
			//cout<<"atas"<<endl;
		}
		//bawah
		if(asusementara->y+2<24&&!map[asusementara->y+2][asusementara->x]->visited){
			asu.push_back(map[asusementara->y+2][asusementara->x]);
			map[asusementara->y+2][asusementara->x]->type=PATH;
			map[asusementara->y+2][asusementara->x]->visited=true;
			map[asusementara->y+1][asusementara->x]->type=PATH;
			map[asusementara->y+1][asusementara->x]->visited=true;
			//cout<<"bawah"<<endl;
		}
		asusementara->visited=true;
		system("cls");
		Sleep(2);
		anjingMap();
		
		//cin.get();
		cout<<endl;
		cout<<endl;
	}
	

	cin.get();
	return 0;
}
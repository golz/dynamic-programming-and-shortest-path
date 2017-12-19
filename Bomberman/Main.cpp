#include "Header.h"

void generateMap();
void play();
void game()
{
	system("cls");
	for(int i = 0; i<HEIGHT; i++)
		for(int j = 0; j<WIDTH; j++)
			map[i][j] = WALL;

	for(int i = 0; i<HEIGHT; i++)
	{
		for(int j = 0; j<WIDTH; j++)
		{
			cout<< (char)219;
		}
	}
	generateMap();
	DWORD tid;
	DWORD etd;
	enemyHandle = CreateThread(0,0,threadEnemy,NULL,0,&etd);
	handle = CreateThread(0,0,run,NULL,0,&tid);
	play();
}
void prim(){
	vector<Point*> points;
	Point *start = new Point(rand()%WIDTH, rand()%HEIGHT, NULL);
	Point *end = NULL;
	p = new Player(start->x,start->y,1);
	p->print();
	for(int i = -1; i<=1; i++)
	{
		for(int j = -1; j<=1; j++)
		{
			if(i == 0 && j == 0 || i != 0 && j != 0)
				continue;

			if(start->y+i < 0 || start->y+i >= HEIGHT || start->x+j < 0 || start->x+j >= WIDTH)
				continue;

			points.push_back(new Point(start->x + j, start->y + i, start));
		}
	}
	while(!points.empty())
	{
		p->print();
		int randIndex = rand()%points.size();
		Point* curr = points[randIndex];
		Point* opp = curr->opposite();
		points.erase(points.begin() + randIndex);

		if(curr->y < 0 || curr->y >= HEIGHT || curr->x < 0 || curr->x >= WIDTH || opp->y < 0 || opp->y >= HEIGHT || opp->x < 0 || opp->x >= WIDTH)
			continue;

		if(map[curr->y][curr->x] != PATH && map[opp->y][opp->x] != PATH)
		{
			map[curr->y][curr->x] = PATH;
			map[opp->y][opp->x] = PATH;
			gotoxy(curr->x, curr->y);
			cout<< ' ';
			gotoxy(opp->x, opp->y);
			cout<< ' ';
			gotoxy(0,0);

			for(int i = -1; i<=1; i++)
			{
				for(int j = -1; j<=1; j++)
				{
					if((i == 0 && j == 0 )||( i != 0 && j != 0))
						continue;

					if(opp->y + i < 0 || opp->y + i >= HEIGHT || opp->x + j < 0 || opp->x + j >= WIDTH)
						continue;
					if(map[opp->y + i][opp->x + j] == 0)
						continue;

					points.push_back(new Point(opp->x + j, opp->y + i, opp));
				}
			}
			Sleep(0);
		}
		end = opp;
	}
	
	map[start->y][start->x]=PLAYER;
	map[end->y][end->x] = 2;
	gotoxy(end->x, end->y);
	e = new Player(end->x,end->y,ENEMY);
	e->kind = 2;
	e->print();
}
void av(){
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			int keputusan = rand()%2;
			if(keputusan == PATH && map[i][j]==WALL){
				gotoxy(j,i);
				cout<<' ';
				map[i][j]=PATH;
				Sleep(0);
			}
		}
	}
}
void splash(){
	cout<<"\n\n\n\n\n\t  ____                  _                             __      __"<<endl;
	cout<<"\t |  _ \\                | |                           /\\ \\    / /"<<endl;
	cout<<"\t | |_) | ___  _ __ ___ | |__   ___ _ __ _ __ ___    /  \\ \\  / / "<<endl;
	cout<<"\t |  _ < / _ \\| '_ ` _ \\| '_ \\ / _ \\ '__| '_ ` _ \\  / /\\ \\ \\/ /  "<<endl;
	cout<<"\t | |_) | (_) | | | | | | |_) |  __/ |  | | | | | |/ ____ \\  /   "<<endl;
	cout<<"\t |____/ \\___/|_| |_| |_|_.__/ \\___|_|  |_| |_| |_/_/    \\_\\/    "<<endl;
	printf("%44s","By AV15-1\n");
	printf("%55s","Press Any key to continue...\n");
	char input = _getch();
}
void play(){
	char input;
	while(masihmain){
		input = _getch();
		if(input==0 || input==224){
			input = _getch();
		}
		if(input==UP){
			p->move(UP);
		}else if(input==DOWN){
			p->move(DOWN);
		}else if(input==RIGHT){
			p->move(RIGHT);
		}else if(input==LEFT){
			p->move(LEFT);
		}else if(input==SPACE){
			p->dropBomb();
		}
	}
}
void generateMap()
{
	prim();
	av();
}
void about(){
	system("cls");
	cout<<"\n\n\t  ____                  _                             __      __"<<endl;
	cout<<"\t |  _ \\                | |                           /\\ \\    / /"<<endl;
	cout<<"\t | |_) | ___  _ __ ___ | |__   ___ _ __ _ __ ___    /  \\ \\  / / "<<endl;
	cout<<"\t |  _ < / _ \\| '_ ` _ \\| '_ \\ / _ \\ '__| '_ ` _ \\  / /\\ \\ \\/ /  "<<endl;
	cout<<"\t | |_) | (_) | | | | | | |_) |  __/ |  | | | | | |/ ____ \\  /   "<<endl;
	cout<<"\t |____/ \\___/|_| |_| |_|_.__/ \\___|_|  |_| |_| |_/_/    \\_\\/    "<<endl;
	printf("%44s","By AV15-1\n");
	cout<<"BombermAV is a strategic, maze-based video game that inspired from this complicated life."<<endl;
	cout<<"How to play : "<<endl;
	cout<<"Press arrow button to move the player"<<endl;
	cout<<"Press space button to drop the bomb"<<endl;
}
void menu(){
	int menu=0;
	do{
		gotoxy(0,0);
		vBomb.clear();
		system("cls");
		for(int i=0;i<25;i++)cout<<endl;
		cout<<"BombermAV"<<endl<<"1. Play"<<endl<<"2. About"<<endl<<"3. Exit"<<endl;
		do{
			while(true){
				cout<<">> ";
				cin>>menu;
				if(!cin){
					cin.clear();
					cin.ignore();
					cin.get();
					cin.sync();
				}else{
					cin.get();
					cin.sync();
					break;
				}
			}
		}while(menu<1||menu>3);
		switch(menu){
		case 1:
			masihmain = 1;
			game();
			break;
		case 2:
			about();
			break;
		case 3:
			exit(0);
			break;
		}
		cin.get();
	}while(menu!=3);
}
int main(){
	srand(time(NULL));
	splash();
	while(1){
		menu();
	}
	getchar();
	return 0;
}
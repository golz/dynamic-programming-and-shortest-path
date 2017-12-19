#include<stdio.h>
#include<vector>

using namespace std;

#define HEIGHT 17
#define WIDTH 30

struct node{
	int x, y;
	node(){};
	node(int x, int y) : x(x), y(y){};
} came_from[HEIGHT][WIDTH];

bool is_closed[HEIGHT][WIDTH];
int f[HEIGHT][WIDTH];
int g[HEIGHT][WIDTH];
int h[HEIGHT][WIDTH];

node start;
node finish;

int map[HEIGHT][WIDTH] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1},
	{1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,0,0,0,0,1},
	{1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,1,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0,1,0,1,0,1},
	{1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1},
	{1,0,0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,1,0,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void printMap(){
	for(int i=0;i<HEIGHT;i++){
		for(int j=0;j<WIDTH;j++){
			char c;

			if(i == start.y && j == start.x)
				c = 's';
			else if(i == finish.y && j == finish.x)
				c = 'e';
			else{
				switch(map[i][j]){
					case 2: c = '.'; break;
					case 1: c = '#'; break;
					case 0: c = ' '; break;
				}
			}

			printf("%c", c);
		}
		puts("");
	}
}

int heuristic(int x1, int y1, int x2, int y2){
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int heuristic(node n1, node n2){
	return (n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y);
}

bool is_neigh_valid(int x, int y){
	if(x < 0 || x >= WIDTH)
		return false;
	if(y < 0 || y >= HEIGHT)
		return false;
	if(map[y][x] == 1)
		return false;
	if(is_closed[y][x] == 1)
		return false;
	return true;
}

void backtrack_path(int x, int y){
	map[y][x] = 2;
	if( came_from[y][x].x != -1){
		backtrack_path(came_from[y][x].x,came_from[y][x].y);
	}
}

bool a_star(){
	vector<node> open_list;
	open_list.push_back(start);
	came_from[start.y][start.x].x = -1;
	came_from[start.y][start.x].y = -1;
	h[start.y][start.x] = heuristic(start, finish);
	g[start.y][start.x] = 0;
	f[start.y][start.x] = g[start.y][start.x] + h[start.y][start.x];

	while(open_list.size() > 0){
		//f terkecil, sebagai curr
		int nodeIdx = 0;
		node curr = open_list.at(0);
		for(int i=1;i<open_list.size();i++){
			node n = open_list.at(i);
			if(f[n.y][n.x] < f[curr.y][curr.x]){
				curr = n;
				nodeIdx = i;
			}
		}

		if(curr.x == finish.x && curr.y == finish.y){
			backtrack_path(curr.x, curr.y);
			return true;
		}

		int x = curr.x;
		int y = curr.y;

		int nx, ny;

		//tetangga kiri
		nx = x-1;
		ny = y;
		if( is_neigh_valid(nx,ny) ){ 
			int temp_g = g[y][x] + 1;
			if(g[ny][nx] != 9999 && g[ny][nx] > temp_g ){
				g[ny][nx] = temp_g;
				f[ny][nx] = g[ny][nx] + h[ny][nx];
				came_from[ny][nx] = node(x,y);
			} else if(g[ny][nx] == 9999){
				g[ny][nx] = temp_g;
				h[ny][nx] = heuristic( node(nx,ny) , finish );
				f[ny][nx] = g[ny][nx] + h[ny][nx];
				came_from[ny][nx] = node(x,y);
				open_list.push_back(node(nx,ny));
			}
		}

		//tetangga kanan
		nx = x+1;
		ny = y;
		if( is_neigh_valid(nx,ny) ){ 
			int temp_g = g[y][x] + 1;
			if(g[ny][nx] != 9999 && g[ny][nx] > temp_g ){
				g[ny][nx] = temp_g;
				f[ny][nx] = g[ny][nx] + h[ny][nx];
				came_from[ny][nx] = node(x,y);
			} else if(g[ny][nx] == 9999){
				g[ny][nx] = temp_g;
				h[ny][nx] = heuristic( node(nx,ny) , finish );
				f[ny][nx] = g[ny][nx] + h[ny][nx];
				came_from[ny][nx] = node(x,y);
				open_list.push_back(node(nx,ny));
			}
		}

		//tetangga bawah
		nx = x;
		ny = y+1;
		if( is_neigh_valid(nx,ny) ){ 
			int temp_g = g[y][x] + 1;
			if(g[ny][nx] != 9999 && g[ny][nx] > temp_g ){
				g[ny][nx] = temp_g;
				f[ny][nx] = g[ny][nx] + h[ny][nx];
				came_from[ny][nx] = node(x,y);
			} else if(g[ny][nx] == 9999){
				g[ny][nx] = temp_g;
				h[ny][nx] = heuristic( node(nx,ny) , finish );
				f[ny][nx] = g[ny][nx] + h[ny][nx];
				came_from[ny][nx] = node(x,y);
				open_list.push_back(node(nx,ny));
			}
		}

		//tetangga atas
		nx = x;
		ny = y-1;
		if( is_neigh_valid(nx,ny) ){ 
			int temp_g = g[y][x] + 1;
			if(g[ny][nx] != 9999 && g[ny][nx] > temp_g ){
				g[ny][nx] = temp_g;
				f[ny][nx] = g[ny][nx] + h[ny][nx];
				came_from[ny][nx] = node(x,y);
			} else if(g[ny][nx] == 9999){
				g[ny][nx] = temp_g;
				h[ny][nx] = heuristic( node(nx,ny) , finish );
				f[ny][nx] = g[ny][nx] + h[ny][nx];
				came_from[ny][nx] = node(x,y);
				open_list.push_back(node(nx,ny));
			}
		}

		is_closed[curr.y][curr.x] = true;
		open_list.erase(open_list.begin() + nodeIdx);
	}

	return false;
}

int main(){
	for(int i=0; i<HEIGHT; i++){
		for(int j=0; j<WIDTH; j++){
			g[i][j] = f[i][j] = 9999;
		}
	}
	start = node(1,1);
	finish = node(27,15);
	printf("%d\n", a_star() );
	printMap();
	getchar();
	return 0;
}
import java.util.ArrayList;
import java.util.Random;
class RecursiveBacktracker{
	final int WIDTH = 50;
	final int HEIGHT = 20;
	final int WALL = 1;
	final int PATH = 0;
	int unvisited = WIDTH * HEIGHT;
	class Vertex{
		Integer x;
		Integer y;
		Boolean visited;
		Integer status;
		public Vertex(Integer x, Integer y){
			this.x = x;
			this.y = y;
			this.visited = false;
		}
	}
	Vertex map[][] = new Vertex[HEIGHT][WIDTH];
	Random rand = new Random();
	ArrayList<Vertex> stack = new ArrayList<Vertex>();
	public void fill(){
		for(int i=0;i<HEIGHT;i++){
			for(int j=0;j<WIDTH;j++){
				map[i][j] = new Vertex(j,i);
				map[i][j].status=WALL;
			}
		}
	}
	public void render(){
		for(int i=0;i<25;i++)System.out.println();
		for(int i=0;i<HEIGHT;i++){
			for(int j=0;j<WIDTH;j++){
				int a = map[i][j].visited?1:-1;
				switch(a){
				case -1:
					System.out.print("#");
					break;
				case 1:
					System.out.print(" ");
				break;
				}
			}
			System.out.println();
		}
	}

	public void checkNeigh(Vertex curr){
		try{
			int random = rand.nextInt(4);
			unvisited--;
			map[curr.y][curr.x].visited = true;
			map[curr.y][curr.x].status = PATH;
			render();
			try{Thread.sleep(100);}catch(Exception e){}
			switch(random){
				case 0:
				//kiri
				if(!map[curr.y][curr.x-1].visited && !map[curr.y][curr.x-2].visited ){
					map[curr.y][curr.x-1].visited = true;
					map[curr.y][curr.x-1].status = PATH;
					checkNeigh(map[curr.y][curr.x-2]);
				}
				//atas
				if(!map[curr.y-1][curr.x].visited && !map[curr.y-2][curr.x].visited ){
					map[curr.y-1][curr.x].visited = true;
					map[curr.y-1][curr.x].status = PATH;
					checkNeigh(map[curr.y-2][curr.x]);
				}
				//bawah
				if(!map[curr.y+1][curr.x].visited  && !map[curr.y+2][curr.x].visited){
					map[curr.y+1][curr.x].visited = true;
					map[curr.y+1][curr.x].status = PATH;
					checkNeigh(map[curr.y+2][curr.x]);
				}
				//kanan
				if(!map[curr.y][curr.x+1].visited && !map[curr.y][curr.x+2].visited ){
					map[curr.y][curr.x+1].visited = true;
					map[curr.y][curr.x+1].status = PATH;
					checkNeigh(map[curr.y][curr.x+2]);
				}
				break;
				case 1:
				//bawah
				if(!map[curr.y][curr.x+1].visited && !map[curr.y][curr.x+2].visited ){
					map[curr.y][curr.x+1].visited = true;
					map[curr.y][curr.x+1].status = PATH;
					checkNeigh(map[curr.y][curr.x+2]);
				}
				//kanan
				if(!map[curr.y+1][curr.x].visited  && !map[curr.y+2][curr.x].visited){
					map[curr.y+1][curr.x].visited = true;
					map[curr.y+1][curr.x].status = PATH;
					checkNeigh(map[curr.y+2][curr.x]);
				}
				//atas
				if(!map[curr.y-1][curr.x].visited && !map[curr.y-2][curr.x].visited ){
					map[curr.y-1][curr.x].visited = true;
					map[curr.y-1][curr.x].status = PATH;
					checkNeigh(map[curr.y-2][curr.x]);
				}
				//kiri
				if(!map[curr.y][curr.x-1].visited && !map[curr.y][curr.x-2].visited ){
					map[curr.y][curr.x-1].visited = true;
					map[curr.y][curr.x-1].status = PATH;
					checkNeigh(map[curr.y][curr.x-2]);
				}
				break;
				case 2:
				//kanan
				if(!map[curr.y+1][curr.x].visited  && !map[curr.y+2][curr.x].visited){
					map[curr.y+1][curr.x].visited = true;
					map[curr.y+1][curr.x].status = PATH;
					checkNeigh(map[curr.y+2][curr.x]);
				}
				//bawah
				if(!map[curr.y][curr.x+1].visited && !map[curr.y][curr.x+2].visited ){
					map[curr.y][curr.x+1].visited = true;
					map[curr.y][curr.x+1].status = PATH;
					checkNeigh(map[curr.y][curr.x+2]);
				}
				//kiri
				if(!map[curr.y][curr.x-1].visited && !map[curr.y][curr.x-2].visited ){
					map[curr.y][curr.x-1].visited = true;
					map[curr.y][curr.x-1].status = PATH;
					checkNeigh(map[curr.y][curr.x-2]);
				}
				//atas
				if(!map[curr.y-1][curr.x].visited && !map[curr.y-2][curr.x].visited ){
					map[curr.y-1][curr.x].visited = true;
					map[curr.y-1][curr.x].status = PATH;
					checkNeigh(map[curr.y-2][curr.x]);
				}
				break;
				case 3:
				//kanan
				if(!map[curr.y][curr.x+1].visited && !map[curr.y][curr.x+2].visited ){
					map[curr.y][curr.x+1].visited = true;
					map[curr.y][curr.x+1].status = PATH;
					checkNeigh(map[curr.y][curr.x+2]);
				}
				//kiri
				if(!map[curr.y][curr.x-1].visited && !map[curr.y][curr.x-2].visited ){
					map[curr.y][curr.x-1].visited = true;
					map[curr.y][curr.x-1].status = PATH;
					checkNeigh(map[curr.y][curr.x-2]);
				}
				//bawah
				if(!map[curr.y+1][curr.x].visited  && !map[curr.y+2][curr.x].visited){
					map[curr.y+1][curr.x].visited = true;
					map[curr.y+1][curr.x].status = PATH;
					checkNeigh(map[curr.y+2][curr.x]);
				}
				//atas
				if(!map[curr.y-1][curr.x].visited && !map[curr.y-2][curr.x].visited ){
					map[curr.y-1][curr.x].visited = true;
					map[curr.y-1][curr.x].status = PATH;
					checkNeigh(map[curr.y-2][curr.x]);
				}
				break;
			}
		}catch(Exception e){
			return;
		}
	}

	public RecursiveBacktracker(){
		fill();
		//while(unvisited!=0){
			Vertex start = map[rand.nextInt(HEIGHT)][rand.nextInt(WIDTH)];
			start.visited = true;
			unvisited--;
			start.status = PATH;
			checkNeigh(start);
		//}
		render();
	}
	public static void main(String [] args){
		new RecursiveBacktracker();
	}
}
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.LayoutManager;
import java.util.ArrayList;
import java.util.Collections;


import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Main extends JFrame{
	AssetManager asset = AssetManager.getInstance();
	int x = 100;
	int y = 100;
	private ArrayList<Vertex> stack = new ArrayList<Vertex>();
	private ArrayList<Vertex> jalan = new ArrayList<Vertex>();
	private final int DIST_X = 1, DIST_Y = 2;
	private boolean[][] status = new boolean[19][57];
	private boolean[][] path = new boolean[19][57];
	private boolean notFinished = true;
	private Vertex start=null, finish=null;
	public Main() {
		try {
			asset.playAudio();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		setSize(900,500);
		setLocationRelativeTo(null);
		setVisible(true);
		setResizable(false);
		setTitle("Dijkstra");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		doDijkstra();
		repaint();
	}
	private void open(Vertex open){
		if(notFinished){
			if(asset.map[open.x][open.y]==1)
				return;
			else if(status[open.x][open.y])
				return;
			else{
				status[open.x][open.y]=true;
				stack.add(open);
				if(open.x == DIST_X && open.y == DIST_Y){
					finish = open;
					notFinished = false;
				}
			}
		}
	}
	private void doDijkstra() {
		// TODO Auto-generated method stub
		start = new Vertex(17, 54, null);
		stack.add(start);
		do{
			//DFS
			//Vertex curr = stack.get(stack.size()-1);
			//BFS
			Vertex curr = stack.get(0);
			open(new Vertex(curr.x,curr.y-1,curr));
			open(new Vertex(curr.x-1,curr.y,curr));
			open(new Vertex(curr.x,curr.y+1,curr));
			open(new Vertex(curr.x+1,curr.y,curr));
			stack.remove(curr);
			ulang();
		}while(notFinished);
		backtrack();
	}
	private void swap(int x, int y, int oldx, int oldy){
		int temp = asset.map[oldx][oldy];
		asset.map[oldx][oldy] = asset.map[x][y];
		asset.map[x][y] = temp;
	}
	private void ulang() {
		// TODO Auto-generated method stub
		repaint();
		try {
			Thread.sleep(25);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	private void backtrack() {
		// TODO Auto-generated method stub
		Vertex curr = finish;
		while(curr.parent!=null){
			jalan.add(curr);
			curr=curr.parent;
		}
		for(int i=0; i<jalan.size(); i++){
			int x = jalan.get(i).x;
			int y = jalan.get(i).y;
			path[x][y]=true;
			ulang();
		}
		Collections.reverse(jalan);
		jalan.get(0).y=54;
		for(int i=0; i<jalan.size()-1; i++){
			swap(jalan.get(i+1).x,jalan.get(i+1).y,jalan.get(i).x,jalan.get(i).y);
			ulang();
		}
	}
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		Graphics2D g2d = (Graphics2D)g;
		for(int i=0;i<asset.map[0].length;i++){
			for(int j=0;j<asset.map.length;j++){
				if(asset.map[j][i]==1){
					g2d.setColor(Color.RED);
					g2d.fillRect(15*i+20, 15*j+100, 15, 15);
				}else if(asset.map[j][i]==3){
					g2d.setColor(new Color(0x000));
					g2d.fillRect(15*i+20, 15*j+100, 15, 15);
					g2d.setColor(Color.YELLOW);
					g2d.fillOval(15*i+20, 15*j+100, 15, 15);
				}else if(asset.map[j][i]==2 && (status[j][i])){
					g2d.setColor(Color.BLUE);
					g2d.fillRect(15*i+20, 15*j+100, 15, 15);
					g2d.setColor(Color.GREEN);
					g2d.fillOval(15*i+20, 15*j+100, 15, 15);
				}else if(asset.map[j][i]==2 && (path[j][i])){
					g2d.setColor(Color.GRAY);
					g2d.fillRect(15*i+20, 15*j+100, 15, 15);
					g2d.setColor(Color.GREEN);
					g2d.fillOval(15*i+20, 15*j+100, 15, 15);
				}else if(asset.map[j][i]==2){
					g2d.setColor(new Color(0x000));
					g2d.fillRect(15*i+20, 15*j+100, 15, 15);
					g2d.setColor(Color.GREEN);
					g2d.fillOval(15*i+20, 15*j+100, 15, 15);
				}else if(path[j][i]){
					g2d.setColor(Color.GRAY);
					g2d.fillRect(15*i+20, 15*j+100, 15, 15);
				}else if(status[j][i]){
					g2d.setColor(Color.BLUE);
					g2d.fillRect(15*i+20, 15*j+100, 15, 15);
				}else if(asset.map[j][i]==0){
					g2d.setColor(new Color(0x000));
					g2d.fillRect(15*i+20, 15*j+100, 15, 15);
				}

			}
		}
	}
	public static void main(String[] args) {
		new Main();
	}
}
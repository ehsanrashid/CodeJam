import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;
import java.util.StringTokenizer;

public class Main 
{
	Stack<Integer>[] blocks;
	int[] pos;

	public static void main(String[] args) throws IOException 
	{
		Main p = new Main();
		p.go();
		p.print();
	}

	private void print() 
	{
		for(int i=0; i<blocks.length; i++){
			System.out.println(blockToString(i));
		}

	}

	private String blockToString(int i) {

		String ans = "";

		while(!blocks[i].isEmpty())
			ans = " "+ blocks[i].pop() + ans;

		ans = i+ ":" + ans;

		return ans;
	}

	@SuppressWarnings("unchecked")
	public void go() throws NumberFormatException, IOException {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		int N = Integer.parseInt(in.readLine());
		blocks = new Stack[N];
		pos = new int[N];
		for (int i = 0; i < N; i++) {
			blocks[i] = new Stack<Integer>();
			blocks[i].push(i);
			pos[i] = i;
		}
		String l = "";
		while (!(l = in.readLine()).equals("quit")) {
			StringTokenizer tokens = new StringTokenizer(l);
			String action = tokens.nextToken();
			int a = Integer.parseInt(tokens.nextToken());
			String type = tokens.nextToken();
			int b = Integer.parseInt(tokens.nextToken());

			if(a==b || pos[a] ==pos[b]) continue;
			if (action.equals("move")) {

				if (type.equals("onto"))
					moveOnto(a, b);
				else if (type.equals("over"))
					moveOver(a, b);

			} else if (action.equals("pile")) {
				if (type.equals("onto"))
					pileOnto(a, b);

				else if (type.equals("over"))
					pileOver(a, b);
			}

		}

	}

	public void moveOnto(int a, int b) {

		clearAbove(b);
		moveOver(a, b);
	}

	public void moveOver(int a, int b) {
		clearAbove(a);
		blocks[pos[b]].push(blocks[pos[a]].pop());
		pos[a] = pos[b];
	}

	public void pileOnto(int a, int b) {
		clearAbove(b);
		pileOver(a, b);
	}

	public void pileOver(int a, int b) {

		Stack<Integer> aPile = new Stack<Integer>();
		while (blocks[pos[a]].peek() != a)
			aPile.push(blocks[pos[a]].pop());

		aPile.push(blocks[pos[a]].pop());

		while (!aPile.isEmpty()) {
			int top = aPile.pop();
			blocks[pos[b]].push(top);
			pos[top] = pos[b];
		}
	}

	public void clearAbove(int x) {
		while (blocks[pos[x]].peek() != x)
			returnHome(blocks[pos[x]].pop());
	}

	private void returnHome(Integer x) {
		while (!blocks[x].isEmpty()) {
			returnHome(blocks[x].pop());
		}
		blocks[x].push(x);
		pos[x] = x;
	}
}

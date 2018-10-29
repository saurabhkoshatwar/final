import java.util.*;
class EightPuzzle{ 
    
    public static int findMin(int[][] goal,ArrayList<int[][]> open)
    {
        int min=cost(open.get(0),goal) + gn.get(0);
        int[][] st = open.get(0);
        for(int i=0;i<open.size();i++)
        {
            if(cost(open.get(i),goal)+gn.get(i)<min)
            {
                min = cost(open.get(i),goal)+gn.get(i);
                st = open.get(i);
            }
        }
        return st;
    }
        for(int i=0;i<open.size();i++)
        {
            int gn=0;
            char[] path = pathStored.get(i).toCharArray();
            for(int j=0;j<path.length-1;j++)
                gn=gn + adjmat[path[j]-65][path[j+1]-65];

                 if(heuristics[open.get(i)]+gn < min)
                {
                    min =heuristics[open.get(i)]+gn;
                    index =i;
                }
        }

   
     
    	public static boolean match(int[][] child,int[][] goal) {
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++)
				if(child[i][j]!=goal[i][j])
					return false;
		}
		return true;
	}
	
	public static boolean feasible(int[][] child,String move) {
		for(int i=0;i<3;i++) {
			for(int j=0;j<3;j++)
				if(child[i][j]==0) {
					if(move.equals("moveright"))
						if(j==2)
							return false;
					if(move.equals("moveleft"))
						if(j==0)
							return false;
					if(move.equals("moveup"))
						if(i==0)
							return false;
					if(move.equals("movedown"))
						if(i==2)
							return false;
				}
		}
		return true;
	}
	
	public static int cost(int[][] state,int[][] goal) {
	    int c=0;
	    for(int i=0;i<3;i++)
	      for(int j=0;j<3;j++)
	        if(state[i][j]!=0 && state[i][j]!= goal[i][j])
	           c++;
	    return c;
	}
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        int n;
        System.out.println("Enter Number of Nodes");
        n = sc.nextInt();
        int[][] adjmat = new int[n][n];
        ArrayList<Integer> open = new ArrayList<Integer>();
        ArrayList<Integer> closed = new ArrayList<Integer>();
        ArrayList<String> pathStored = new ArrayList<String>();

        // int[] parent = new int[n];

        System.out.println("Enter Edges");
        System.out.print(" ");
        for(int i=0;i<n;i++)
            System.out.print((char)(65+i)+"  ");

        System.out.println();
        for(int i=0;i<n;i++)
        {
            System.out.print((char)(65+i));
            for(int j=0;j<n;j++)
            {
                adjmat[i][j] = sc.nextInt();
            }
        }
       
        System.out.println("Enter Goal Node");
        char Goal = sc.next().charAt(0);
        int goalno = (int)(Goal) - 65;

        int[] heuristics = new int[n];
        for(int i=1;i<n;i++)
        {
            System.out.println("Enter heuristic for node "+(char)(65+i));
            heuristics[i] = sc.nextInt();
        }

        int source=0;
        open.add(source);
        pathStored.add(Character.toString((char)(source+65)));
        int currIndex=0;
        while(!open.isEmpty())
        {
             System.out.println("Path:"+pathStored.clone());
           currIndex = findMin(open,heuristics,adjmat,pathStored);
           int curr = open.get(currIndex);
           closed.add(curr);
           if(curr ==goalno)
            break;

            open.remove(currIndex);
            for(int i=0;i<n;i++)
            {
                if(adjmat[curr][i]!=0 && adjmat[curr][i]!=999 && !closed.contains(i))
                {
                    open.add(i);
                    pathStored.add( pathStored.get(currIndex)+Character.toString((char)(i+65)) );
                    
                }
                
            }
            pathStored.remove(currIndex);
          
        }

        System.out.println("Path: "+pathStored.get(currIndex));
        
        sc.close();

    }
}
import java.util.*;
class BFS{ 
    
    public static int findMin(ArrayList<Integer> open,int[] heuristics)
    {
        int min=999;
        int index=-1;
        for(int i=0;i<open.size();i++)
        {
            if(heuristics[open.get(i)] < min)
            {
                min =heuristics[open.get(i)];
                index = open.get(i);
            }
        }

        return index;
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
        int[] parent = new int[n];

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

        while(!open.isEmpty())
        {
           int curr = findMin(open,heuristics);
           closed.add(curr);
           if(curr==goalno)
            break;

            open.remove(new Integer(curr));

            for(int i=0;i<n;i++)
            {
                if(adjmat[curr][i]!=0 && adjmat[curr][i]!=999 && !closed.contains(i) && !open.contains(i))
                {
                    open.add(i);
                    parent[i] = curr;
                }
            }
           

        }

        ArrayList<Character> Actualpath = new ArrayList<Character>();
        int path = goalno;
        while(path!=source)
        {
            Actualpath.add((char)(65+path));
            path = parent[path];
        }
        Actualpath.add((char)(65+path));

        for(int i=Actualpath.size()-1;i>=0;i--)
        {
            System.out.print(Actualpath.get(i)+" ");
        }
        
        sc.close();

    }
}
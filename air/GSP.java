import java.util.*;

class GSP{
    int k;

    int[][] on;
    int[] ontable;
    int[] clear;
    char holding;
    int armempty;

    char[] alphabet;

    Stack<String> gstack = new Stack<String>();
    ArrayList<String> actions = new ArrayList<String>();

    Scanner sc = new Scanner(System.in);
    String start,goal;
    GSP(int n)
    {
        k = n;
        on = new int[n][n];
        ontable = new int[n];
        clear  = new int[n];
        armempty=1;
        alphabet = "abcdefghijklmnopqrtsuvwxyz".toCharArray();

    }

    	public void input()
	{

		// System.out.println("Enter Start State");
		// start = sc.next();
		// System.out.println("Enter Goal State");
		// goal = sc.next();
		start = "ontable(a)^ontable(c)^on(b,a)^clear(b)^clear(c)^armempty";
		goal = "clear(a)^ontable(c)^on(a,b)^on(b,c)^armempty";

		// start = "ontable(b)^ontable(c)^on(d,b)^on(a,c)^clear(d)^clear(a)^armempty";	
		// goal =  "ontable(a)^on(b,a)^on(c,b)^on(d,c)^clear(d)^armempty";	
	};

    void set_initial()
    {
        String sg[] = start.split("['^']");
        for(int i=0;i<sg.length;i++)
        {
            if(sg[i].contains("ontable"))
            {
                ontable[sg[i].charAt(8)%97] = 1;
            }
            else if(sg[i].contains("on"))
            {
                on[sg[i].charAt(3)%97][sg[i].charAt(5)%97] = 1;
            }
            else if(sg[i].contains("clear"))
            {
                clear[sg[i].charAt(6)%97] = 1;
            }
            else if(sg[i].contains("holding"))
            {
                holding = sg[i].charAt(8);
            }
            else if(sg[i].contains("armempty"))
            {
                armempty = 1;
            }
            
        }
    }
     void pushAction(String pred)
    {
            if(pred.contains("ontable"))
            {
                gstack.push("putdown("+pred.charAt(8)+")");

                gstack.push("holding("+pred.charAt(8)+")");
                
            }
            else if(pred.contains("on"))
            {
                gstack.push("stack("+pred.charAt(3)+","+pred.charAt(5)+")");
                
                gstack.push("clear("+pred.charAt(5)+")^"+"holding("+pred.charAt(3)+")");
            }
            else if(pred.contains("clear"))
            {
                int i;
                for(i=0;i<k;i++)
                {
                    if(on[i][pred.charAt(6)%97]==1)
                    {
                        break;
                    }
                }
                gstack.push("unstack("+alphabet[i]+","+pred.charAt(6)+")");

                gstack.push("on("+alphabet[i]+","+pred.charAt(6)+")^clear("+alphabet[i]+")^armempty");
                
            }
            else if(pred.contains("holding"))
            {
                if(ontable[pred.charAt(8)%97]==1)
                {
                    gstack.push("pickup("+pred.charAt(8)+")");

                    gstack.push("ontable("+pred.charAt(8)+")clear("+pred.charAt(8)+")^armempty");
                }
                else{
                    int i;
                    for(i=0;i<k;i++)
                    {
                        if(on[pred.charAt(8)%97][i]==1)
                        {
                            break;
                        }
                    }
                    gstack.push("unstack("+pred.charAt(8)+","+alphabet[i]+")");

                    gstack.push("on("+pred.charAt(8)+","+alphabet[i]+")^clear("+pred.charAt(8)+")^armempty");
                    
                }
               
            }
            else if(pred.contains("armempty"))
            {
                gstack.push("putdown("+holding+")");

                gstack.push("holding("+holding+")");
                
            }

    }

     boolean check(String pred)
    {
        if(pred.contains("^"))
        {
            String sim[] = pred.split("['^']");

            for(int i=0;i<sim.length;i++)
            {
                if(!check_simple(sim[i]))
                    return false;
            }
            return true;           
        }
        else{
            return check_simple(pred);
        }
    }

     boolean check_simple(String pred)
    {
            if(pred.contains("ontable") && ontable[pred.charAt(8)%97] == 1)
            {
                return true;   
            }
            else if(pred.contains("on") && on[pred.charAt(3)%97][pred.charAt(5)%97] == 1)
            {
                return true;
            }
            else if(pred.contains("clear") && clear[pred.charAt(6)%97] == 1)
            {
                return true;   
            }
            else if(pred.contains("holding") && holding == pred.charAt(8))
            {
                return true;
            }
            else if(pred.contains("armempty") &&  armempty == 1)
            {
               return true;
            }
            return false;
               
    }

    public void doAction(String action)
    {
        if(action.contains("unstack"))
        {
            
            clear[action.charAt(10)%97] = 1;
            holding = action.charAt(8);

            on[action.charAt(8)%97][action.charAt(10)%97]=0;
            armempty = 0;
        }
        else if(action.contains("stack"))
        {

            on[action.charAt(6)%97][action.charAt(8)%97]=1;
            armempty = 1;
            clear[action.charAt(6)%97] = 1;

            clear[action.charAt(8)%97] = 0;
            holding =0;
        }
        else if(action.contains("putdown"))
        {

            ontable[action.charAt(8)%97]=1;
            armempty = 1;
            //clear[action.charAt(8)%97] = 1;

            
            holding =0;
        }
        else if(action.contains("pickup"))
        {

            holding = action.charAt(7);

            ontable[action.charAt(7)%97]=1;
            armempty = 0;
            //clear[action.charAt(7)%97] = 0;

        }
        
    }

    void plan()
    {
        int c= 0;
        gstack.push(goal);
        String curr;
        while(!gstack.isEmpty())
        {
            // if(c>15)
            // return;

            System.out.println(gstack.clone());
            curr = gstack.pop();
            System.out.println(gstack.clone());
            if(curr.contains("stack") || curr.contains("unstack") || curr.contains("pickup") || curr.contains("putdown"))
            {
                doAction(curr);
                actions.add(curr);
            }
            else if(!check(curr))
            {
                if(curr.contains("^"))
                {
                    gstack.push(curr);
                    String sub[] = curr.split("['^']");
                    for(int i=0;i<sub.length;i++)
                    {
                        gstack.push(sub[i]);
                    }
                }
                else{
                    gstack.push(curr);
                    pushAction(curr);
                }
            }
            c++;
        }
    }

    public void dispAction()
    {
        System.out.println("Actions: ");
        for(int i=0;i<actions.size();i++)
        {
            System.out.println(actions.get(i));
        }
    }
    public static void main(String args[])
    {
        Scanner s = new Scanner(System.in);
        System.out.println("Enter Num of Blocks");
        int n = s.nextInt();
        GSP p = new GSP(n);
        p.input();
        p.set_initial();
        p.plan();
        p.dispAction();
    }
}
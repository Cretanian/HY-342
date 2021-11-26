import java.util.*;
import java.io.*;
import java.util.Scanner;
import java.io.IOException; 
import java.io.FileWriter;

class Main 
{
    
    public static void FindForce(Body b, TreeNode n)
    {
        boolean iAmleaf = (n.getLLN() == null && n.getLN() == null && n.getRN() == null && n.getRRN() == null);
        
        if (iAmleaf && (n.getMyBody() == null || n.getMyBody() == b))
            return;
        
        double X = n.getX() - b.getX();
        double Y = n.getY() - b.getY();
        
        double distance = Math.sqrt(Math.pow(X, 2) + Math.pow(Y, 2));

        double range = 2 * b.getBoxR();

        boolean ContainsBody = n.myBodiesID.contains(b.getID());

        if ((((distance - range) > 0) && !ContainsBody) || iAmleaf)
        {
            assert (distance != 0) : "Bad Input: The distance between the points is Zero";

            double G = 6.67 * Math.pow((double)10, (double)-11);

            double F = G * ((n.getM() * b.getM()) / Math.pow(distance, 2));

            double Fx = (F * ((n.getX() - b.getX()) / distance));
            double Fy = (F * ((n.getY() - b.getY()) / distance));

            double Ax = Fx / b.getM();
            double Ay = Fy / b.getM();

            b.setAx(Ax);
            b.setAy(Ay);

        }
        else if (((distance - range) <= 0) || ContainsBody)
        {
            FindForce(b, n.getLLN());
            FindForce(b, n.getLN());
            FindForce(b, n.getRN());
            FindForce(b, n.getRRN());
        }
        else
            assert(false);
            
        return;
    }

    public static void createOutputFile(Vector<Body> myBodies, int NumberOfBodies, double RangeOfUniverse)
    {
        try 
        {
            PrintWriter printWriter = new PrintWriter(new FileWriter(new File("output.txt")));

            printWriter.print(NumberOfBodies + "\n");
            printWriter.print(RangeOfUniverse + "\n");
            for (int i = 0; i < myBodies.size(); ++i)
            {
                printWriter.print(
                    myBodies.get(i).getX() + " " +
                    myBodies.get(i).getY() + " " +
                    myBodies.get(i).getVx() + " " +
                    myBodies.get(i).getVy() + " " +
                    myBodies.get(i).getM() + " " +
                    myBodies.get(i).getName() + "\n"
                );
            }
            
            printWriter.close();
        } 
        catch (IOException e) 
        {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static int FindNumBodies(TreeNode node, Vector<Body> myBodies, Double X, Double Y,Double R, int flag)
    {
        int counter = 0;
        Double _X = 0.0;
        Double _Y = 0.0;
        int indic = 0;

        node.setMyBody(null);

        for(int i = 0; i < myBodies.size(); ++i)
        {
            _X = myBodies.get(i).getX();
            _Y = myBodies.get(i).getY();
            if(counter > 1)
                break;

            if( ((X - R) <= _X && _X <= (X + R)) && ((Y - R) <= _Y && _Y <= (Y + R)))
            {
                if ( myBodies.get(i).getMarked() == 0 ) 
                {
                    myBodies.get(i).setMarked(flag);
                    indic = i;
                    ++counter;
                }   
            } 
        }

        if (counter == 1)
        {
            myBodies.get(indic).setMarked(-1);
            myBodies.get(indic).setBoxsR(R);
            node.setMyBody(myBodies.get(indic));
            node.myBodiesID.addElement(indic);
        }

        return counter;
    }

    public static TreeNode createTree(TreeNode node, Vector<Body> myBodies, Double X, Double Y, Double R, int flag)
    {
        
        node = new TreeNode(X,Y,R);

        int numHelper = FindNumBodies(node, myBodies, X, Y, R, flag);
        
        if( -1 < numHelper && numHelper < 2)
        {
            node.setLLN(null);
            node.setLN(null);
            node.setRN(null);
            node.setRRN(null);
            node.setM(0.0);
            node.setX(0.0);
            node.setY(0.0);

            if (numHelper == 1)
            {
                node.setM(node.getMyBody().getM());
                node.setX(node.getMyBody().getX());
                node.setY(node.getMyBody().getY());
            }

            return node;
        }
        else
        {
            for (int i = 0; i < myBodies.size(); ++i) {
                if (myBodies.get(i).getMarked() != -1) {
                    myBodies.get(i).setMarked(0);
                }
            }

            Double newR  = R/2;
            node.setLLN(createTree(node.getLLN(),  myBodies,   X - newR, Y + newR, newR, 1));
            node.setLN (createTree(node.getLN(),  myBodies,    X - newR, Y - newR, newR, 2));
            node.setRN (createTree(node.getRN(),  myBodies,    X + newR, Y - newR, newR, 3));
            node.setRRN(createTree(node.getRRN(),  myBodies,   X + newR, Y + newR, newR, 4));
            assert(node.getLLN() != null && node.getLN() != null && node.getRN() != null && node.getRRN() != null);
        
            Double m1 = node.getLLN().getM();
            Double m2 = node.getLN().getM();
            Double m3 = node.getRN().getM();
            Double m4 = node.getRRN().getM();

            Double x1 = node.getLLN().getX();
            Double x2 = node.getLN().getX();
            Double x3 = node.getRN().getX();
            Double x4 = node.getRRN().getX();

            Double y1 = node.getLLN().getY();
            Double y2 = node.getLN().getY();
            Double y3 = node.getRN().getY();
            Double y4 = node.getRRN().getY();

            node.setM(m1 + m2 + m3 + m4);

            assert(node.getM() != 0) : "One Body has M == 0";

            node.setX((x1 * m1 + x2 * m2 + x3 * m3 + x4 * m4) / node.getM());

            node.setY((y1 * m1 + y2 * m2 + y3 * m3 + y4 * m4) / node.getM());

            if(node.getLLN().myBodiesID.size() != 0)
                node.addmybodiesID(node.getLLN().myBodiesID);

            if (node.getLN().myBodiesID.size() != 0)
                node.addmybodiesID(node.getLN().myBodiesID);

            if (node.getRN().myBodiesID.size() != 0)
                node.addmybodiesID(node.getRN().myBodiesID);

            if (node.getRRN().myBodiesID.size() != 0)
                node.addmybodiesID(node.getRRN().myBodiesID);
        }
        
        return node;
    }

    public static int TreeSize(TreeNode node) 
    { 
        if (node == null) 
            return 0; 
        else
            return  (TreeSize(node.getLLN()) + TreeSize(node.getLN()) + TreeSize(node.getRN()) + TreeSize(node.getRRN())) + 1;
    } 

    public static void main(String[] args) throws FileNotFoundException 
    {
        assert (args.length == 2): " BAD INPUT!!" ;
       
        Vector<Body> myBodies = new Vector<Body>();

        int IterationNumber = Integer.parseInt(args[1]);
        int NumberOfBodies = 0; 
        Double RangeOfUniverse = 0.0; 

        File myObj = new File(args[0]); // Specify the filename

        if (!myObj.canRead())
            assert(false): " File not opened!\n" ;
       
        Scanner sc = new Scanner(myObj);
        String line = "";
       
        if(sc.hasNext())
        {
            line = sc.nextLine();
            NumberOfBodies = Integer.parseInt(line);
            assert (NumberOfBodies >= 0);
            //System.out.println("The number of Bodies is: " + NumberOfBodies); 

        }
        else
            assert false : "Missing data in File";

        if(sc.hasNext())
        {
            line = sc.nextLine();
            RangeOfUniverse = Double.parseDouble(line);
            assert (RangeOfUniverse >= 0);
            //System.out.println("The Range is: " + RangeOfUniverse); 

        }
        else
            assert false : "Missing data in File";
         
        for(int i = 0; i < NumberOfBodies; ++i)
        {
            line = sc.nextLine();

            String[] tokens = line.split(" ");  
            
            assert (tokens.length == 6) : "Wrong file format!";
            
            Body HelperBody = new Body();
            HelperBody.SetMyParams(tokens, RangeOfUniverse, i);        

            myBodies.addElement(HelperBody);
        }

        sc.close();

        assert myBodies.size() == NumberOfBodies;
        //System.out.println("Size of myBodies vector: " + myBodies.size()); 

        long start = System.currentTimeMillis();

        for(int i = 0; i < IterationNumber; ++i)
        {
            TreeNode Root = new TreeNode();
            Root = createTree(Root, myBodies, 0.0, 0.0, RangeOfUniverse, 1);
            //System.out.println("Tree size: " + TreeSize(Root) + "\n");

            //parallel
            for (int k = 0; k < myBodies.size(); ++k)
                assert(myBodies.get(k).getMarked() == -1) : "Input Error Body out of Range";


            //parallel
            for (int o = 0; o < myBodies.size(); ++o)
                FindForce(myBodies.get(o), Root);

            //parallel
            for (int u = 0; u < myBodies.size(); ++u)
                myBodies.get(u).newPosition();


            //parallel
            for (int y = 0; y < myBodies.size(); ++y)
            {
                double X = myBodies.get(y).getX();
                double Y = myBodies.get(y).getY();

                for (int j = y + 1; j < myBodies.size(); ++j)
                    if (X == myBodies.get(j).getX() && Y == myBodies.get(j).getY())
                    {
                        myBodies.get(j).setX(X + 0.001);
                        myBodies.get(j).setY(Y + 0.001);
                    }
            }

            //parallel
            for (int h = 0; h < myBodies.size(); ++h)
            {
                myBodies.get(h).setMarked(0);
                myBodies.get(h).setBoxsR(0);
            }
        }
        long end = System.currentTimeMillis();
        System.out.println("Timer took " + (end - start) + " ms  (" + (long)((end - start) / (long)1000) +" sec )");
        
        createOutputFile(myBodies, NumberOfBodies, RangeOfUniverse);
    }

}
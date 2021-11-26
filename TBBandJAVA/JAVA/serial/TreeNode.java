import java.util.*;
import java.io.*;


public class TreeNode{
private
    Double X;
    Double Y;
    Double M;
    Double R;
    Body mybody = null;
    TreeNode LLN = null;
    TreeNode LN = null;
    TreeNode RN = null;
    TreeNode RRN = null;

public
    Vector<Integer> myBodiesID = new Vector <Integer>();

    TreeNode(){
        this.X = (Double) 0.0;
        this.Y = (Double) 0.0;
        this.M = (Double) 0.0;
        this.R = (Double) 0.0;
    } 

    public TreeNode(Double X, Double Y,Double R)
    {
        this.X = X;
        this.Y = Y;
        this.M = (Double) 0.0;
        this.R = R;
    }
   
    //GET & SET

    public Double getX()
    {
       return this.X;
    }

    public Double getM()
    {
       return this.M;
    }

    public Double getY()
    {
       return this.Y;
    }

    public Double getR()
    {
       return this.R;
    }

    public void setY(Double Y)
    {
        this.Y = Y;
    }

    public void setX(Double X)
    {
        this.X = X;
    }

    public void setR(Double R)
    {
        this.R = R;
    }

    public void setM(Double M)
    {
        this.M = M;
    }

    public TreeNode getLLN(){
        return this.LLN;
    }

    public TreeNode getLN(){
        return this.LN;
    }

    public TreeNode getRRN(){
        return this.RRN;
    }

    public TreeNode getRN(){
        return this.RN;
    }

    public Body getMyBody(){
        return this.mybody;
    }

    public void setMyBody(Body tmp){
        this.mybody = tmp;
    }

    public void setLLN(TreeNode tmp){
        this.LLN = tmp;
    }

    public void setLN(TreeNode tmp){
        this.LN = tmp;
    }

    public void setRRN(TreeNode tmp){
        this.RRN = tmp;
    }

    public void setRN(TreeNode tmp){
        this.RN = tmp;
    }

    public void addmybodiesID(Vector<Integer> addthisvec)
    {
        for (int i = 0; i < addthisvec.size(); ++i)
            this.myBodiesID.addElement(addthisvec.get(i));
    }
};


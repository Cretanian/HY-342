

public class Body{
private
    double X;
    double Y;
    double Vx;
    double Vy;
    double M;
    double Ax;
    double Ay;
    String S;
    int marked;
    int ID;
    double BoxsR;


public

    Body(){
        this.X          = 0;
        this.Y          = 0;
        this.Vx         = 0;
        this.Vy         = 0;
        this.M          = 0;
        this.S          = "";
        this.marked     = 0;
        this.BoxsR      = 0;
        this.ID         = 0;
        this.Ax         = 0;
        this.Ay         = 0;
    }

    public void SetMyParams(String[] str, double range, int ID)
    {
        this.X          = Double.parseDouble(str[0]);
        this.Y          = Double.parseDouble(str[1]);
        this.Vx         = Double.parseDouble(str[2]);
        this.Vy         = Double.parseDouble(str[3]);
        this.M          = Double.parseDouble(str[4]);
        this.S          = str[5];

        assert (this.M != 0.0) : "One Body has M == 0";
        assert ( (Math.abs(X) <= range && Math.abs(Y) <= range) ) : "BAD INPUT: A body is out of range";
        assert (this.S != null && this.S.length() != 0) : "Error in body's name";

        this.marked     = 0;
        this.ID         = ID;
        this.Ax         = 0;
        this.Ay         = 0;
        this.BoxsR      = 0;
    }

    public void PrintInfo()
    {
        System.out.println("X: " + X);
        System.out.println("Y: " + Y);
        System.out.println("Vx: " + Vx);
        System.out.println("Vy: " + Vy);
        System.out.println("M: " + M);
        System.out.println("S: " + S + "\n");
    }
    
    void newPosition() {
        this.Vx += this.Ax;
        this.Vy += this.Ay;
        this.X  += this.Vx;
        this.Y  += this.Vy;
    }

    //SET && GET
    public void setX_Y(Double X, Double Y){
        this.X = X;
        this.Y = Y;
    }

    public void setX(Double X){
        this.X = X;
    }

    public void setBoxsR(double R) {
        this.BoxsR = R;
    }

    public void setAx(double Ax) {
        this.Ax += Ax;
    }

    public void setAy(double Ay) {
        this.Ay += Ay;
    }
    
    public void setY(Double Y){
        this.Y = Y;
    }

    public void setVx(Double Vx){
        this.Vx = Vx;
    }

    public void setVy(Double Vy){
        this.Vy = Vy;
    }

    public void setM(Double M){
        this.M = M;
    }

    public void setMarked(int tmp){
        this.marked = tmp;
    }
    
    public void reset(){
        this.marked = 0;
        this.BoxsR = 0;
     }

    public Double getX(){
        return this.X;
    }

    public Double getY(){
        return this.Y;
    }

    public Double getVx(){
        return this.Vx;
    }

    public Double getVy(){
        return this.Vy;
    }

    public Double getM(){
        return this.M;
    }
    
    public int getID(){
        return this.ID;
    }
   
    public Double getAx(){
        return this.Ax;
    }

    public Double getAy(){
        return this.Ay;
    }

    public int getMarked(){
        return this.marked;
    }

    public Double getBoxR(){
        return this.BoxsR;
    }

    public String getName(){
        return this.S;
    }

};
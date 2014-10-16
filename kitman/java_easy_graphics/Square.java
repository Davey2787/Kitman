// This program is the square class which allows the user to write the 
//coordinates and size of the square to a file and upload it to 
//an easygraphics window
import java.io.PrintWriter;

public class Square
{
	//Private varibles 
	private int x1;
	private int y1;
	private int length;
	
	// Constructer
	public Square(int xpos, int ypos, int length1)
	{
		this.x1 = xpos;
		this.y1 = ypos;
		this.length = length1;
	}
	
	// Writes the coordinates and lenght of the square to a file
	public void write(PrintWriter printWriter)
	{
		printWriter.println(this.x1 + " " + this.y1 + " " + this.length);
	}
	
	//Draws the square to the lenght specified by the user and
	//to the users coordinates
	public void draw(EasyGraphics easyGraphics)
	{	
		easyGraphics.drawRectangle(this.x1 - length / 2, this.y1 - length / 2, this.length, this.length);
	}
}


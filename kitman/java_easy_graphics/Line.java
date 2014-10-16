// This program is the line class which allows the user to write the 
//coordinates of the start and end of a line to a file and upload it to 
//an easygraphics window 
import java.io.PrintWriter;

public class Line
{
	// Private varibles
	private int x1;
	private int y1;
	private int x2;
	private int y2;

	// Constructer
	public Line(int x1pos, int y1pos, int x2pos, int y2pos)
	{
		this.x1 = x1pos;
		this.y1 = y1pos;
		this.x2 = x2pos;
		this.y2 = y2pos;
	}
	
	// Writes the users coordinates to a file
	public void write(PrintWriter printWriter)
	{
		printWriter.println(this.x1 + " " + this.y1 + " " + " " + this.x2 + " " + this.y2);
	}
	
	// Draws a line to the users coordinates
	public void draw(EasyGraphics easyGraphics)
	{
		easyGraphics.drawLine(this.x1, this.y1, this.x2, this.y2);
		easyGraphics.repaint();
	}
}


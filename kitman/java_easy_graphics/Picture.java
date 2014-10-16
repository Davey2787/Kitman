//This is a picture class that allows you to save, load pictures and holds 
// the methods for drawing the line, square and text
import java.io.File;
import java.util.Scanner;
import java.io.*;

public class Picture
{
	//Private variables
	
	private EasyGraphics draw;
	private int numSquare = 0;
	private int numLine = 0;
	private int numTxt = 0;
	
	private Square holdSquare[];
	private Line holdLine[];
	private Txt holdTxt[];
	
	// Constructor
	Picture(int i, int j)
	{ 
		holdSquare = new Square[20];
		holdLine = new Line[20];
		holdTxt = new Txt[20];
		draw = new EasyGraphics(i, j);
		deletePicture();
	}

	//  
	public void deletePicture()         
	{
		numLine = 0;         
		numSquare = 0;
		numTxt = 0;
	}
	
	// Draw Square
	public void addSquare(int x, int y, int length)
	{
		Square square = new Square(x, y, length);
		square.draw(draw);
		holdSquare[numSquare] = square;
		numSquare++;        
	}
	
	// Line
	public void addLine(int x1, int y1, int x2, int y2)
     	{
    	    	Line line = new Line(x1, y1, x2, y2);
		line.draw(draw);  
		holdLine[numLine] = line;   
		numLine++;                   
	}
        
	// Add Txt
	public void addTxt(String txt, int x1, int y1)
	{
		Txt text1 = new Txt(txt, x1, y1);
		text1.draw(draw);               
		holdTxt[numTxt] = text1;
		numTxt++;    
	} 
    
	// Save picture
	public void save(String filename) 
	{
		FileWriter filewriter = null;
		
		// Throws I/O exception  
		try
		{
			filewriter = new FileWriter(filename);
		}
		
		catch(IOException a)       
		{
			System.err.println("Error when saving file ");
			System.exit(0);
		}
		
		 // write to files
		PrintWriter printwriter = new PrintWriter(filewriter, true);
		
		// checks holdSquare array to see how many Squares were drawn
		printwriter.println(numSquare);
		for(int j = 0; j < numSquare; j++)
		{
			holdSquare[j].write(printwriter); 
		}
		
		// checks holdLine array to see how many Lines were drawn
		printwriter.println(numLine);
		for(int i = 0; i < numLine; i++)
		{
			holdLine[i].write(printwriter);     
		}
		
		// checks holdTxt array to see how much Txt was written
		printwriter.println(numTxt);
		for(int k = 0; k < numTxt; k++)
		{
			holdTxt[k].write(printwriter);    
		}
        }
    
        // Load picture
        public void load(String filename)
        {
     		int numPictures = 0;
     		Scanner scanner = null;
     		draw.clear();
     		// Throws exception
     		try  
     		{
     			scanner = new Scanner(new File(filename));
     		}
     		catch(Exception exception)
     		{
     			System.out.println("Error when opening file");
     			System.exit(0);
     		}
     		
     		//Reading saved file for information for Squares
     		numPictures = scanner.nextInt();
     		for(int k = 0; k < numPictures; k++)
     		{
     			int x1 = scanner.nextInt();
     			int y1 = scanner.nextInt();
     			int length = scanner.nextInt();
     			addSquare(x1, y1, length);     
     		}
     		
     		//Reading saved file for information for Lines
     		numPictures = scanner.nextInt();
     		for(int j = 0; j < numPictures; j++)
     		{
     			int x1 = scanner.nextInt();
     			int y1 = scanner.nextInt();
     			int x2 = scanner.nextInt();
     			int y2 = scanner.nextInt();
     			addLine(x1, y1, x2, y2); 
     		}
     		
     		//Reading saved file for Txt
     		numPictures = scanner.nextInt();
     		for(int l = 0; l < numPictures; l++)
     		{
     			int x1 = scanner.nextInt();
     			int y1 = scanner.nextInt();
     			String txt = scanner.next();
     			addTxt(txt,x1, y1);      
     		}

     	}
     	
    
	// Clear picture
	public void clearPicture()
	{
		draw.clear();
		deletePicture();
	}
            
}

	
	
	

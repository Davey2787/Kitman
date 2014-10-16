// This program diplays the menu for the user to select 
// what drawing they want to draw and contains all the methods
// for the square, line, text, save and load
import java.io.PrintStream;
import java.util.Scanner;

public class Illustrator
{
	public static void main(String[] arrayofstring)
	{
		int width = 200;
		int hight = 200; 
		Picture display = new Picture(width,hight);
		Scanner userInput = new Scanner(System.in);
		print_menu();
		
		while(userInput.hasNext())
		{
			String input = userInput.next();
			char c = input.charAt(0);// allows user to enter lower
			c = Character.toUpperCase(c);// or upper case letters
			
			switch(c) // switch statment used to call the methods
			{	  // see below line 58 onwards	
			case 'S':
				square1(display, userInput);
				print_menu();
				break;
			case 'L':
				line1(display, userInput);
				print_menu();
				break;
			case 'T':
				txt1(display, userInput);
				print_menu();
				break;
			case 'D':
				loadfile(display, userInput);
				print_menu();
				break;
			case 'V':
				savefile(display, userInput);
				print_menu();
				break;
			case 'C':
				clearPic(display);
				print_menu();
				break;
			case 'Q':
				System.exit(0);
				break;	
			}
		}
	
	
	}
	
	/* Methods*/
	//Menu
	private static void print_menu()
	{
		System.out.println("(S) Add Square");
		System.out.println("(L) Add Line");
		System.out.println("(T) Add Text");
		System.out.println("(D) LoaD Picture");
		System.out.println("(V) saVe Picture");
		System.out.println("(C) Clear Picture");
		System.out.println("(Q) Quit");
		System.out.print("Enter Command (S,L,T,U,D,V,C,H or Q): ");
	}
	
	// Square
	 private static void square1(Picture display, Scanner userInput)
	{
		System.out.println("Adding Square");
		System.out.print("Enter x pos: ");
		int i = userInput.nextInt();
		System.out.print("Enter y pos: ");
		int j = userInput.nextInt();
		System.out.print("Enter Size: ");
		int k = userInput.nextInt();
		display.addSquare(i, j, k);
    	}
    	
    	// Line
	private static void line1(Picture display, Scanner userInput)
	{
		System.out.println("Adding Line");
		System.out.print("Enter x1 pos: ");
		int i = userInput.nextInt();
		System.out.print("Enter y1 pos: ");
		int j = userInput.nextInt();
		System.out.print("Enter x2 pos: ");
		int k = userInput.nextInt();
		System.out.print("Enter y2 pos: ");
		int m = userInput.nextInt();
		display.addLine(i, j, k, m);
	}
	
	// Text
	private static void txt1(Picture display, Scanner userInput)
	{
		System.out.println("Adding Text");
		System.out.print("Enter text string: ");
		String str = userInput.next();
		System.out.print("Enter x1 pos: ");
		int i = userInput.nextInt();
		System.out.print("Enter y1 pos: ");
		int j = userInput.nextInt();
		display.addTxt(str, i, j);
	}
	
	// Load Picture
	private static void loadfile(Picture display, Scanner userInput)
	{
		System.out.println("Load Picutre");
		System.out.print("Enter file name: ");
		String loadpic = userInput.next();
		display.load(loadpic);
	}
	
	//Save Picture
	private static void savefile(Picture display, Scanner userInput)
	{
		System.out.println("Save Picutre");
		System.out.print("Enter file name: ");
		String savepic = userInput.next();
		display.save(savepic);
	}
	
	// clear Picture
	private static void clearPic(Picture display)
	{
		display.clearPicture();
	}

}

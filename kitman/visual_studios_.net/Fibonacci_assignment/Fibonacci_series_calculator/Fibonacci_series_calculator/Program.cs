using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Fibonacci_series_calculator.testweb1; // links to the Fibonacci web service

namespace Fibonacci_series_calculator
{

    class Program
    {
        static void Main(string[] args)
        {
            // creates a new connection to the webservice
            Service1 webservice = new Service1(); 
            // asks the user to input the amount of numbers in the sequence they want
            Console.WriteLine("Please enter the amount of fibonacci numbers required:"); 
            // Reads in the the value the user entered as string
            string input = Console.ReadLine();
            Console.Write("\n"); 
            // converts the the value from a string to an integer
            int j = Convert.ToInt32(input);
            // creates an integer array of the size entered by the user
            int[] Fseries = new int[j];

            // calls the Fibonacci Web service and passes it 
            // the length of the sequence to calculate and
            // the size of the array to return and stores it 
            // in the Fseries array
            Fseries = webservice.Fibonacci(j, Fseries);

            // For loop prints out the Fibonacci sequence returned
            // into the Fseries array with a suitable message 
            Console.Write("The Fibonaci sequence is ");  
            for (int i = 0; i < Fseries.Length; i++)
            {
                Console.Write(Fseries[i] + " ");
            }
            Console.Write("\n\n");  
        }
    }
}

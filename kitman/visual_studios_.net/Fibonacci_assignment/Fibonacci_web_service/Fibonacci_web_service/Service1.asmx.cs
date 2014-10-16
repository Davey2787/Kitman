using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Services;


namespace Fibonacci_web_service
{
   
    /// <summary>
    /// Summary description for Service1
    /// </summary>
    [WebService(Namespace = "http://tempuri.org/")]
    [WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
    [System.ComponentModel.ToolboxItem(false)]
    // To allow this Web Service to be called from script, using ASP.NET AJAX, uncomment the following line. 
    // [System.Web.Script.Services.ScriptService]

  
    public class Service1 : System.Web.Services.WebService
    {
        // Creates the web method "Fibonacci" which is passed in two arguments
        // An integer "n" and an integer array "FibArr"
        // It returns an integer array
        [WebMethod]
        public int[] Fibonacci(int n, int[] FibArr) 
        {
            int j = 0;
            int k = 1;
            int temp;

            // For loop populates "FibArr" with the 
            // Fibonacci sequence of lenght n
            // The next number in a Fibonacci sequence is 
            // the sum of the previous two.
            for (int i = 0; i < n; i++)
            {
                temp = j;
                j = k;
                k = temp + k;
                FibArr[i] = j;
            }

            // returns the integer array containing the 
            // fibonacci sequence to the console application 
            return FibArr;
        }
    }
}
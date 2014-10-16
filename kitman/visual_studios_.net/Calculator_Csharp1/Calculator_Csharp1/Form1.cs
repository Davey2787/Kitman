using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using DLLMathFuncs;


namespace Calculator_Csharp1
{
    public partial class Form1 : Form
    {
        Char currentop;
		Char previousOp ='+';
		double running_tot = 0;
		double begin = 1;
		double newnum;

        Class1 obj1 = new Class1();

        public Form1()
        {
            InitializeComponent();
        }

        private void button_0_Click(object sender, EventArgs e)
        {
            if ((display.Text == "0") || (begin == 1))
            {
                display.Text = "0";
                begin = 0;
            }
            else
            {
                display.Text += "0";
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {

            if ((display.Text == "0") || (begin == 1))
            {
                display.Text = "1";
                begin = 0;
            }
            else
            {
                display.Text += "1";
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if((display.Text == "0")||(begin==1))
				 {
					 display.Text = "2";
					 begin=0;
				 }
			 else
				 {
					 display.Text += "2";
				 }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if((display.Text == "0")||(begin==1))
				 {
					 display.Text = "3";
					 begin=0;
				 }
			 else
				 {
					 display.Text += "3";
				 }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if((display.Text == "0")||(begin==1))
				 {
					 display.Text = "4";
					 begin=0;
				 }
			 else
				 {
					 display.Text += "4";
				 }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if((display.Text == "0")||(begin==1))
				 {
					 display.Text = "5";
					 begin=0;
				 }
			 else
				 {
					 display.Text += "5";
				 }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            if((display.Text == "0")||(begin==1))
				 {
					 display.Text = "6";
					 begin=0;
				 }
			 else
				 {
					 display.Text += "6";
				 }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            if((display.Text == "0")||(begin==1))
				 {
					 display.Text = "7";
					 begin=0;
				 }
			 else
				 {
					 display.Text += "7";
				 }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            if((display.Text == "0")||(begin==1))
				 {
					 display.Text = "8";
					 begin=0;
				 }
			 else
				 {
					 display.Text += "8";
				 }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            if((display.Text == "0")||(begin==1))
				 {
					 display.Text = "9";
					 begin=0;
				 }
			 else
				 {
					 display.Text += "9";
				 }
        }

        private void dec_point_Click(object sender, EventArgs e)
        {
            display.Text += ".";
            begin = 0;
        }

        private void plus_button_Click(object sender, EventArgs e)
        {
            currentop = '+';
            newnum = Convert.ToDouble(display.Text);
            switch (previousOp)
            {
                case '+':
                    running_tot = obj1.add(running_tot,newnum);
                    break;
                case '-':
                    running_tot = obj1.sub(running_tot, newnum);
                    break;
                case 'x':
                    running_tot = obj1.mul(running_tot, newnum);
                    break;
                case '/':
                    running_tot = obj1.div(running_tot, newnum);
                    break;
            }
             display.Text = Convert.ToString(running_tot);
			 previousOp = currentop;
			 begin = 1;
        }

        private void minus_button_Click(object sender, EventArgs e)
        {
             currentop= '-';
			 newnum = Convert.ToDouble(display.Text);
			 switch(previousOp){
                 case '+':
                     running_tot = obj1.add(running_tot, newnum);
                     break;
                 case '-':
                     running_tot = obj1.sub(running_tot, newnum);
                     break;
                 case 'x':
                     running_tot = obj1.mul(running_tot, newnum);
                     break;
                 case '/':
                     running_tot = obj1.div(running_tot, newnum);
                     break;
            }
             display.Text = Convert.ToString(running_tot);
             previousOp = currentop;
             begin = 1;
        }

        private void multiply_button_Click(object sender, EventArgs e)
        {
             currentop= 'x';
			 newnum = Convert.ToDouble(display.Text);
			 switch(previousOp){
                 case '+':
                     running_tot = obj1.add(running_tot, newnum);
                     break;
                 case '-':
                     running_tot = obj1.sub(running_tot, newnum);
                     break;
                 case 'x':
                     running_tot = obj1.mul(running_tot, newnum);
                     break;
                 case '/':
                     running_tot = obj1.div(running_tot, newnum);
                     break;
            }
             display.Text = Convert.ToString(running_tot);
             previousOp = currentop;
             begin = 1;
        }

        private void divide_button_Click(object sender, EventArgs e)
        {
            currentop= '/';
			 newnum = Convert.ToDouble(display.Text);
			 switch(previousOp){
                 case '+':
                     running_tot = obj1.add(running_tot, newnum);
                     break;
                 case '-':
                     running_tot = obj1.sub(running_tot, newnum);
                     break;
                 case 'x':
                     running_tot = obj1.mul(running_tot, newnum);
                     break;
                 case '/':
                     running_tot = obj1.div(running_tot, newnum);
                     break;
            }
             display.Text = Convert.ToString(running_tot);
             previousOp = currentop;
             begin = 1;
        }

        private void equals_button_Click(object sender, EventArgs e)
        {
            currentop= '=';
			 newnum = Convert.ToDouble(display.Text);
			 switch(previousOp){
                 case '+':
                     running_tot = obj1.add(running_tot, newnum);
                     break;
                 case '-':
                     running_tot = obj1.sub(running_tot, newnum);
                     break;
                 case 'x':
                     running_tot = obj1.mul(running_tot, newnum);
                     break;
                 case '/':
                     running_tot = obj1.div(running_tot, newnum);
                     break;
			 }
			 display.Text = Convert.ToString(running_tot);
			 previousOp = currentop;
			 begin = 1;
        }

        private void clear_button_Click(object sender, EventArgs e)
        {
            display.Text = "0";
            running_tot = 0;
            previousOp = '+';
            begin = 1;
        }

        private void display_TextChanged(object sender, EventArgs e)
        {

        }

    }
}

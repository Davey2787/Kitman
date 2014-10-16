import MySQLdb
import subprocess
def log( x, y ):
	try:
		x = float(x)
		y = float(y)
		db = MySQLdb.connect("localhost",user="root",passwd="burnface27",db="logger")
		cursor=db.cursor()		
		SQLString = "INSERT INTO XandY (x,y,timestamp) VALUES (%f,%f,NOW());" % (x,y)
		#print SQLString
		cursor.execute(SQLString)		
		db.commit()
		db.close()
		return "Database updated successfully"
	except:
		return "Error updating database"

def fetch(req):
	req.content_type = "text.html"
	try:	
		db = MySQLdb.connect("localhost",user="root",passwd="burnface27",db="logger")
		cursor=db.cursor()		
		SQLString = "SELECT x,y,timestamp FROM XandY;"
		cursor.execute(SQLString)
		
		ReturnHTML = '<TABLE border = "1" style = width: "300px">'
		ReturnHTML = ReturnHTML + "<TR>"
		ReturnHTML = ReturnHTML + "<TH>" + "X_coor" + "</TH>"
		ReturnHTML = ReturnHTML + "<TH>" + "Y_coor" + "</TH>"
		ReturnHTML = ReturnHTML + "<TH>" + "Time Stamp" + "</TH>"
		ReturnHTML = ReturnHTML + "</TR>"
		row=cursor.fetchone()
		while row:
			ReturnHTML = ReturnHTML + "<TR>"
			ReturnHTML = ReturnHTML + "<TD>" + str(row[0]) + "</TD>"
			ReturnHTML = ReturnHTML + "<TD>" + str(row[1]) + "</TD>"
			ReturnHTML = ReturnHTML + "<TD>" + str(row[2]) + "</TD>"
			ReturnHTML = ReturnHTML + "</TR>"
			row = cursor.fetchone()
		db.close()
		ReturnHTML = ReturnHTML + "</TABLE>"
		return ReturnHTML		
	except:
		return "Error retrieving data"

def graph(req):
	req.content_type = "text.html"
	try:	
		db = MySQLdb.connect("localhost",user="root",passwd="burnface27",db="logger")
		cursor=db.cursor()		
		SQLString = "SELECT x,y,timestamp FROM XandY;"
		cursor.execute(SQLString)
		row=cursor.fetchone()
		f = open("/home/david/public_html/img/test.dat","w")
		while row:
			f.write("%f:%f\n"%(row[0],row[1]))
			row = cursor.fetchone()	
		db.close()
		f.close()
		PlotCommand = ['gnuplot', '-e', "set term png; set output '/home/david/public_html/img/test.png'; set title 'XandY MySQl Table Data'; set xlabel 'X axis' ; set ylabel 'Y axis'; plot '/home/david/public_html/img/test.dat' u 1 with lines"]
		subprocess.check_output(PlotCommand)
		
		return "<img src='../img/test.png'>"
	except Exception as e:
		return "Error retrieving data. Reason:"+ str(e)	


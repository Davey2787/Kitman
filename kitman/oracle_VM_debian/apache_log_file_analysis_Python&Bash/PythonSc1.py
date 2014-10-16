#!/usr/bin/python

# 07/03/2014 - David Byrne & Paul Conlon 
# Logfile used: access.log.14

# The following script is used to  analyse the data in an apache access log file and carry 
# out the following objectives:
# 1) List the top 10 visitors to the site by IP address and, if possible, by name
# 2) List the top ten pdf downloads from the site
# 3) List the top 5 Browsers/user agents that visit the site.
# 4) The number of ipv6 visitors (if any)

import sys # imports syst library
import collections #import collections library - contains "Counter"
import socket # imports socket library

# First loop to find top ten IP's
def Get_Top10_IP(FileName): # passes log details to function
	print "\nOpening %s " + FileName + "\n" # prints to terminal
	LogFile=open(FileName,"r") # opens log file, "r" denotes read
	Entry=LogFile.readline() #readline() reads a single line from the file
	ips=[] # declares the array
	
	while Entry:
		if "GET" in Entry: # if GET in line of interest in Entry enter loop
			# build up an array of ip addressess 
			# append() built in function, adds line to bottom of 'ips' array
			ips.append(Entry.split()[0]) # first space is used as delim
		Entry=LogFile.readline() #read next line of logfile
	# Counter added from library to support convenient and rapid tallies

	CountIP = collections.Counter(ips) # Tallies the array in CountIP
	print "Top Ten IP :" +"\n" # print
	

	# Use most_common() to produce a sequence of the 
	# n most frequently encountered
	# input values and their respective counts.
	for count in CountIP.most_common(10): # Allows printing in colunms
		while True:
			try:	# tries to print IP adress and get host website from IP address
				print str(count[0])
				ip = str(count[0])
				print(socket.gethostbyaddr(ip)) 
				break	
			except socket.herror: # if socket.herror prints error message
				print "Oops!  Could not Identify host"
				break
# Second loop to find top ten pdf's
def Get_Top10_pdf(FileName): # passes log details to function
	print "\nOpening %s " + FileName + "\n" # prints to terminal
	LogFile=open(FileName,"r") # opens log file
	Entry=LogFile.readline()
	pdfs=[] # declares the array
	while Entry:
		if "GET" in Entry:
			if ".pdf" in Entry:
				# build up an array of pdf's
				pdfs.append(Entry.split()[6]) # seventh space is used as delim, 0 equiv to 1 in bash
		Entry=LogFile.readline() #read next line of logfile
	Countpdf = collections.Counter(pdfs)
	print "Top Ten pdf's :" +"\n" # print
	for count in Countpdf.most_common(10): # count most common 
			print str(count[0]) 

# Third loop to find top 5 browsers 
def Get_Top5_Browser(FileName): # passes log details to function
	print "\nOpening %s " + FileName + "\n" # prints to terminal
	LogFile=open(FileName,"r") # opens log file
	Entry=LogFile.readline()
	browser=[] # declares the array
	while Entry:
		if "GET" in Entry: 
			if "Mozilla" in Entry: 
				# inverted commas used as delim,
				# browser info of note between 5th & 6th
				browser.append(Entry.split('"')[5]) 
		Entry=LogFile.readline() #read next line of logfile
	CountBrowser = collections.Counter(browser) 
	print "Top 5 Browsers :" +"\n" # print	
	for count in CountBrowser.most_common(5):
			print str(count[0]) #prints 1st colunm

# Fourth loop to show IPV6 visitors, talies and total visitors  
def Get_IPV6(FileName): # passes log details to function
	print "\nOpening %s " + FileName + "\n" # prints to terminal
	LogFile=open(FileName,"r") # opens log file
	Entry=LogFile.readline()
	ipv6=[] # declares the array
	unique_ipv6 = 0
	while Entry:
		if "GET" in Entry: 
			if "::" in Entry: 
				ipv6.append(Entry.split()[0]) # first space is used as deli
		Entry=LogFile.readline() #read next line of logfile
	CountIPV6 = collections.Counter(ipv6) #
	# values() returns a list of all the values availablle
	num_ipv6= sum(CountIPV6.values()) # sum returns the total
	
	for count in CountIPV6.most_common():
			print str(count[1])+ "\t" + str(count[0]) # prints 1st & 2nd Colunm
			unique_ipv6 = unique_ipv6 + 1
	print "\nTotal Number of IPV6 ip addresses is "
	print (str(num_ipv6))
	print "\nUnique IPV6 ip addresses is"
	print unique_ipv6

# main loop calls each function in turn
def main():
	print ("Starting main")
	Get_Top10_IP(sys.argv[1]) #sys.argv[1]"access.log.14"
	Get_Top10_pdf(sys.argv[1]) 
	Get_Top5_Browser(sys.argv[1])
	Get_IPV6(sys.argv[1])

# if loop designates the main loop
if __name__ == "__main__":
    main()

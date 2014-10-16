# 07/03/2014 - David Byrne & Paul Conlon 
# Logfile used: access.log.14

# The following script is used to  analyse the data in an apache access log file and carry 
# out the following objectives:
# 1) List the top 10 visitors to the site by IP address and, if possible, by name
# 2) List the top ten pdf downloads from the site
# 3) List the top 5 Browsers/user agents that visit the site.
# 4) The number of ipv6 visitors (if any)

# Locates get requests in log file and cuts all the text after the first space, finds the top 10 
# unique IP address, the while loop is used to identify the host names.
echo 
echo [Top 10 IP]
grep "GET " access.log.14 | cut -f 1 -d ' ' | sort | uniq  -c | sort -nr \
| head | cut -c 9- |\
while read hostip; do
	echo $hostip
	whois -H $hostip | grep -i netname | cut -f 2 -d ':'
done
echo

# Locates get requests in log file, searchs for pdfs, awk searches the line for spaces and 
# captures text before seventh space, finds the top 10 unique pdfs 
echo [Top 10 pdf]
grep "GET" access.log.14 | grep .pdf | awk '{print$7}' | sort -n | \
uniq -c | sort -rn | head | cut -c 10-
echo

# Locates get requests in log file that has the word Mozilla in it, in this case the delimeter " is 
# used to isolate the browser information of interest. The top 5 browsers are found in this case
echo [Top 5 Browsers]
grep "GET" access.log.14 | grep "Mozilla" | cut -f 6 -d '"' |\
sort -n | uniq -c | sort -nr | head -5 | cut -c 9-
echo

# Extracts and counts all IPV6 addresses, in this case :: is used to further isolate IPV6 
# addresses from get request, the first field up to the delimeter of the first space is isolated.
# In this case the unique and total IPV6's are tallied and printed to the terminal
echo [Count ipv6] 
grep "GET" access.log.14 | grep "::" | sort | cut -f 1 -d ' ' |  uniq -c | sort -nr  

grep "GET" access.log.14 | grep "::" | sort | cut -f 1 -d ' ' |  uniq -c | wc -l 
echo Unique IPV6

grep "GET" access.log.14 | grep "::" | wc -l
echo In total

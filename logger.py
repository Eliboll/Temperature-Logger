import time		#used much like datetime
import flask	#runs http server
import os 		#used for directories
from datetime import datetime	#used for timestamp

def Tprint(message):	#function takes a string, prints it with the current time, hour, and second, then returns the value it printed
	now = datetime.now()
	message = "[{0}]".format(now.strftime("%H:%M:%S")) + message
	print(message)
	return message

tempServer = flask.Flask(__name__) # initializes the server

@tempServer.route('/') 
def landing():
	temp = flask.request.args.get("temp") #sets request keyward to "temp"
	time = datetime.now()
	try:		#tries to make a director for the current year and month. If it fails then there is already one made and it catches the exception
		os.makedirs("logs/{0}/{1}".format(time.year,time.month))
	except FileExistsError:
		0
	file= open(os.path.dirname(os.path.realpath(__file__)) + "/logs/{0}/{1}/{2}.txt".format(time.year,time.month,time.day),"a") #opens/creates file for logs for individual day
	file.write(Tprint(temp) +"\n") #prints the terminal as well as loggs file
	file.close()
	return "LOGGED " + temp


if __name__ == "__main__":
	tempServer.run(host='0.0.0.0')

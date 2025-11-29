from datetime import date, datetime
import requests
import os.path

today = date.today()

year = today.year
day = today.day

print(year)
print(day)

# Only run if after 7 AM
current_time = datetime.now().time()
if current_time.hour < 7:
	exit(0)

if (day > 25):
	exit(0)

path = str(day) + "/InputData.txt"
test_path = str(day) + "/TestData.txt"
f = open("session.txt", "r")

if (os.path.isfile(path) is False):
    cookies = {'session': f.read()}

    url = f"https://adventofcode.com/{year}/day/{day}/input"

    r = requests.get(url=url, cookies=cookies)

    data = r.text

    f = open(path, "w")
    f.write(data)

# Create TestData.txt if it doesn't exist
if (os.path.isfile(test_path) is False):
    f = open(test_path, "w")
    f.close()

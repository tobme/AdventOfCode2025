from datetime import date, datetime
import requests
import os.path
import sys
import argparse


def main(argv=None):
    parser = argparse.ArgumentParser(description="Fetch Advent of Code input for the current day")
    parser.add_argument("--force", action="store_true", help="Ignore month check (allow running outside December)")
    parser.add_argument("--day", type=int, help="Override day (1-25) for testing)")
    args = parser.parse_args(argv)

    today = date.today()
    year = today.year
    use_day = args.day if args.day is not None else today.day

    print(year)
    print(use_day)

    # Only intended for Advent of Code (December 1-25)
    if not args.force and today.month != 12:
        print("This script only works for December (Advent of Code). Exiting.")
        return 0

    # Only run if after 7 AM
    current_time = datetime.now().time()
    if current_time.hour < 7:
        return 0

    if use_day > 25 or use_day < 1:
        print("Day out of range (1-25). Exiting.")
        return 0

    path = str(use_day) + "/InputData.txt"
    test_path = str(use_day) + "/TestData.txt"

    try:
        with open("session.txt", "r") as sf:
            session_token = sf.read().strip()
    except FileNotFoundError:
        print("session.txt not found. Please create it with your session cookie.")
        return 1

    if not os.path.isfile(path):
        cookies = {"session": session_token}
        url = f"https://adventofcode.com/{year}/day/{use_day}/input"

        r = requests.get(url=url, cookies=cookies)
        if r.status_code != 200:
            print(f"Failed to fetch input: HTTP {r.status_code}")
            return 1

        data = r.text
        os.makedirs(str(use_day), exist_ok=True)
        with open(path, "w", encoding="utf-8") as outf:
            outf.write(data)

    # Create TestData.txt if it doesn't exist
    if not os.path.isfile(test_path):
        os.makedirs(str(use_day), exist_ok=True)
        with open(test_path, "w", encoding="utf-8") as tf:
            pass

    return 0


if __name__ == "__main__":
    try:
        rc = main()
        sys.exit(rc)
    except Exception as e:
        print("Error while running FetchInput.py:", e)
        sys.exit(1)

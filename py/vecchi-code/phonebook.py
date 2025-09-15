import csv

name = input("name: ")
number = input("number: ")

with open("phonebook.csv", "a") as file:
    temp = csv.writer(file)
    temp.writerow([name, number])

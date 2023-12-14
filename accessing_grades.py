def forgrades(i):
    for index, element in enumerate(i):
        if index % 2 == 0:
            print(element)


def fornames(i):
    for index, element in enumerate(i):
        if index % 2 == 1:
            print(element, end="\r")


file = open("grades.txt", "r")
mystring = file.readlines()
arr = []

for i in mystring[1:]:
    arr = arr + i.split("\t\t")

forgrades(arr)
fornames(arr)

file.close()

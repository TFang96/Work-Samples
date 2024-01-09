def main():
    x = input("Enter a numerical value: ")
    y = input("Enter another numerical value: ")
    print("The sum is: " + str(addtwonumbers(int(x), int(y))))


def addtwonumbers(a, b):
    return a + b


main()
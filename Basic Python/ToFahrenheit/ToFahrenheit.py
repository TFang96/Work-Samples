def main():
    celsius = int(input("Please enter a value: "))
    print(str(celsius) + " degrees in celsius is " + str(to_fahrenheit(celsius)) + " in celsius")


def to_fahrenheit(celsius):
    return 1.8 * celsius + 32


main()
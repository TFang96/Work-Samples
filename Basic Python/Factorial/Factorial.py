def main():
    n = int(input("Please enter a number... "))
    print("The factorial of " + str(n) + " is " + str(factorial(n)))


def factorial(n):
    if n < 0:
        raise Exception("Err: Factorial of a negative number. ")
    elif n == 0 or n == 1:
        return 1
    else:
        return n * factorial(n-1)


main()

def main():
    n = int(input("Please enter a number... "))
    if is_prime(n):
        print("The number, " + str(n) + " is prime")
    else:
        print("The number, " + str(n) + " is not prime")


def is_prime(n):
    for i in range(3, int(n/2) + 1):
        if n % i == 0:
            return False
    return True


main()

def main():
    year = int(input("Please enter a year: "))
    if is_leap(year):
        print("Yes")
    else:
        print("No")


def is_leap(year):
    if year % 400 == 0:
        return True
    elif year % 4 == 0 and year % 100 != 0:
        return True
    else:
        return False


main()

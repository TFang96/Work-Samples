def main():
    number = int(input("Please enter a number: "))
    if sum_of_digits_power(number) == number:
        print("Yes, this is an armstrong number... ")
    else:
        print("No, this is not an armstrong number... ")


def sum_of_digits_power(number):
    sum = 0
    for digit in str(number):
        sum += int(digit)**len(str(number))
    return sum

main()
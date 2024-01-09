def main():
    number = input("Please enter a number: ")
    print("The reverse is: " + reverse(number))


def reverse(num):
    stack = []
    reverse = ""
    for digit in str(num):
        stack.append(digit)
    while stack:
        reverse += stack[-1]
        stack.pop()
    return reverse


main()

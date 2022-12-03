#!/bin/python3

name = "input.txt"

def main():
    sum = 0
    sums = []
    print("Start")
    with open(name, "r") as file:
        for line in file:
            # This gets you on the naughty list, not nice to rely on exceptions like this
            try:
                num = int(line)
                sum += num
            except:
                sums.append(sum)
                sum = 0
    print("The sum array is: ")
    print(sums)
    print("The maximum of the array is: ")
    print(max(sums))


if __name__ == "__main__":
    main()

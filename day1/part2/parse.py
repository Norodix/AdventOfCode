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

    total_to_share = 0
    for i in range(3):
        maximal = max(sums)
        print(maximal)
        sums.remove(maximal)
        total_to_share += maximal

    print("total to share: ")
    print(total_to_share)

    #print("The sum array is: ")
    #print(sums)
    #print("The maximum of the array is: ")
    #print(max(sums))


if __name__ == "__main__":
    main()

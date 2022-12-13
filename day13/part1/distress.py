import json

inputfile = "input.txt"

# a bigger -> 1
# b bigger -> -1
# equal 0
def compare(a, b):
    print("Comparing ", a, " to ", b)
    if isinstance(a, int) and isinstance(b, int):
        return compare_num(a, b)
    
    elif isinstance(a, list) and isinstance(b, list):
        return compare_list(a, b)

    elif isinstance(a, list) and isinstance(b, int):
        return compare_list(a, [b])
    
    elif isinstance(a, int) and isinstance(b, list):
        return compare_list([a], b)
    
    else:
        print("There is something really wrong... neigher list nor int")
    pass

def compare_list(a, b):
    print("Comparing list ", a, " to list ", b)
    for i in range(min(len(a), len(b))):
        c = compare(a[i], b[i])
        if c != 0:
            return c
    # not returned during direct comparison -> shorter is smaller
    if len(a) < len(b):
        return -1
    if len(b) < len(a):
        return 1
    
    #same len, same elements
    return 0

def compare_num(a, b):
    if a > b:
        return 1
    if a < b:
        return -1
    return 0


index = 0
acc = 0
with open(inputfile, "r") as file:
    while True:
        index += 1
        str1 = file.readline()
        str2 = file.readline()
        file.readline() # skip empty line
        if not str2: break

        result = compare(json.loads(str1), json.loads(str2))
        print("Compare result: ", result)
        if result == -1:
            acc += index

print("Sum of indexes: ", acc)


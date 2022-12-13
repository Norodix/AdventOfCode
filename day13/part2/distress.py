import json

inputfile = "input.txt"

# a bigger -> 1
# b bigger -> -1
# equal 0
def compare(a, b):
    if isinstance(a, int) and isinstance(b, int):
        return compare_num(a, b)
    
    elif isinstance(a, list) and isinstance(b, list):
        return compare_list(a, b)

    elif isinstance(a, list) and isinstance(b, int):
        return compare_list(a, [b])
    
    elif isinstance(a, int) and isinstance(b, list):
        return compare_list([a], b)
    
    else:
        print("There is something really wrong... neither list nor int")
    pass

def compare_list(a, b):
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


messages = []
with open(inputfile) as f_in:
    lines = list(line for line in (l.strip() for l in f_in) if line)
    for l in lines:
        messages.append(json.loads(l))
        # fix separators
    messages.append([[2]])
    messages.append([[6]])

# do a bubble sort for the messages
for i in range(len(messages) - 1):
    for j in range(len(messages) - 1):
        if ( compare(messages[j], messages[j+1]) == 1 ):
            tmp = messages[j]
            messages[j] = messages[j+1]
            messages[j+1] = tmp
        pass

mult = 1
for i in range(len(messages)):
    if (compare(messages[i], [[2]]) == 0 or 
        compare(messages[i], [[6]]) == 0):
        mult *= (i+1)
    print(messages[i])
print("Product of indeces: ", mult)
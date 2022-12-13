from anytree import NodeMixin, RenderTree
import regex as re

inputfile = "input.txt"

class MyFile:
    def __init__(self, name, dir = False, size = 0, parent = None) -> None:
        self.name = name
        self.is_dir = dir
        self.size = size
        self.parent = parent
        self.children = []

    def calculate_size(self):
        if not self.is_dir:
            return self.size
        else:
            self.size = 0
            for child in self.children:
                self.size += child.calculate_size()
            return self.size
       
    def add(self, object):
        if self.is_dir == False:
            print("Cannot add to non dir")
            exit(-1)
        
        print("Adding ", object.name, " to ", self.name)
        self.children.append(object)
    
    def get_file(self, name):
        if self.is_dir == False:
            print("Cannot get from non dir")
            exit(-1)
        for child in self.children:
            if child.name == name:
                return child
        return None
    
    def print(self):
        print(self.name)
        for child in self.children:
            if child.is_dir:
                child.print()
            else:
                print(child.name)
    
    def print_dirs(self):
        print(self.name, " size: ", self.size)
        for child in self.children:
            if child.is_dir:
                child.print_dirs()
    
    def print_dirs_small(self):
        if self.size < 100000:
            print(self.name, " size: ", self.size)
        for child in self.children:
            if child.is_dir:
                child.print_dirs_small()

        

lines = []
with open(inputfile, "r") as file:
    for line in file:
        lines.append(line.strip()) # not very nice to load everything at once




i = 1 # 0 is alwas cd root
# Create root directory
root = MyFile("/", True)
pwd = root

while i < len(lines):
    line = lines[i]
    if line[0] == '$':
        # This is a command, handle it
        print(line)
        if re.match("\$ cd.*", line):
            g = re.search("\$ cd (.*)$", line)
            newdir_name = g.group(1)
            if newdir_name == "..":
                pwd = pwd.parent
            else:
                #check if dir exists
                newdir = pwd.get_file(newdir_name)
                if newdir == None:
                    newdir = MyFile(newdir_name, True, 0, pwd)
                    pwd.add(newdir) 

                pwd = newdir
    else:
        # else it is a listing
        g = re.search("^([\w\d]+) ([\w.]+)$", line)
        newdir_name = g.group(2)
        newdir = pwd.get_file(newdir_name)
        if newdir == None:
            newdir = MyFile(newdir_name, False, 0, pwd)
            if g.group(1) == "dir":
                newdir.is_dir = True
            else:
                newdir.size = int(g.group(1))
            pwd.add(newdir)
            
    i+=1

root.calculate_size()
#root.print()



root.print_dirs_small()

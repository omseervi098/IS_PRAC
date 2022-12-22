import hashlib

class Node:
    def __init__(self, data=None, left=None, right=None):
        self.data = data
        self.hash = hashlib.sha256(str(data).encode("utf-8")).hexdigest()
        self.left = left
        self.right = right

class MerkelTree:
    def __init__(self, leaves):
        self.root = Node(leaves)
        open = [self.root]
        while len(open):
            node = open.pop(0)
            data = node.data
            half_data = len(data)//2
            if half_data:
                new_leaves = [Node(data[:half_data]), Node(data[half_data:])]
                node.left = new_leaves[0]
                node.right = new_leaves[1]
                open.extend(new_leaves)

    def print_tree(self):
        open = [self.root]
        while len(open):
            node = open.pop(0)
            print("")
            print("Content: ", node.data)
            print("Hash: ", node.hash)
            new_right = node.right
            new_left = node.left
            if new_right is not None:
                open = [new_right] + open
            if new_left is not None:
                open = [new_left] + open
            
s = input("Enter the text : ")
tree = MerkelTree(s.split())
tree.print_tree()
import hashlib
class Node:
    def __init__(self,data=None,left=None,right=None):
        self.data = data
        self.hash = hashlib.sha256(str(data).encode('utf-8')).hexdigest()
        self.left = left
        self.right = right
class MerkelTree:
    def __init__(self,leaves):
        #leaves is a list of data
        self.root=None
        nodes=[]
        while len(leaves)>1:
            for i in range(0,len(leaves),2):
                if(i<len(leaves)-1):
                    leaves[i]=Node(leaves[i])
                    leaves[i+1]=Node(leaves[i+1])
                    nodes.append(Node(leaves[i].hash+leaves[i+1].hash,leaves[i],leaves[i+1]))
                else:
                    nodes.append(Node(leaves[i]))
            leaves=nodes
            nodes=[]
        self.root=leaves[0]
    def getRoot(self):
        return self.root
s=input("Enter the string:")
leaves=s.split(" ")
tree=MerkelTree(leaves)
print("Root hash:",tree.getRoot().hash)
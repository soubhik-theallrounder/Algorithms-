class Graph(object):
    def __init__(self, N, M):
        self.N, self.M = N, M
        self.alist = {key:list() for key in range(1, N+1)}
        for index in range(M):
            t, h = [int(value) for value in input().split()]
            self.alist[t].append(h)
            self.alist[h].append(t)
            
    def bfs(self, source):
        distances = {key:-1 for key in range(1, self.N+1)}
        to_explore = set([source])
        current_distance = 0
        while to_explore:
            next_nodes = set()
            for tnode in to_explore:
                if distances[tnode] == -1:
                    distances[tnode] = current_distance
                    next_nodes.update(self.alist[tnode])
            to_explore = next_nodes
            current_distance += 1
        self.distances = distances
        
    def answer(self, source):
        self.bfs(source)
        for index in range(1, N+1):
            if index == source:
                continue
            elif self.distances[index] == -1:
                print(-1, end=" ")
            else:
                print(6 * self.distances[index], end=" ")
        print()
                    
T = int(input())
for index in range(T):
    N, M = [int(value) for value in input().split()]
    graph = Graph(N, M)
    source = int(input())
    graph.answer(source) 
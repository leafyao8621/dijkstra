import dijkstra.cpp
import dijkstra.c

if __name__ == "__main__":
    print("CPP")
    print(dijkstra.cpp.distance("../graph/test.graph", 0, 2, True))
    print("C")
    print(dijkstra.c.distance("../graph/test.graph", 0, 2, True))

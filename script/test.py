import dijkstra.cpp
import dijkstra.c
import dijkstra.native

if __name__ == "__main__":
    print("CPP")
    print(dijkstra.cpp.distance("../graph/test.graph", 0, 2, True))
    print("C")
    print(dijkstra.c.distance("../graph/test.graph", 0, 2, True))
    print("NATIVE")
    print(dijkstra.native.distance("../graph/test.graph", 0, 2, True))

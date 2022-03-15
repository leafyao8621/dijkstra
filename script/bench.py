import timeit
import dijkstra.cpp

if __name__ == "__main__":
    cpp = lambda: dijkstra.cpp.distance("../graph/small.graph", 0, 20)
    print("CPP")
    print(timeit.timeit(cpp))

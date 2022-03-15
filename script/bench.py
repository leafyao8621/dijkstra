import timeit
import dijkstra.cpp
import dijkstra.c
import dijkstra.native

if __name__ == "__main__":
    suite = ["small", "medium", "large"]
    iter = 100
    for i in suite:
        print(f"Graph {i}:")
        cpp = lambda: dijkstra.cpp.distance(f"../graph/{i}.graph", 0, 20)
        print(f"CPP Runtime ({iter} iterations):")
        print(f"{timeit.timeit(cpp, number=iter)} seconds")
        c = lambda: dijkstra.c.distance(f"../graph/{i}.graph", 0, 20)
        print(f"C Runtime ({iter} iterations):")
        print(f"{timeit.timeit(c, number=iter)} seconds")
        native = lambda: dijkstra.native.distance(f"../graph/{i}.graph", 0, 20)
        print(f"NATIVE Runtime ({iter} iterations):")
        print(f"{timeit.timeit(native, number=iter)} seconds")

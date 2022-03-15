import _core

if __name__ == "__main__":
    graph = _core.Graph("../../../graph/test.graph")
    print(graph)
    print("Path:")
    result = graph.distance(0, 4, True)
    print(f"Distance: {result}")

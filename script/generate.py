import dijkstra.generator

if __name__ == "__main__":
    dijkstra.generator.generate(100, 1000, 10, 1000, "../graph/small.graph")
    dijkstra.generator.generate(1000, 10000, 10, 1000, "../graph/medium.graph")
    dijkstra.generator.generate(10000, 100000, 10, 1000, "../graph/large.graph")

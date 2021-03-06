from ._core import Graph

def distance(fn: str, from_idx: int, to_idx: int, verbose: bool=False) -> float:
    """_summary_

    Args:
        fn (str): _description_
        from_idx (int): _description_
        to_idx (int): _description_
        verbose (bool, optional): _description_. Defaults to False.

    Returns:
        float: _description_
    """
    graph = Graph(fn)
    if (verbose):
        print(graph)
    return graph.distance(from_idx, to_idx, verbose)

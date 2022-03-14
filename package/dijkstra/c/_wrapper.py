import dijkstra.c._base

def distance(fn: str, from_idx: int, to_idx: int, verbose: bool) -> float:
    """_summary_

    Args:
        fn (str): _description_
        from_idx (int): _description_
        to_idx (int): _description_
        verbose (bool): _description_

    Returns:
        float: _description_
    """
    return dijkstra.c._base.distance(fn, from_idx, to_idx, verbose)

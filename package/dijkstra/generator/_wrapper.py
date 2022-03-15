import dijkstra.generator._base

def generate(
    n_node: int,
    n_edge: int,
    max_distance: float,
    seed: int,
    ofn: str
):
    """_summary_

    Args:
        n_node (int): _description_
        n_edge (int): _description_
        max_distance (float): _description_
        seed (int): _description_
        ofn (str): _description_
    """
    dijkstra.generator._base.generate(
        n_node,
        n_edge,
        max_distance,
        seed,
        ofn
    )

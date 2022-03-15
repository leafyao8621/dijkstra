import heapq
import collections
import typing

class GraphNode:
    """_summary_
    """
    def __init__(self):
        """_summary_
        """
        self.visited: bool = False
        self.prev: int = -1
        self.distance: float = 0
        self.neighbors: collections.deque[typing.Tuple[int, float]] =\
            collections.deque()

class Graph:
    """_summary_
    """
    def __init__(self, fn: str):
        """_summary_

        Args:
            fn (str): _description_
        """
        with open(fn, "r") as fin:
            buf: str = fin.readline()
            tokens: typing.List[str] = buf.split()
            self._n_node: int = int(tokens[0])
            self._n_edge: int = int(tokens[1])
            self._adjacency_list: typing.List[GraphNode] =\
                [GraphNode() for i in range(self._n_node)]
            max_distance: float = 0
            for i in range(self._n_edge):
                buf: str = fin.readline()
                tokens: typing.List[str] = buf.split()
                self\
                    ._adjacency_list[int(tokens[0])]\
                    .neighbors\
                    .append((int(tokens[1]), float(tokens[2])))
                self\
                    ._adjacency_list[int(tokens[1])]\
                    .neighbors\
                    .append((int(tokens[0]), float(tokens[2])))
                if (float(tokens[2]) > max_distance):
                    max_distance = float(tokens[2])
            self._infinity = max_distance * (self._n_edge + 1)
    def distance(self, from_idx: int, to_idx: int, verbose: bool) -> float:
        """_summary_

        Args:
            from_idx (int): _description_
            to_idx (int): _description_
            verbose (bool): _description_

        Raises:
            Exception: _description_

        Returns:
            float: _description_
        """
        pq: typing.List[typing.Tuple[float, int]] = []
        for i, ii in enumerate(self._adjacency_list):
            ii.visited = False
            ii.prev = -1
            ii.distance = 0 if i == from_idx else self._infinity
            heapq.heappush(pq, (ii.distance, i))
        while (len(pq)):
            cur_distance, cur_idx = heapq.heappop(pq)
            if (self._adjacency_list[cur_idx].visited):
                continue
            self._adjacency_list[cur_idx].visited = True
            if (cur_idx == to_idx):
                break
            for i in self._adjacency_list[cur_idx].neighbors:
                temp_idx, temp_distance = i
                if (
                    cur_distance + temp_distance <\
                    self._adjacency_list[temp_idx].distance
                ):
                    self._adjacency_list[temp_idx].prev = cur_idx
                    self._adjacency_list[temp_idx].distance =\
                        cur_distance + temp_distance
                    heapq.heappush(pq, (cur_distance + temp_distance, temp_idx))
        if (not self._adjacency_list[to_idx].visited):
            raise Exception("NOT_CONNECTED")
        if (verbose):
            i = to_idx
            while (i != from_idx):
                print(f"{i}<-")
                i = self._adjacency_list[i].prev
            print(from_idx)
        return self._adjacency_list[to_idx].distance
    def __str__(self):
        """_summary_

        Returns:
            _type_: _description_
        """
        lines: typing.List[str] = []
        for i, ii in enumerate(self._adjacency_list):
            lines.append(f"Node {i}:")
            for j in ii.neighbors:
                lines.append(f"To: {j[0]} Distance: {j[1]}")
        return "\n".join(lines)

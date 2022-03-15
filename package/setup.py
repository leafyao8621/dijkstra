from setuptools import setup, Extension

cpp_base = Extension('dijkstra.cpp._base',
                     sources=["dijkstra/cpp/src/core/core.cpp",
                              "dijkstra/cpp/src/main.cpp"])

c_base = Extension('dijkstra.c._base',
                   sources=["dijkstra/c/src/core/core.c",
                            "dijkstra/c/src/util/heap.c",
                            "dijkstra/c/src/util/list.c",
                            "dijkstra/c/src/main.c"])

setup(name="dijkstra",
      version="0.1",
      packages=["dijkstra",
                "dijkstra.cpp",
                "dijkstra.c",
                "dijkstra.native",
                "dijkstra.native._core"],
      ext_modules=[cpp_base, c_base])

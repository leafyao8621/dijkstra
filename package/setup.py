from setuptools import setup, Extension

cpp_base = Extension('dijkstra.cpp._base',
                     sources=["dijkstra/cpp/src/core/core.cpp",
                              "dijkstra/cpp/src/main.cpp"])

setup(name="sinstagram",
      version="0.1",
      packages=["dijkstra",
                "dijkstra.cpp"],
      ext_modules=[cpp_base])

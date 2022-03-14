#include <Python.h>
#include "core/core.h"

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

struct module_state {
    PyObject* error;
};

static PyObject* distance(PyObject* self, PyObject* args) {
    const char *fn;
    long from;
    long to;
    int verbose;
    if (!PyArg_ParseTuple(args,
                          "sllp",
                          &fn,
                          &from,
                          &to,
                          &verbose)) {
        return NULL;
    }
    double result = 0;
    try {
        Core::Graph graph(fn);
        result = graph.distance(from, to, verbose);
    } catch (Core::Graph::Err err) {
        switch (err) {
        case Core::Graph::Err::FILE_ACCESS:
            PyErr_SetString(PyExc_RuntimeError, "FILE_ACCESS");
            return NULL;
        case Core::Graph::Err::IDX_OUT_OF_RANGE:
            PyErr_SetString(PyExc_RuntimeError, "IDX_OUT_OF_RANGE");
            return NULL;
        case Core::Graph::Err::NOT_CONNECTED:
            PyErr_SetString(PyExc_RuntimeError, "NOT_CONNECTED");
            return NULL;
        }
    }
    return PyFloat_FromDouble(result);
}


static PyMethodDef _base_methods[] = {
    {"distance", (PyCFunction)distance, METH_VARARGS, NULL},
    {0}
};

static int _base_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int _base_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "dijkstra.cpp._base",
    NULL,
    sizeof(struct module_state),
    _base_methods,
    NULL,
    _base_traverse,
    _base_clear,
    NULL
};

PyMODINIT_FUNC PyInit__base(void) {
    PyObject *module = PyModule_Create(&moduledef);
    if (!module) return NULL;
    return module;
}

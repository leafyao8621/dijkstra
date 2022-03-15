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
    struct Graph graph;
    int ret = graph_initialize(&graph, fn);
    if (ret) {
        goto finalize;
    }
    if (verbose) {
        graph_log(&graph, stdout);
    }
    ret = graph_distance(&graph, from, to, &result, verbose);
    if (ret) {
        goto finalize;
    }
finalize:
    graph_finalize(&graph);
    switch (ret) {
    case ERR_NULL_PTR:
        PyErr_SetString(PyExc_RuntimeError, "NULL_PTR");
        return NULL;
    case ERR_FILE_ACCESS:
        PyErr_SetString(PyExc_RuntimeError, "FILE_ACCESS");
        return NULL;
    case ERR_IDX_OUT_OF_RANGE:
        PyErr_SetString(PyExc_RuntimeError, "IDX_OUT_OF_RANGE");
        return NULL;
    case ERR_NOT_CONNECTED:
        PyErr_SetString(PyExc_RuntimeError, "NOT_CONNECTED");
        return NULL;
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
    "dijkstra.c._base",
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

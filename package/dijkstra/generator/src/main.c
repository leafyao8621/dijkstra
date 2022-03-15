#include <Python.h>
#include "core/core.h"

#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

struct module_state {
    PyObject* error;
};

static PyObject* generate(PyObject* self, PyObject* args) {
    long n_node;
    long n_edge;
    double max_distance;
    long seed;
    const char *ofn;
    if (!PyArg_ParseTuple(args,
                          "lldls",
                          &n_node,
                          &n_edge,
                          &max_distance,
                          &seed,
                          &ofn)) {
        return NULL;
    }
    int ret = core_generate(n_node, n_edge, max_distance, seed, ofn);
    switch (ret) {
    case ERR_TOO_MANY_EDGES:
        PyErr_SetString(PyExc_RuntimeError, "TOO_MANY_EDGES");
        return NULL;
    case ERR_INVALID_SEED:
        PyErr_SetString(PyExc_RuntimeError, "INVALID_SEED");
        return NULL;
    case ERR_FILE_ACCESS:
        PyErr_SetString(PyExc_RuntimeError, "FILE_ACCESS");
        return NULL;
    }
    Py_RETURN_NONE;
}


static PyMethodDef _base_methods[] = {
    {"generate", (PyCFunction)generate, METH_VARARGS, NULL},
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
    "dijkstra.generator._base",
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

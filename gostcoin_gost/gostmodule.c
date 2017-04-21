#include <Python.h>

#include "gost.h"

static PyObject *gost_getpowhash(PyObject *self, PyObject *args)
{
    char *output;
    PyObject *value;
    PyStringObject *input;
    if (!PyArg_ParseTuple(args, "S", &input))
        return NULL;
    Py_INCREF(input);
    output = PyMem_Malloc(32);

    // scrypt_1024_1_1_256((char *)PyString_AsString((PyObject*) input), output);
    // const unsigned char *
    hash_256((const unsigned char *)PyString_AsString((PyObject*) input), output);
    Py_DECREF(input);
    value = Py_BuildValue("s#", output, 32);
    PyMem_Free(output);
    return value;
}

static PyMethodDef GostMethods[] = {
    { "getPoWHash", gost_getpowhash, METH_VARARGS, "Returns the proof of work hash using gost" },
    { NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initgst_gost(void) {
    (void) Py_InitModule("gst_gost", GostMethods);
}

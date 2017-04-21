#include <Python.h>

#include "gost.h"

static PyObject *gost_getpowhash(PyObject *self, PyObject *args)
{
	PyObject *value;
	PyStringObject *input;
	if (!PyArg_ParseTuple(args, "S", &input))
		return NULL;
	Py_INCREF(input);
	uint32_t digest[16] __attribute__((aligned(64)));
	uint32_t hash[8] __attribute__((aligned(32)));

	sph_gost512(
		(unsigned char *)digest,
		(const unsigned char *)PyString_AsString((PyObject*) input),
		(unsigned long long)PyString_Size((PyObject*) input)
	);
	sph_gost256(
		(unsigned char *)hash,
		(const unsigned char *)digest,
		64
	);
	Py_DECREF(input);
	value = Py_BuildValue("s#", hash, 32);
	return value;
}

static PyMethodDef GostMethods[] = {
	{ "getPoWHash", gost_getpowhash, METH_VARARGS, "Returns the proof of work hash using gost" },
	{ NULL, NULL, 0, NULL }
};

PyMODINIT_FUNC initgst_gost(void) {
	(void) Py_InitModule("gst_gost", GostMethods);
}

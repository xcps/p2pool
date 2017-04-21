#include <Python.h>

#include "gost.h"

// int scanhash_gostd(int thr_id, uint32_t *pdata, const uint32_t *ptarget,
//     uint32_t max_nonce, unsigned long *hashes_done)
// {
//     uint32_t data[20] __attribute__((aligned(128)));
//     uint32_t hash[8] __attribute__((aligned(32)));
//     uint32_t digest[16] __attribute__((aligned(64)));
//     const uint32_t Htarg = ptarget[7];

//     for (int i = 0; i < 19; i++) // revert everything but nonce
//         data[i] = swab32(pdata[i]);
//     uint32_t n = pdata[19] - 1;
//     const uint32_t first_nonce = pdata[19];

//     do
//     {
//         data[19] = ++n;
//         sph_gost512 (digest, data, 80);
//         sph_gost256 (hash, digest, 64);


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

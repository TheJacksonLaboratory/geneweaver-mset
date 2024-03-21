#include <Python.h>
#include <vector>
#include <algorithm>
#include "include/mset.h"


static PyObject* wrap_trial(PyObject* self, PyObject* args) {
    PyObject *list1, *list2;
    long u_size;

    // Parse Python arguments: two lists and a long integer
    if (!PyArg_ParseTuple(args, "O!O!l", &PyList_Type, &list1, &PyList_Type, &list2, &u_size)) {
        return NULL; // Return error if parsing fails
    }

    // Convert Python lists to C++ arrays
    long arr_1_size = PyList_Size(list1);
    long arr_2_size = PyList_Size(list2);
    int *arr_1 = new int[arr_1_size];
    int *arr_2 = new int[arr_2_size];

    for (Py_ssize_t i = 0; i < arr_1_size; i++) {
        PyObject *item = PyList_GetItem(list1, i);
        if (!PyLong_Check(item)) {
            delete[] arr_1;
            delete[] arr_2;
            return NULL; // Error if not all items are integers
        }
        arr_1[i] = (int)PyLong_AsLong(item);
    }

    for (Py_ssize_t i = 0; i < arr_2_size; i++) {
        PyObject *item = PyList_GetItem(list2, i);
        if (!PyLong_Check(item)) {
            delete[] arr_1;
            delete[] arr_2;
            return NULL; // Error if not all items are integers
        }
        arr_2[i] = (int)PyLong_AsLong(item);
    }

    // Call the C++ function
    int result = mset_tools::trial(arr_1, arr_2, arr_1_size, arr_2_size, u_size);

    // Cleanup
    delete[] arr_1;
    delete[] arr_2;

    // Convert the result back to Python and return
    return PyLong_FromLong(result);
}

static PyObject* wrap_intersection_size(PyObject* self, PyObject* args) {
    PyObject *list1, *list2;

    // Parse Python arguments: two lists
    if (!PyArg_ParseTuple(args, "O!O!", &PyList_Type, &list1, &PyList_Type, &list2)) {
        return NULL; // Return error if parsing fails
    }

    // Convert Python lists to std::vector<int>
    std::vector<int> vec1, vec2;
    for (Py_ssize_t i = 0; i < PyList_Size(list1); i++) {
        PyObject *item = PyList_GetItem(list1, i);
        if (!PyLong_Check(item)) {
            return PyErr_Format(PyExc_TypeError, "List items must be integers");
        }
        vec1.push_back((int)PyLong_AsLong(item));
    }
    for (Py_ssize_t i = 0; i < PyList_Size(list2); i++) {
        PyObject *item = PyList_GetItem(list2, i);
        if (!PyLong_Check(item)) {
            return PyErr_Format(PyExc_TypeError, "List items must be integers");
        }
        vec2.push_back((int)PyLong_AsLong(item));
    }

    // Sort each vector
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());

    // Remove duplicates from each vector
    vec1.erase(std::unique(vec1.begin(), vec1.end()), vec1.end());
    vec2.erase(std::unique(vec2.begin(), vec2.end()), vec2.end());


    // Call the C++ function
    size_t result = mset_tools::intersection_size(vec1, vec2);

    // Convert the result back to Python and return
    return PyLong_FromSize_t(result);
}

static PyMethodDef methods[] = {
    {"trial", wrap_trial, METH_VARARGS, "Runs a trial and returns the intersection size"},
    {"intersection_size", wrap_intersection_size, METH_VARARGS, "Calculates the size of the intersect of two lists of integers without saving the intersect"},
    {NULL, NULL, 0, NULL} // Sentinel
};

static struct PyModuleDef module = {
    PyModuleDef_HEAD_INIT,
    "mset", // Module name
    NULL, // Module docstring (could be filled in)
    -1,   // Size of per-interpreter state of the module, or -1 if the module keeps state in global variables.
    methods
};

PyMODINIT_FUNC PyInit_mset(void) {
    return PyModule_Create(&module);
}

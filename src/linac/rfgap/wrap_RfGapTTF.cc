#include "orbit_mpi.hh"
#include "pyORBIT_Object.hh"

#include "wrap_RfGapTTF.hh"
#include "wrap_linacmodule.hh"
#include "wrap_bunch.hh"

#include <iostream>

#include "wrap_utils.hh"
#include "RfGapTTF.hh"
#include "OU_Polynomial.hh"

using namespace OrbitUtils;

namespace wrap_linac{

#ifdef __cplusplus
extern "C" {
#endif

	//---------------------------------------------------------
	//Python RfGapTTF class definition
	//---------------------------------------------------------

	//constructor for python class wrapping RfGapTTF instance
	//It never will be called directly
	static PyObject* RfGapTTF_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
	{
		pyORBIT_Object* self;
		self = (pyORBIT_Object *) type->tp_alloc(type, 0);
		self->cpp_obj = NULL;
		//std::cerr<<"The RfGapTTF new has been called!"<<std::endl;
		return (PyObject *) self;
	}

  //initializator for python  RfGapTTF class
  //this is implementation of the __init__ method
  static int RfGapTTF_init(pyORBIT_Object *self, PyObject *args, PyObject *kwds){
		self->cpp_obj = new RfGapTTF();	
		((RfGapTTF*) self->cpp_obj)->setPyWrapper((PyObject*) self);
		return 0;
  }
			
	//trackBunch(Bunch* bunch)
  static PyObject* RfGapTTF_trackBunch(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;
		PyObject* pyBunch;
	  double frequency, e0tl, phase, ampl;		
		if(!PyArg_ParseTuple(args,"Odddd:trackBunch",&pyBunch,&frequency,&ampl,&e0tl,&phase)){
			ORBIT_MPI_Finalize("PyRfGapTTF - trackBunch(Bunch* bunch, freq, ampl, E0TL, phase) - parameters are needed.");
		}
		PyObject* pyORBIT_Bunch_Type = wrap_orbit_bunch::getBunchType("Bunch");
		if(!PyObject_IsInstance(pyBunch,pyORBIT_Bunch_Type)){
			ORBIT_MPI_Finalize("PyRfGapTTF - trackBunch(Bunch* bunch, freq, ampl, E0TL, phase) - first param. should be a Bunch.");
		}
		Bunch* cpp_bunch = (Bunch*) ((pyORBIT_Object*)pyBunch)->cpp_obj;
		cpp_RfGapTTF->trackBunch(cpp_bunch,frequency,ampl,e0tl,phase);
		Py_INCREF(Py_None);
    return Py_None;	
	}		
	
	//setT_TTF() returns the Polynomial instance for T Transit Time Factor
  static PyObject* RfGapTTF_setT_TTF(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;
		PyObject* pyPolynomial;
		if(!PyArg_ParseTuple(args,"O:setT_TTF",&pyPolynomial)){
			ORBIT_MPI_Finalize("PyRfGapTTF - setT_TTF(Polynomial) - parameter is needed.");
		}		
		PyObject* pyORBIT_Polynomial_Type = wrap_orbit_utils::getOrbitUtilsType("Polynomial");
		if(!PyObject_IsInstance(pyPolynomial,pyORBIT_Polynomial_Type)){
			ORBIT_MPI_Finalize("PyRfGapTTF - setT_TTF(Polynomial) - the param. should be a Polynomial.");
		}		
		Polynomial* cpp_poly = (Polynomial*) ((pyORBIT_Object*)pyPolynomial)->cpp_obj;
		cpp_RfGapTTF->setT_TTF(cpp_poly);
		Py_INCREF(Py_None);
    return Py_None;		
	}	
	
	//setS_TTF() returns the Polynomial instance for T Transit Time Factor
  static PyObject* RfGapTTF_setS_TTF(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;
		PyObject* pyPolynomial;
		if(!PyArg_ParseTuple(args,"O:setS_TTF",&pyPolynomial)){
			ORBIT_MPI_Finalize("PyRfGapTTF - setS_TTF(Polynomial) - parameter is needed.");
		}		
		PyObject* pyORBIT_Polynomial_Type = wrap_orbit_utils::getOrbitUtilsType("Polynomial");
		if(!PyObject_IsInstance(pyPolynomial,pyORBIT_Polynomial_Type)){
			ORBIT_MPI_Finalize("PyRfGapTTF - setS_TTF(Polynomial) - the param. should be a Polynomial.");
		}		
		Polynomial* cpp_poly = (Polynomial*) ((pyORBIT_Object*)pyPolynomial)->cpp_obj;
		cpp_RfGapTTF->setS_TTF(cpp_poly);
		Py_INCREF(Py_None);
    return Py_None;		
	}		
	
	//getT_TTF() returns the Polynomial instance for T Transit Time Factor
  static PyObject* RfGapTTF_getT_TTF(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;
		PyObject* mod = PyImport_ImportModule("orbit_utils");
		pyORBIT_Object* pyPoly = (pyORBIT_Object*) PyObject_CallMethod(mod,"Polynomial","O",Py_BuildValue("i",0));
		Polynomial* cpp_poly = (Polynomial*) ((pyORBIT_Object*)pyPoly)->cpp_obj;
		cpp_RfGapTTF->getT_TTF()->copyTo(cpp_poly);
    return (PyObject*) pyPoly;	
	}		
	
	//getS_TTF() returns the Polynomial instance for T Transit Time Factor
  static PyObject* RfGapTTF_getS_TTF(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;
		PyObject* mod = PyImport_ImportModule("orbit_utils");
		pyORBIT_Object* pyPoly = (pyORBIT_Object*) PyObject_CallMethod(mod,"Polynomial","O",Py_BuildValue("i",0));
		Polynomial* cpp_poly = (Polynomial*) ((pyORBIT_Object*)pyPoly)->cpp_obj;
		cpp_RfGapTTF->getS_TTF()->copyTo(cpp_poly);
    return (PyObject*) pyPoly;	
	}	

	//setParameters() Sets up the gap parameters: T,S, minimal and maximal beta, 
  //rf frequency, the gap length,  and the relative amplitude
  static PyObject* RfGapTTF_setParameters(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;
		PyObject* pyPolynomialT;
		PyObject* pyPolynomialS;
		double beta_min,beta_max,rf_frequency,gap_length,relative_amplitude;
		if(!PyArg_ParseTuple(args,"OOddddd:setParameters",&pyPolynomialT,&pyPolynomialS,
			                   &beta_min,&beta_max,&rf_frequency,&gap_length,
												  &relative_amplitude))
		{
			ORBIT_MPI_Finalize("RfGapTTF - setParameters(...) - parameters are needed.");
		}		
		PyObject* pyORBIT_Polynomial_Type = wrap_orbit_utils::getOrbitUtilsType("Polynomial");
		if(!PyObject_IsInstance(pyPolynomialT,pyORBIT_Polynomial_Type) || 
			 !PyObject_IsInstance(pyPolynomialS,pyORBIT_Polynomial_Type))
		{
			ORBIT_MPI_Finalize("RfGapTTF - setParameters(PolyT,PolyS,...) - 2 first should be a Polynomial.");
		}	
		Polynomial* cpp_polyT = (Polynomial*) ((pyORBIT_Object*)pyPolynomialT)->cpp_obj;
		Polynomial* cpp_polyS = (Polynomial*) ((pyORBIT_Object*)pyPolynomialS)->cpp_obj;
		cpp_RfGapTTF->setParameters(cpp_polyT,cpp_polyS,beta_min,beta_max,rf_frequency,
			                          gap_length,relative_amplitude);
		Py_INCREF(Py_None);
    return Py_None;		
	}	
		
	//getBetaMinMax() returns the (beat_min,beta_max) tuple.
  static PyObject* RfGapTTF_getBetaMinMax(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;	
		double beta_min = cpp_RfGapTTF->getBetaMin();
		double beta_max = cpp_RfGapTTF->getBetaMax();
		return Py_BuildValue("(dd)",beta_min,beta_max);
	}
	
	//getFrequency() returns the RF frequency.
  static PyObject* RfGapTTF_getFrequency(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;	
		return Py_BuildValue("d",cpp_RfGapTTF->getFrequency());
	}
	
	//getLength() returns the RF frequency.
  static PyObject* RfGapTTF_getLength(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;	
		return Py_BuildValue("d",cpp_RfGapTTF->getLength());
	}
	
	//getRelativeAmplitude() returns the RF frequency.
  static PyObject* RfGapTTF_getRelativeAmplitude(PyObject *self, PyObject *args){
    pyORBIT_Object* pyRfGapTTF = (pyORBIT_Object*) self;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) pyRfGapTTF->cpp_obj;	
		return Py_BuildValue("d",cpp_RfGapTTF->getRelativeAmplitude());
	}
	
  //-----------------------------------------------------
  //destructor for python RfGapTTF class (__del__ method).
  //-----------------------------------------------------
  static void RfGapTTF_del(pyORBIT_Object* self){
		//std::cerr<<"The RfGapTTF __del__ has been called!"<<std::endl;
		RfGapTTF* cpp_RfGapTTF = (RfGapTTF*) self->cpp_obj;
		delete cpp_RfGapTTF;
		self->ob_type->tp_free((PyObject*)self);
  }
	
	// defenition of the methods of the python RfGapTTF wrapper class
	// they will be vailable from python level
  static PyMethodDef RfGapTTFClassMethods[] = {
		{ "trackBunch",     RfGapTTF_trackBunch,    METH_VARARGS,"tracks the Bunch through the RF gap."},
		{ "getT_TTF",       RfGapTTF_getT_TTF,      METH_VARARGS,"get the T TTF Polynomial of the gap model."},
		{ "getS_TTF",       RfGapTTF_getS_TTF,      METH_VARARGS,"get the S TTF Polynomial of the gap model."},
		{ "setT_TTF",       RfGapTTF_setT_TTF,      METH_VARARGS,"set the T TTF Polynomial to the gap model."},
		{ "setS_TTF",       RfGapTTF_setS_TTF,      METH_VARARGS,"set the S TTF Polynomial to the gap model."},
		{ "setParameters",         RfGapTTF_setParameters,       METH_VARARGS,"sets parameters (Tttf,Sttf,b0,b1,rfFreq,L,Amp)."},		
		{ "getBetaMinMax",         RfGapTTF_getBetaMinMax,       METH_VARARGS,"returns (beta_min,beta_max)."},
		{ "getFrequency",          RfGapTTF_getFrequency,        METH_VARARGS,"returns the RF frequency."},
		{ "getLength",             RfGapTTF_getLength,           METH_VARARGS,"returns the RF length. "},
		{ "getRelativeAmplitude",  RfGapTTF_getRelativeAmplitude,METH_VARARGS,"returns the RF gap relative amplitude."},
    {NULL}
  };

	// defenition of the memebers of the python RfGapTTF wrapper class
	// they will be vailable from python level
	static PyMemberDef RfGapTTFClassMembers [] = {
		{NULL}
	};

	//new python RfGapTTF wrapper type definition
	static PyTypeObject pyORBIT_RfGapTTF_Type = {
		PyObject_HEAD_INIT(NULL)
		0, /*ob_size*/
		"RfGapTTF", /*tp_name*/
		sizeof(pyORBIT_Object), /*tp_basicsize*/
		0, /*tp_itemsize*/
		(destructor) RfGapTTF_del , /*tp_dealloc*/
		0, /*tp_print*/
		0, /*tp_getattr*/
		0, /*tp_setattr*/
		0, /*tp_compare*/
		0, /*tp_repr*/
		0, /*tp_as_number*/
		0, /*tp_as_sequence*/
		0, /*tp_as_mapping*/
		0, /*tp_hash */
		0, /*tp_call*/
		0, /*tp_str*/
		0, /*tp_getattro*/
		0, /*tp_setattro*/
		0, /*tp_as_buffer*/
		Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
		"The RfGapTTF python wrapper", /* tp_doc */
		0, /* tp_traverse */
		0, /* tp_clear */
		0, /* tp_richcompare */
		0, /* tp_weaklistoffset */
		0, /* tp_iter */
		0, /* tp_iternext */
		RfGapTTFClassMethods, /* tp_methods */
		RfGapTTFClassMembers, /* tp_members */
		0, /* tp_getset */
		0, /* tp_base */
		0, /* tp_dict */
		0, /* tp_descr_get */
		0, /* tp_descr_set */
		0, /* tp_dictoffset */
		(initproc) RfGapTTF_init, /* tp_init */
		0, /* tp_alloc */
		RfGapTTF_new, /* tp_new */
	};	

	//--------------------------------------------------
	//Initialization function of the pyRfGapTTF class
	//It will be called from Bunch wrapper initialization
	//--------------------------------------------------
  void initRfGapTTF(PyObject* module){
		if (PyType_Ready(&pyORBIT_RfGapTTF_Type) < 0) return;
		Py_INCREF(&pyORBIT_RfGapTTF_Type);
		PyModule_AddObject(module, "RfGapTTF", (PyObject *)&pyORBIT_RfGapTTF_Type);
	}

#ifdef __cplusplus
}
#endif

//end of namespace wrap_linac
}
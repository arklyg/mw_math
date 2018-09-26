#ifndef _MW_MATH_FUNCTION_H_
#define _MW_MATH_FUNCTION_H_

#include <math.h>

#include <mwsingleton.h>
#include <proclockable.h>
#include <mwserializablesingleton.h>

#include "mwmatrix.h"

enum MWMathFunctionType
{
	MWMathFunctionTypeDerivable,
	MWMathFunctionTypeUnderivable
};

class MWMathFunction;

typedef MWMatrix<MWData> &(MWMathFunction::* MWMathFunctionFunctionHandleAssignMatrixWithMatrix)(const MWMatrix<MWData> &, MWMatrix<MWData> &) const;
typedef MWMatrix<MWData> (MWMathFunction::* MWMathFunctionFunctionHandleGetMatrixWithMatrix)(const MWMatrix<MWData> &) const;
typedef MWVector<MWData> &(MWMathFunction::* MWMathFunctionFunctionHandleAssignVectorWithVector)(const MWVector<MWData> &, MWVector<MWData> &) const;
typedef MWVector<MWData> (MWMathFunction::* MWMathFunctionFunctionHandleGetVectorWithVector)(const MWVector<MWData> &) const;

class MWMathFunction : public MWSerializableSingleton
{
protected:
	static pthread_cond_t _start_cond;
	static pthread_cond_t _end_cond;
	static ProcLockable _start_lock;
	//static ProcLockable _finished_lock;
	static ProcLockable _end_lock;
	static vector<pthread_t> _thread_id_vector;
	static vector<size_t> _worker_id_vector;
	static vector<bool> _work_signal;

	static size_t _finished_count;
	static const MWMathFunction* _work_instance;
	static MWMathFunctionFunctionHandleAssignMatrixWithMatrix _assign_value_matrix_function_pt;
	static const MWVector<MWMatrix<MWData> >* _input_pt;
	static MWVector<MWMatrix<MWData> >* _ret_pt;

	static bool _is_exit;

protected:
	MWMatrix<MWData> &assign_multi_result(const MWMatrix<MWData> &input, const MWMathFunctionFunctionHandleAssignVectorWithVector function_handle, MWMatrix<MWData> &ret) const;
	MWMatrix<MWData> get_multi_result(const MWMatrix<MWData> &input, const MWMathFunctionFunctionHandleGetVectorWithVector function_handle) const;
	MWVector<MWMatrix<MWData> > &assign_multi_result(const MWVector<MWMatrix<MWData> > &input, const MWMathFunctionFunctionHandleAssignMatrixWithMatrix function_handle, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0) const;
	MWVector<MWMatrix<MWData> > get_multi_result(const MWVector<MWMatrix<MWData> > &input, const MWMathFunctionFunctionHandleGetMatrixWithMatrix function_handle) const;

	MWVector<MWMatrix<MWData> > &assign_value_vector_matrix_multi_thread_operation(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret, MWMathFunctionFunctionHandleAssignMatrixWithMatrix assign_value_matrix_function_pt) const;

public:
	static void initialize(size_t thread_num);
	static void finalize();

	static void* run(void* arg);

	virtual ~MWMathFunction();

	MWVector<MWData> get_value(const MWVector<MWData> &input) const;

	MWMatrix<MWData> get_value_matrix_structure(const MWMatrix<MWData> &input) const;
	MWMatrix<MWData> &assign_value_matrix(const MWMatrix<MWData> &input, MWMatrix<MWData> &ret) const;
	MWMatrix<MWData> get_value_matrix(const MWMatrix<MWData> &input) const;

	MWVector<MWMatrix<MWData> > get_value_vector_matrix_structure(const MWVector<MWMatrix<MWData> > &input) const;
	MWVector<MWMatrix<MWData> > &assign_value_vector_matrix(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret, size_t off = 0, size_t len = 0) const;
	MWVector<MWMatrix<MWData> > &assign_value_vector_matrix_multi_thread(const MWVector<MWMatrix<MWData> > &input, MWVector<MWMatrix<MWData> > &ret) const;
	MWVector<MWMatrix<MWData> > get_value_vector_matrix(const MWVector<MWMatrix<MWData> > &input) const;

	virtual MWVector<MWData> get_value_structure(const MWVector<MWData> &input) const = 0;
	virtual MWVector<MWData> &assign_value(const MWVector<MWData> &input, MWVector<MWData> &ret) const = 0;

	virtual MWMathFunctionType get_type() const = 0;
};

#endif

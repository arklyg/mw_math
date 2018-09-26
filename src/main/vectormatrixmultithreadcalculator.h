#include <proclockable.h>
#include "mwmatrixhelper.h"

#define VECTORMATRIXMULTITHREADCALCULATOR_FUNCTION_ARG_COUNT_MAX 2

enum VectorMatrixMultiThreadCalculatorFunctionType
{
	VectorMatrixMultiThreadCalculatorFunctionType222,
	VectorMatrixMultiThreadCalculatorFunctionType221,
	VectorMatrixMultiThreadCalculatorFunctionType220,
	VectorMatrixMultiThreadCalculatorFunctionType212,
	VectorMatrixMultiThreadCalculatorFunctionType22,
};

class VectorMatrixMultiThreadCalculator;

typedef MWVector<MWMatrix<MWData> > &(* AssignFunction222Pt)(const MWVector<MWMatrix<MWData> > &, const MWVector<MWMatrix<MWData> > &, MWVector<MWMatrix<MWData> > &, size_t, size_t);
typedef MWVector<MWMatrix<MWData> > &(* AssignFunction221Pt)(const MWVector<MWMatrix<MWData> > &, const MWMatrix<MWData> &, MWVector<MWMatrix<MWData> > &, size_t, size_t);
typedef MWVector<MWMatrix<MWData> > &(* AssignFunction220Pt)(const MWVector<MWMatrix<MWData> > &, const MWData &, MWVector<MWMatrix<MWData> > &, size_t, size_t);
typedef MWVector<MWMatrix<MWData> > &(* AssignFunction212Pt)(const MWMatrix<MWData> &, const MWVector<MWMatrix<MWData> > &, MWVector<MWMatrix<MWData> > &, size_t, size_t);
typedef MWVector<MWMatrix<MWData> > &(* AssignFunction22Pt)(const MWVector<MWMatrix<MWData> > &, MWVector<MWMatrix<MWData> > &, size_t, size_t);
typedef MWVector<MWMatrix<MWData> > &(* AssignFunction21Pt)(const MWMatrix<MWData> &, MWVector<MWMatrix<MWData> > &, size_t, size_t);

class VectorMatrixMultiThreadCalculator
{
private:
	static pthread_cond_t _start_cond;
	static pthread_cond_t _finish_cond;
	static ProcLockable _start_lock;
	static ProcLockable _finish_lock;
	static vector<pthread_t> _thread_id_vector;
	static vector<size_t> _worker_id_vector;
	static vector<bool> _start_signal_vector;

	static size_t _finished_count;
	static VectorMatrixMultiThreadCalculatorFunctionType _function_type;
	static void* _function_handle;
	static vector<const void*> _arg_pt_vector;
	static MWVector<MWMatrix<MWData> >* _ret_pt;

	static bool _is_exit;

private:
	static MWVector<MWMatrix<MWData> > &assign_plus_222(const MWVector<MWMatrix<MWData> > &v_m1, const MWVector<MWMatrix<MWData> > &v_m2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);
	static MWVector<MWMatrix<MWData> > &assign_minus_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);
	static MWVector<MWMatrix<MWData> > &assign_times_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);
	static MWVector<MWMatrix<MWData> > &assign_times_transformed_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);
	static MWVector<MWMatrix<MWData> > &assign_diagonaled_times_transformed_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);
	static MWVector<MWMatrix<MWData> > &assign_diagonaled_times_222(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);

	static MWVector<MWMatrix<MWData> > &assign_plus_221(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);
	static MWVector<MWMatrix<MWData> > &assign_times_221(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);
	static MWVector<MWMatrix<MWData> > &assign_diagonaled_times_transformed_221(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);

	static MWVector<MWMatrix<MWData> > &assign_times_220(const MWVector<MWMatrix<MWData> > &v, const MWData &scale, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);

	static MWVector<MWMatrix<MWData> > &assign_times_212(const MWMatrix<MWData> &m, const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);

	static MWVector<MWMatrix<MWData> > &assign_square_22(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);
	static MWVector<MWMatrix<MWData> > &assign_22(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len);

	static MWVector<MWMatrix<MWData> > &assign_sum_22(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &mid_ret, size_t off, size_t len);

	static void assign_work_description(size_t worker_id, size_t work_size, size_t &off, size_t &work_load);

	static void assign_operation_222(void* function_handle, size_t worker_id);
	static void assign_operation_221(void* function_handle, size_t worker_id);
	static void assign_operation_220(void* function_handle, size_t worker_id);
	static void assign_operation_212(void* function_handle, size_t worker_id);
	static void assign_operation_22(void* function_handle, size_t worker_id);

	static void* run(void* arg);

	static MWVector<MWMatrix<MWData> > &assign_operate_multi_thread(VectorMatrixMultiThreadCalculatorFunctionType function_type, void* function_handle, const void* v1_pt, const void* v2_pt, MWVector<MWMatrix<MWData> >* ret_pt);

public:
	static void initialize(size_t thread_num);
	static void finalize();

	static MWVector<MWVector<MWMatrix<MWData> > > &assign_times_transformed(const MWVector<MWVector<MWMatrix<MWData> > > &v_m1, const MWVector<MWVector<MWMatrix<MWData> > > &v_m2, MWVector<MWVector<MWMatrix<MWData> > > &ret);

	static MWVector<MWMatrix<MWData> > &assign_plus(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret);
	static MWVector<MWMatrix<MWData> > &assign_minus(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret);
	static MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret);
	static MWVector<MWMatrix<MWData> > &assign_times_transformed(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret);
	static MWVector<MWMatrix<MWData> > &assign_diagonaled_times_transformed(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret);
	static MWVector<MWMatrix<MWData> > &assign_diagonaled_times(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret);

	static MWVector<MWMatrix<MWData> > &assign_plus(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret);
	static MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret);
	static MWVector<MWMatrix<MWData> > &assign_diagonaled_times_transformed(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret);

	static MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v, const MWData &scale, MWVector<MWMatrix<MWData> > &ret);

	static MWVector<MWMatrix<MWData> > &assign_times(const MWMatrix<MWData> &m, const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret);

	static MWVector<MWMatrix<MWData> > &assign_square(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret);
	static MWVector<MWMatrix<MWData> > &assign(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret);

	static MWMatrix<MWData> &assign_sum(const MWVector<MWMatrix<MWData> > &v, MWMatrix<MWData> &ret);
};

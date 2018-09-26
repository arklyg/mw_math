#include <mwlogger.h>

#include <mwmathglobal.h>
#include <mwvector.h>
#include <mwmatrix.h>
#include <mwmatrixhelper.h>
#include <linearfunction.h>
#include <logsigfunction.h>
#include <randomfunction.h>
#include <fixedareasinbycountfunction.cpp>
#include <fixedareasinupbycountfunction.cpp>
#include <normalizefunction.cpp>

#define PROGRAMM_NAME "mwmathordinarytest"

int main(int argc, const char* argv[])
{
	init_logger(PROGRAMM_NAME);

	cout.precision(20);

	LOG_INFO(_logger, "vector test:");

	MWVector<MWData> v1(3);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	LOG_INFO(_logger, "v1 = " << v1);

	MWVector<MWData> v2 = v1 + v1;
	LOG_INFO(_logger, "v2 = " << v2);

	v2 += v1;
	LOG_INFO(_logger, "v2 = " << v2);

	MWVector<MWData> v3 = v1 + (MWData) 1;
	LOG_INFO(_logger, "v3 = " << v3);

	MWVector<MWData> v4 = v3 - v1;
	LOG_INFO(_logger, "v4 = " << v4);

	v4 -= v1;
	LOG_INFO(_logger, "v4 = " << v4);

	MWVector<MWData> v5 = v1 * 3;
	LOG_INFO(_logger, "v5 = " << v5);
	
	v5 = v1 * v2;
	LOG_INFO(_logger, "v5 = " << v5);
	
	MWVector<MWData> v6 = v5 / (MWData) 2;
	LOG_INFO(_logger, "v6 = " << v6);

	MWVector<MWData> v7 = - v6;
	LOG_INFO(_logger, "v7 = " << v7);

	LOG_INFO(_logger, "matrix test:");

	MWMatrix<MWData> m1(3, 3);
	LOG_INFO(_logger, "m1 = " << m1);

	MWMatrix<MWData> m2(3, 3, 1);
	LOG_INFO(_logger, "m2 = " << m2);

	MWMatrix<MWData> m3(MWMatrixInfo(3, 3));
	LOG_INFO(_logger, "m3 = " << m3);

	MWMatrix<MWData> m4(MWMatrixInfo(3, 3), 2);
	LOG_INFO(_logger, "m4 = " << m4);

	MWMatrix<MWData> m5(v1, MWVectorAsMatrixTypeRow);
	LOG_INFO(_logger, "m5 = " << m5);

	MWMatrix<MWData> m6(v1, MWVectorAsMatrixTypeColumn);
	LOG_INFO(_logger, "m6 = " << m6);

	MWMatrix<MWData> m7(v1, MWVectorAsMatrixTypeDiagonal);
	LOG_INFO(_logger, "m7 = " << m7);

	MWMatrix<MWData> m8(v1);
	LOG_INFO(_logger, "m8 = " << m8);

	MWVector<MWMatrix<MWData> > vector_matrix(3);
	vector_matrix[0] = m1;
	vector_matrix[1] = m4;
	vector_matrix[2] = m7;
	LOG_INFO(_logger, "vector_matrix = " << vector_matrix);

	MWMatrix<MWData> big_matrix(vector_matrix);
	LOG_INFO(_logger, "big_matrix = " << big_matrix);
	
	LOG_INFO(_logger, "big_matrix.get_matrix_info() = " << big_matrix.get_matrix_info());
	LOG_INFO(_logger, "big_matrix.get_row_num() = " << big_matrix.get_row_num());
	LOG_INFO(_logger, "big_matrix.get_column_num() = " << big_matrix.get_column_num());

	MWMatrix<MWData> m9 = m8;
	LOG_INFO(_logger, "m9 = " << m9);

	//MWMatrix<MWData> m10 = m8 + m9;
	MWMatrix<MWData> m10(m8.get_matrix_info());
	assign_plus(m8, m9, m10);
	LOG_INFO(_logger, "m10 = " << m10);

	//m10 += m8;
	assign_plus(m10, m8, m10);
	LOG_INFO(_logger, "m10 = " << m10);

	//MWMatrix<MWData> m11 = m10 - m4;
	MWMatrix<MWData> m11(m10.get_matrix_info());
	assign_minus(m10, m4, m11);
	LOG_INFO(_logger, "m11 = " << m11);

	MWMatrix<MWData> m12 = - m11;
	LOG_INFO(_logger, "m12 = " << m12);

	//m12 -= m11;
	assign_minus(m12, m11, m12);
	LOG_INFO(_logger, "m12 = " << m12);

	//MWMatrix<MWData> m13 = m11 * m12;
	MWMatrix<MWData> m13(m11.get_row_num(), m12.get_column_num());
	assign_times(m11, m12, m13);
	LOG_INFO(_logger, "m13 = " << m13);

	//MWMatrix<MWData> m14 = m13 * 2;
	MWMatrix<MWData> m14(m13.get_matrix_info());
	assign_times(m13, 2, m14);
	LOG_INFO(_logger, "m14 = " << m14);

	MWVector<MWMatrix<MWData> > vector_matrix_2 = m14 * vector_matrix;
	LOG_INFO(_logger, "vector_matrix_2 = " << vector_matrix_2);

	MWMatrix<MWData> m15 = m14 / 3;
	LOG_INFO(_logger, "m15 = " << m15);

	MWMatrix<MWData> big_matrix_2 = big_matrix.t();
	LOG_INFO(_logger, "big_matrix_2 = " << big_matrix_2);
	LOG_INFO(_logger, "big_matrix_2.get_matrix_info() = " << big_matrix_2.get_matrix_info());
	LOG_INFO(_logger, "big_matrix_2.get_row_num() = " << big_matrix_2.get_row_num());
	LOG_INFO(_logger, "big_matrix_2.get_column_num() = " << big_matrix_2.get_column_num());

	m1.add_row(MWVector<MWData>(3, 1));
	LOG_INFO(_logger, "m1 = " << m1);

	m2.add_column(MWVector<MWData>(3, 1));
	LOG_INFO(_logger, "m2 = " << m2);

	MWMatrix<MWData> m = big_matrix.get_row_as_matrix(2, MWVectorAsMatrixTypeRow);
	LOG_INFO(_logger, "m = " << m);

	m = big_matrix.get_row_as_matrix(2, MWVectorAsMatrixTypeColumn);
	LOG_INFO(_logger, "m = " << m);

	m = big_matrix.get_row_as_matrix(2, MWVectorAsMatrixTypeDiagonal);
	LOG_INFO(_logger, "m = " << m);

	m = big_matrix.get_column_as_matrix(2, MWVectorAsMatrixTypeRow);
	LOG_INFO(_logger, "m = " << m);

	m = big_matrix.get_column_as_matrix(2, MWVectorAsMatrixTypeColumn);
	LOG_INFO(_logger, "m = " << m);

	m = big_matrix.get_column_as_matrix(2, MWVectorAsMatrixTypeDiagonal);
	LOG_INFO(_logger, "m = " << m);

	MWVector<MWData> v = big_matrix.get_row_as_vector(2);
	LOG_INFO(_logger, "v = " << v);

	v = big_matrix.get_column_as_vector(2);
	LOG_INFO(_logger, "v = " << v);

	m = big_matrix.get_row_average();
	LOG_INFO(_logger, "m = " << m);

	m = big_matrix.get_column_average();
	LOG_INFO(_logger, "m = " << m);

	LOG_INFO(_logger, "LinearFunction::get_instance()->get_value(" << v1 << ") = " << LinearFunction::get_instance()->get_value(v1));
	LOG_INFO(_logger, "LinearFunction::get_instance()->get_value_matrix(" << m4 << ") = " << LinearFunction::get_instance()->get_value_matrix(m4));
	LOG_INFO(_logger, "LinearFunction::get_instance()->get_value_vector_matrix(" << vector_matrix << ") = " << LinearFunction::get_instance()->get_value_vector_matrix(vector_matrix));
	LOG_INFO(_logger, "LinearFunction::get_instance()->get_derivative(" << v1 << ") = " << LinearFunction::get_instance()->get_derivative(v1));
	LOG_INFO(_logger, "LinearFunction::get_instance()->get_derivative_matrix(" << m4 << ") = " << LinearFunction::get_instance()->get_derivative_matrix(m4));
	LOG_INFO(_logger, "LinearFunction::get_instance()->get_derivative_vector_matrix(" << vector_matrix << ") = " << LinearFunction::get_instance()->get_derivative_vector_matrix(vector_matrix));

	LOG_INFO(_logger, "LogsigFunction::get_instance()->get_value(" << v1 << ") = " << LogsigFunction::get_instance()->get_value(v1));
	LOG_INFO(_logger, "LogsigFunction::get_instance()->get_value_matrix(" << m4 << ") = " << LogsigFunction::get_instance()->get_value_matrix(m4));
	LOG_INFO(_logger, "LogsigFunction::get_instance()->get_value_vector_matrix(" << vector_matrix << ") = " << LogsigFunction::get_instance()->get_value_vector_matrix(vector_matrix));
	LOG_INFO(_logger, "LogsigFunction::get_instance()->get_derivative(" << v1 << ") = " << LogsigFunction::get_instance()->get_derivative(v1));
	LOG_INFO(_logger, "LogsigFunction::get_instance()->get_derivative_matrix(" << m4 << ") = " << LogsigFunction::get_instance()->get_derivative_matrix(m4));
	LOG_INFO(_logger, "LogsigFunction::get_instance()->get_derivative_vector_matrix(" << vector_matrix << ") = " << LogsigFunction::get_instance()->get_derivative_vector_matrix(vector_matrix));

	RandomFunction::get_instance()->initialize();
	LOG_INFO(_logger, "RandomFunction::get_instance()->get_value(" << v1 << ") = " << RandomFunction::get_instance()->get_value(v1));
	LOG_INFO(_logger, "RandomFunction::get_instance()->get_value_matrix(" << m4 << ") = " << RandomFunction::get_instance()->get_value_matrix(m4));
	LOG_INFO(_logger, "RandomFunction::get_instance()->get_value_vector_matrix(" << vector_matrix << ") = " << RandomFunction::get_instance()->get_value_vector_matrix(vector_matrix));

	MWVector<MWData> nf_test(5);
	nf_test[1] = 100;
	nf_test[2] = 200;
	nf_test[3] = 1;
	nf_test[4] = 2;
	nf_test[0] = 130;
	LOG_INFO(_logger, "NormalizeFunction::get_instance()->get_value(" << nf_test << ") = " << NormalizeFunction::get_instance()->get_value(nf_test));

	MWVector<MWData> p_vector(2);
	MWMatrix<MWData> a_matrix;
	MWData square;
	for (size_t i = 1, j; i < 100; ++ i)
	{
		p_vector[1] = i;
		MWMatrix<MWData> p_matrix;
		for (j = 0; j < i; ++ j)
		{
			p_vector[0] = j;
			p_matrix.add_row(p_vector);
		}
		a_matrix = FixedAreaSinByCountFunction::get_instance()->get_value_matrix(p_matrix);
		square = 0;
		for (j = 0; j < i; ++ j)
		{
			square += a_matrix._data[j][0];
		}
		LOG_INFO(_logger, "FixedAreaSinByCountFunction: i = " << i << ", a_matrix " << a_matrix << ", square = " << square);
	}

	for (size_t i = 1, j; i < 100; ++ i)
	{
		p_vector[1] = i;
		MWMatrix<MWData> p_matrix;
		for (j = 0; j < i; ++ j)
		{
			p_vector[0] = j;
			p_matrix.add_row(p_vector);
		}
		a_matrix = FixedAreaSinUpByCountFunction::get_instance()->get_value_matrix(p_matrix);
		square = 0;
		for (j = 0; j < i; ++ j)
		{
			square += a_matrix._data[j][0];
		}
		LOG_INFO(_logger, "FixedAreaSinUpByCountFunction: i = " << setprecision(20) << i << ", a_matrix " << a_matrix << ", square = " << square);
	}

	vector_matrix[0]._data[0][0] = 2;
	vector_matrix[0]._data[1][0] = 3;
	vector_matrix[0]._data[1][1] = 5;
	vector_matrix[0]._data[2][1] = 7;
	vector_matrix_2[0]._data[0][2] = 2;
	vector_matrix_2[0]._data[0][1] = 3;
	vector_matrix_2[0]._data[1][2] = 5;
	vector_matrix_2[0]._data[2][2] = 7;
	MWVector<MWMatrix<MWData> > vector_matrix_3 = vector_matrix;
	assign_minus(vector_matrix, vector_matrix_2, vector_matrix_3);
	LOG_INFO(_logger, "(vector_matrix = " << vector_matrix << ") - (vector_matrix_2 = " << vector_matrix_2 << ") = (vector_matrix_3 = " << vector_matrix_3 << ")");

	assign_times(vector_matrix, 2, vector_matrix_3);
	LOG_INFO(_logger, "(vector_matrix = " << vector_matrix << ") * 2 = (vector_matrix_3 = " << vector_matrix_3 << ")");

	assign_times(vector_matrix, m11, vector_matrix_3);
	LOG_INFO(_logger, "(vector_matrix = " << vector_matrix << ") * (m11 = " << m11 << ") = (vector_matrix_3 = " << vector_matrix_3 << ")");

	assign_times(vector_matrix, vector_matrix_2, vector_matrix_3);
	LOG_INFO(_logger, "(vector_matrix = " << vector_matrix << ") * (vector_matrix_2 = " << vector_matrix_2 << ") = (vector_matrix_3 = " << vector_matrix_3 << ")");

	m11._data[1][0] = 3;
	m12._data[1][0] = 5;
	m12._data[1][2] = 7;
	assign_times_transformed(m12, m11, m13);
	LOG_INFO(_logger, "(m12 = " << m12 << ") * (m11.t() = " << m11.t() << ") = (m13 = " << m13 << ")");

	assign_diagonaled_times_transformed(vector_matrix, m13, vector_matrix_3);
	LOG_INFO(_logger, "(vector_matrix = " << vector_matrix << ") * (m13 = " << m13.t() << ") assign_diagonaled_times_transformed= (vector_matrix_3 = " << vector_matrix_3 << ")");

	LOG_INFO(_logger, "m11 = " << m11);
	m11 = m11.to_squared();
	LOG_INFO(_logger, "m11.to_squared() = " << m11);

	return EXIT_SUCCESS;
}

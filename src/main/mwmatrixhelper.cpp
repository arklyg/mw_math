#include "mwmatrixhelper.h"

MWVector<MWVector<MWMatrix<MWData> > > &assign_times_transformed(const MWVector<MWVector<MWMatrix<MWData> > > &v_m1, const MWVector<MWVector<MWMatrix<MWData> > > &v_m2, MWVector<MWVector<MWMatrix<MWData> > > &ret)
{
	if (v_m1.size() != v_m2.size())
	{
		LOG_ERROR(_logger, "(v_m1.size() = " << v_m1.size() << ") != (v_m2.size() = " << v_m2.size() << "), can not do, return");
		return ret;
	}

	for (size_t i = 0; i < v_m1.size(); ++ i)
	{
		assign_times_transformed(v_m1[i], v_m2[i], ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &assign_plus(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v1.size() != v2.size() || v1.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v1.size() = " << v1.size() << ") != (v2.size() = " << v2.size() << ") || (v1.size() = " << v1.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i)
	{
		assign_plus(v1[i], v2[i], ret[i]);
	}

	return ret;
}

// len = 0 表示计算到结尾
MWVector<MWMatrix<MWData> > &assign_minus(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v1.size() != v2.size() || v1.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v1.size() = " << v1.size() << ") != (v2.size() = " << v2.size() << ") || (v1.size() = " << v1.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i)
	{
		assign_minus(v1[i], v2[i], ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v1.size() != v2.size() || v1.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v1.size() = " << v1.size() << ") != (v2.size() = " << v2.size() << ") || (v1.size() = " << v1.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i)
	{
		assign_times(v1[i], v2[i], ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &assign_times_transformed(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v1.size() != v2.size() || v1.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v1.size() = " << v1.size() << ") != (v2.size() = " << v2.size() << ") || (v1.size() = " << v1.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i)
	{
		assign_times_transformed(v1[i], v2[i], ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &assign_diagonaled_times_transformed(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v1.size() != v2.size() || v1.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v1.size() = " << v1.size() << ") != (v2.size() = " << v2.size() << ") || (v1.size() = " << v1.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i)
	{
		assign_diagonaled_times_transformed(v1[i], v2[i], ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &assign_diagonaled_times(const MWVector<MWMatrix<MWData> > &v1, const MWVector<MWMatrix<MWData> > &v2, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v1.size() != v2.size() || v1.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v1.size() = " << v1.size() << ") != (v2.size() = " << v2.size() << ") || (v1.size() = " << v1.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v1.size(); ++ i)
	{
		assign_diagonaled_times(v1[i], v2[i], ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &assign_plus(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v.size() = " << v.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i)
	{
		assign_plus(v[i], m, ret[i]);
	}

	return ret;
}


MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v.size() = " << v.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i)
	{
		assign_times(v[i], m, ret[i]);
	}
	
	return ret;
}

MWVector<MWMatrix<MWData> > &assign_diagonaled_times_transformed(const MWVector<MWMatrix<MWData> > &v, const MWMatrix<MWData> &m, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v.size() = " << v.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i)
	{
		assign_diagonaled_times_transformed(v[i], m, ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &assign_times(const MWVector<MWMatrix<MWData> > &v, const MWData &scale, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v.size() = " << v.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i)
	{
		assign_times(v[i], scale, ret[i]);
	}
	
	return ret;
}

MWVector<MWMatrix<MWData> > &assign_times(const MWMatrix<MWData> &m, const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v.size() = " << v.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i)
	{
		assign_times(m, v[i], ret[i]);
	}
	
	return ret;
}

MWVector<MWMatrix<MWData> > &assign_square(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v.size() = " << v.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i)
	{
		v[i].assign_square(ret[i]);
	}

	return ret;
}

MWVector<MWMatrix<MWData> > &assign(const MWVector<MWMatrix<MWData> > &v, MWVector<MWMatrix<MWData> > &ret, size_t off, size_t len)
{
	if (v.size() != ret.size())
	{
		LOG_ERROR(_logger, "(v.size() = " << v.size() << ") != (ret.size() = " << ret.size() << "), return.");
		return ret;
	}

	for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i)
	{
		v[i].assign(ret[i]);
	}

	return ret;
}

MWMatrix<MWData> &assign_sum(const MWVector<MWMatrix<MWData> > &v, MWMatrix<MWData> &ret, size_t off, size_t len)
{
	ret = 0;
	for (size_t i = off; (i < off + len || len == 0) && i < v.size(); ++ i)
	{
		assign_plus(ret, v[i], ret);
	}

	return ret;
}

MWMatrix<MWData> &assign_plus(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret)
{
	if (m1.get_matrix_info() != m2.get_matrix_info())
	{
		LOG_ERROR(_logger, "(m1._info = " << m1.get_matrix_info() << ") != (m2._info = " << m2.get_matrix_info() << ", can not do, return");
		return ret;
	}

	for (size_t i = 0, j; i < m1.get_row_num(); ++ i)
	{
		for(j = 0; j < m1.get_column_num(); ++ j)
		{
			ret._data[i][j] = m1._data[i][j] + m2._data[i][j];
		}
	}

	return ret;
}

MWMatrix<MWData> &assign_minus(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret)
{
	if (m1.get_matrix_info() != m2.get_matrix_info())
	{
		LOG_ERROR(_logger, "(m1._info = " << m1.get_matrix_info() << ") != (m2._info = " << m2.get_matrix_info() << ", can not do, return");
		return ret;
	}

	for (size_t i = 0, j; i < m1.get_row_num(); ++ i)
	{
		for(j = 0; j < m1.get_column_num(); ++ j)
		{
			ret._data[i][j] = m1._data[i][j] - m2._data[i][j];
		}
	}

	return ret;
}

MWMatrix<MWData> &assign_times(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret)
{
	if (m1.get_column_num() != m2.get_row_num())
	{
		LOG_ERROR(_logger, "m1._matrix_info = " << m1.get_matrix_info() << ", m2._matrix_info = " << m2.get_matrix_info() << ", can not do operator *");
		return ret;
	}

	for (size_t i_row = 0, i_column, i; i_row < m1.get_row_num(); ++ i_row)
	{
		for (i_column = 0; i_column < m2.get_column_num(); ++ i_column)
		{
			for (i = 0; i < m1.get_column_num(); ++ i)
			{
				ret._data[i_row][i_column] = (i == 0 ? 0 : ret._data[i_row][i_column]) + m1._data[i_row][i] * m2._data[i][i_column];
			}
		}
	}

	return ret;
}

MWMatrix<MWData> &assign_times_transformed(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret)
{
	if (m1.get_column_num() != m2.get_column_num())
	{
		LOG_ERROR(_logger, "m1._matrix_info = " << m1.get_matrix_info() << ", m2._matrix_info = " << m2.get_matrix_info() << ", can not do operator *");
		return ret;
	}

	for (size_t i_row = 0, i_column, i; i_row < m1.get_row_num(); ++ i_row)
	{
		for (i_column = 0; i_column < m2.get_row_num(); ++ i_column)
		{
			for (i = 0; i < m1.get_column_num(); ++ i)
			{
				ret._data[i_row][i_column] = (i == 0 ? 0 : ret._data[i_row][i_column]) + m1._data[i_row][i] * m2._data[i_column][i];
			}
		}
	}

	return ret;
}

MWMatrix<MWData> &assign_diagonaled_times_transformed(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret)
{
	if (m1.get_row_num() != m2.get_column_num())
	{
		LOG_ERROR(_logger, "(m1.info = " << m1.get_matrix_info() << "), (m2.info = " << m2.get_matrix_info() << "), can not do assign_diagonaled_times_transformed, return");
		return ret;
	}

	for (size_t i = 0, j; i < m2.get_column_num(); ++ i)
	{
		for (j = 0; j < m2.get_row_num(); ++ j)
		{
			ret._data[i][j] = m1._data[i][0] * m2._data[j][i];
		}
	}

	return ret;
}

MWMatrix<MWData> &assign_diagonaled_times(const MWMatrix<MWData> &m1, const MWMatrix<MWData> &m2, MWMatrix<MWData> &ret)
{
	if (m1.get_row_num() != m2.get_row_num())
	{
		LOG_ERROR(_logger, "(m1.info = " << m1.get_matrix_info() << "), (m2.info = " << m2.get_matrix_info() << "), can not do assign_diagonaled_times, return");
		return ret;
	}

	for (size_t i = 0, j; i < m2.get_row_num(); ++ i)
	{
		for (j = 0; j < m2.get_column_num(); ++ j)
		{
			ret._data[i][j] = m1._data[i][0] * m2._data[i][j];
		}
	}

	return ret;
}

MWMatrix<MWData> &assign_times(const MWMatrix<MWData> &m, const MWData &scale, MWMatrix<MWData> &ret)
{
	for (size_t i = 0, j; i < m.get_row_num(); ++ i)
	{
		for(j = 0; j < m.get_column_num(); ++ j)
		{
			ret._data[i][j] = m._data[i][j] * scale;
		}
	}

	return ret;
}


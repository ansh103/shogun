/*
 * This software is distributed under BSD 3-clause license (see LICENSE file).
 *
 * Authors: Heiko Strathmann, Soumyajit De, Björn Esser
 */

#ifndef DENSE_EXACT_LOG_JOB_H_
#define DENSE_EXACT_LOG_JOB_H_

#include <shogun/lib/config.h>

#include <shogun/lib/computation/job/IndependentJob.h>

namespace shogun
{
template<class T> class SGVector;
template<class T> class CDenseMatrixOperator;

/** @brief Class that represents the job of applying the log of
 * a CDenseMatrixOperator on a real vector
 */
class CDenseExactLogJob : public CIndependentJob
{
public:
	/** default constructor */
	CDenseExactLogJob();

	/**
	 * constructor
	 *
	 * @param aggregator the job result aggregator for this job
	 * @param log_operator the dense matrix operator to be applied to the vector
	 * @param vector the sample vector to which operator is to be applied
	 */
	CDenseExactLogJob(CJobResultAggregator* aggregator,
		CDenseMatrixOperator<float64_t>* log_operator,
		SGVector<float64_t> vector);

	/** destructor */
	virtual ~CDenseExactLogJob();

	/** implementation of compute method for the job */
	virtual void compute();

	/** @return the vector */
	SGVector<float64_t> get_vector() const;

	/** @return the linear operator */
	CDenseMatrixOperator<float64_t>* get_operator() const;

	/** @return object name */
	virtual const char* get_name() const
	{
		return "DenseExactLogJob";
	}

private:
	/** the log of a CDenseMatrixOperator<float64_t> */
	CDenseMatrixOperator<float64_t>* m_log_operator;

	/** the trace-sample */
	SGVector<float64_t> m_vector;

	/** initialize with default values and register params */
	void init();
};

}

#endif // DENSE_EXACT_LOG_JOB_H_
